/*
  Lockbox: Encrypted File System
  Copyright (C) 2013 Rian Hunter <rian@alum.mit.edu>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lessage General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#ifndef _FS_FSIO_H
#define _FS_FSIO_H

#include <davfuse/iface_util.h>
#include <davfuse/shared_types_fs.h>

#define OUT_VAR

#ifdef __cplusplus
extern "C" {
#endif

fs_error_t
fs_fsio_open(fs_handle_t fs,
             const char *path, bool create,
             OUT_VAR fs_file_handle_t *handle,
             OUT_VAR bool *created);

fs_error_t
fs_fsio_fgetattr(fs_handle_t fs, fs_file_handle_t file_handle,
                 OUT_VAR FsAttrs *attrs);

fs_error_t
fs_fsio_ftruncate(fs_handle_t fs, fs_file_handle_t file_handle,
                  fs_off_t offset);

fs_error_t
fs_fsio_read(fs_handle_t fs, fs_file_handle_t file_handle,
             OUT_VAR char *buf, size_t size, fs_off_t off,
             OUT_VAR size_t *amt_read);

fs_error_t
fs_fsio_write(fs_handle_t fs, fs_file_handle_t file_handle,
              const char *buf, size_t size, fs_off_t off,
              OUT_VAR size_t *amt_written);

fs_error_t
fs_fsio_close(fs_handle_t fs, fs_file_handle_t handle);

fs_error_t
fs_fsio_opendir(fs_handle_t fs, const char *path,
                OUT_VAR fs_directory_handle_t *dir_handle);

fs_error_t
fs_fsio_readdir(fs_handle_t fs, fs_directory_handle_t dir_handle,
                /* name is required and malloc'd by the implementation,
                   the user must free the returned pointer
                */
                OUT_VAR char **name,
                /* attrs is optionally filled by the implementation */
                OUT_VAR bool *attrs_is_filled,
                OUT_VAR FsAttrs *attrs);

fs_error_t
fs_fsio_closedir(fs_handle_t fs, fs_directory_handle_t dir_handle);

/* can remove either a file or a directory,
   removing a directory should fail if it's not empty
*/
fs_error_t
fs_fsio_remove(fs_handle_t fs, const char *path);

fs_error_t
fs_fsio_mkdir(fs_handle_t fs, const char *path);

fs_error_t
fs_fsio_getattr(fs_handle_t fs, const char *path,
                OUT_VAR FsAttrs *attrs);

fs_error_t
fs_fsio_rename(fs_handle_t fs,
               const char *src, const char *dst);

bool
fs_fsio_path_is_root(fs_handle_t fs, const char *path);

bool
fs_fsio_path_equals(fs_handle_t fs, const char *a, const char *b);

bool
fs_fsio_path_is_parent(fs_handle_t fs,
                       const char *potential_parent,
                       const char *potential_child);

const char *
fs_fsio_path_sep(fs_handle_t fs);

CREATE_IMPL_TAG(FS_FSIO_IMPL);

#ifdef __cplusplus
}
#endif

#undef OUT_VAR

#endif
