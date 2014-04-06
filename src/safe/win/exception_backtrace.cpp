/*
  Safe: Encrypted File System
  Copyright (C) 2014 Rian Hunter <rian@alum.mit.edu>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#include <safe/win/exception_backtrace.hpp>

#include <safe/exception_backtrace.hpp>
#include <safe/optional.hpp>
#include <safe/util.hpp>
#include <safe/win/util.hpp>

#include <w32util/sync.hpp>

#include <iostream>
#include <vector>
#include <unordered_map>

#include <windows.h>
#include <dbghelp.h>

// NB: Warning: this file is highly platform dependent
//     it requires a specific:
//     * Linker (GNU ld)
//     * C++ STL (libstdc++)
//     * Arch (i386 or x86_64)

namespace safe { namespace win {

void *
extract_raw_exception_pointer(std::exception_ptr p) {
  void *out;
  static_assert(sizeof(p) == sizeof(out), "exception ptr is not a pointer?");
  memcpy(&out, &p, sizeof(out));
  return out;
}

template <class T>
ptrdiff_t
pointer_difference_in_bytes(T *a, T *b) {
  return (uint8_t *) a - (uint8_t *) b;
}

void *
get_image_base() {
  HMODULE exe_module;
  w32util::check_bool(GetModuleHandleExW,
                      GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                      (LPCWSTR) &get_image_base,
                      &exe_module);
  return (void *) exe_module;
}

OffsetBacktrace
backtrace_to_offset_backtrace(const Backtrace & backtrace) {
  HMODULE exe_module;
  auto success = GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                                    (LPCWSTR) &backtrace_to_offset_backtrace,
                                    &exe_module);
  if (!success) abort();

  std::vector<ptrdiff_t> stack_trace;
  for (const auto & addr : backtrace) {
    // find module of function
    HMODULE return_addr_module;
    auto success2 = GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                                       // NB: we subtract one because the return address might be after the
                                       //     last byte in the module (remote chance of this happening for noreturn functions)
                                       (LPCWSTR) ((char *) addr - 1),
                                       &return_addr_module);

    stack_trace.push_back(!success2
                          ? (ptrdiff_t) -1
                          : return_addr_module == exe_module
                          ? pointer_difference_in_bytes(addr, (decltype(addr)) exe_module)
                          : 0);
  }

  return stack_trace;
}

}}

// NB: we use GNU ld's --wrap option to wrap the call to __cxa_throw()

extern "C"
void __real___cxa_throw(void *thrown_exception,
                        std::type_info *tinfo, void (*dest)(void *))
  __attribute__((noreturn));

extern "C"
void __wrap___cxa_throw(void *thrown_exception,
                        std::type_info *tinfo, void (*dest)(void *))
  __attribute__((noreturn));

class TlsBool {
  DWORD _tls_idx;
public:
  TlsBool() {
    _tls_idx = TlsAlloc();
    if (_tls_idx == TLS_OUT_OF_INDEXES) abort();
  }

  TlsBool &operator=(bool f) {
    auto success = TlsSetValue(_tls_idx, (LPVOID) f);
    if (!success) abort();
    return *this;
  }

  operator bool() const {
    auto ret = TlsGetValue(_tls_idx);
    if (!ret && GetLastError() != ERROR_SUCCESS) abort();
    return (bool) ret;
  }
};

extern "C"
void
__wrap___cxa_throw(void *thrown_exception,
                   std::type_info *tinfo, void (*dest)(void *)) {
  static TlsBool is_currently_throwing;

  // if we throw during the course of executing stack save code
  // then we just abort
  if (is_currently_throwing) abort();

  is_currently_throwing = true;

  // NB: by using __builtin_frame_address() we force this function to have a
  //     frame pointer
  auto cur_bp = __builtin_frame_address(0);

  // derive pseudo-processor state after call to __cxa_throw()
#if defined(__i386__) || defined(__x86_64)
  auto bp_before_our_call = *(void **) cur_bp;
  auto sp_before_our_call = (void *) (((intptr_t) cur_bp) + 2 * sizeof(void *));
  auto return_address = *(void **) ((intptr_t) cur_bp + sizeof(void *));
#else
#error arch not supported!
#endif

  CONTEXT ctx;
  memset(&ctx, 0, sizeof(ctx));
  ctx.ContextFlags = CONTEXT_FULL;

  // init stack frame structure
  STACKFRAME64 frame;
  memset(&frame, 0, sizeof(frame));

#if defined(__i386__) && !defined(__x86_64)
  ctx.Eip = (DWORD) return_address;
  ctx.Esp = (DWORD) sp_before_our_call;
  ctx.Ebp = (DWORD) bp_before_our_call;

  frame.AddrPC.Offset = ctx.Eip;
  frame.AddrPC.Mode = AddrModeFlat;
  frame.AddrStack.Offset = ctx.Esp;
  frame.AddrStack.Mode = AddrModeFlat;
  frame.AddrFrame.Offset = ctx.Ebp;
  frame.AddrFrame.Mode = AddrModeFlat;
  const auto machine = IMAGE_FILE_MACHINE_I386;
#elif defined(__x86_64)
  ctx.Rip = (DWORD_PTR) return_address;
  ctx.Rsp = (DWORD_PTR) sp_before_our_call;
  ctx.Rbp = (DWORD_PTR) bp_before_our_call;

  frame.AddrPC.Offset = ctx.Rip;
  frame.AddrPC.Mode = AddrModeFlat;
  frame.AddrStack.Offset = ctx.Rsp;
  frame.AddrStack.Mode = AddrModeFlat;
  frame.AddrFrame.Offset = ctx.Rbp;
  frame.AddrFrame.Mode = AddrModeFlat;
  const auto machine = IMAGE_FILE_MACHINE_AMD64;
#else
#error "arch not supported!"
#endif

  auto process = GetCurrentProcess();
  auto thread = GetCurrentThread();

  // get stack trace
  auto stack_trace = std::vector<void *>();
  while (true) {
    auto success = StackWalk64(machine, process, thread,
                               &frame, &ctx,
                               nullptr, SymFunctionTableAccess64, SymGetModuleBase64,
                               nullptr);
    if (!success) break;

    stack_trace.push_back((void *) frame.AddrPC.Offset);
  }

  safe::_set_backtrace_for_exception_ptr(thrown_exception, std::move(stack_trace));

  is_currently_throwing = false;

  // call original __cxa_throw
  __real___cxa_throw(thrown_exception, tinfo, dest);
}
