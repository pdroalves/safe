/*
  Safe: Encrypted File System
  Copyright (C) 2013 Rian Hunter <rian@alum.mit.edu>

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

#ifndef __safe_safe_tray_menu_hpp
#define __safe_safe_tray_menu_hpp

#include <safe/constants.h>
#include <safe/util.hpp>

#include <cassert>
#include <cstdint>

#include "language.hpp"

namespace safe {

enum class TrayMenuAction : uint16_t {
  _NO_ACTION,
  UNMOUNT,
  OPEN,
  CREATE,
  MOUNT,
  MOUNT_RECENT,
  CLEAR_RECENTS,
  TOGGLE_RUN_AT_LOGIN,
  ABOUT_APP,
  TEST_BUBBLE,
  TRIGGER_BREAKPOINT,
  QUIT_APP,
  SEND_FEEDBACK,
  THROW_EXCEPTION,
};

typedef uint16_t tray_menu_action_arg_t;

enum class TrayMenuProperty {
    MAC_FILE_TYPE,
};

constexpr size_t _MENU_ACTION_BITS = safe::numbits<tray_menu_action_arg_t>::value;

template<typename Container>
std::tuple<TrayMenuAction, tray_menu_action_arg_t>
decode_menu_id(Container menu_id) {
  return std::make_tuple((safe::TrayMenuAction) (menu_id >> _MENU_ACTION_BITS),
                         menu_id & safe::create_bit_mask<Container>(_MENU_ACTION_BITS));
}

template<typename Container>
Container
encode_menu_id(safe::TrayMenuAction action,
               safe::tray_menu_action_arg_t action_arg) {
  static_assert(_MENU_ACTION_BITS == safe::numbits<decltype(action_arg)>::value, "invalid argument");
  static_assert(sizeof(Container) >= sizeof(action_arg), "Container IS TOO SMALL");
  static_assert(sizeof(Container) >= sizeof(action), "Container Is too small");
  auto action_int = static_cast<Container>(action);
  assert(!action_int ||
         safe::numbitsf(action_int) - safe::numbitsf(action_arg) >
         safe::position_of_highest_bit_set(action_int));
  return (action_int << _MENU_ACTION_BITS) | action_arg;
}

template<typename Menu, typename MountList, typename RecentMountStore>
void
populate_tray_menu(Menu & menu,
                   const MountList & mounts,
                   const RecentMountStore & recent_mounts,
                   bool startup_enabled,
                   bool show_alternative_menu) {
  // Menu is:
  // [ (Open | Unmount) "<mount name>" ]
  // ...
  // [ <separator> ]
  // Create New...
  // Mount Existing...
  // Mount Recent >
  //   [ <folder icon> <mount name> ]
  //   ...
  //   [ <separator> ]
  //   Clear Menu
  // <separator>
  // [✓] Run Safe at Login
  // Send Feedback
  // About Safe
  // [ Test Bubble ]
  // [ Trigger Breakpoint ]
  // <separator>
  // Quit

  const bool show_unmount = show_alternative_menu;
  std::string mount_verb_string;
  TrayMenuAction mount_action_id;
  if (show_unmount) {
    mount_verb_string = get_phrase("UNMOUNT");
    mount_action_id = TrayMenuAction::UNMOUNT;
  }
  else {
    mount_verb_string =get_phrase( "OPEN");
    mount_action_id = TrayMenuAction::OPEN;
  }

  tray_menu_action_arg_t mount_tag = 0;
  for (const auto & md : mounts) {
    auto title = mount_verb_string + " \"" + md.get_mount_name() + "\"";
    menu.append_item(title, mount_action_id, mount_tag);
    ++mount_tag;
    assert(mount_tag);
  }

  if (mount_tag) menu.append_separator();

  // create "Mount Recent" submenu
  if (true) {
    auto sub_menu = menu.append_menu(get_phrase("MOUNT_RECENT"));

    tray_menu_action_arg_t sub_tag = 0;
    for (const auto & p : recent_mounts) {
      auto item = sub_menu.append_item(p.get_last_known_name(),
                                       TrayMenuAction::MOUNT_RECENT, sub_tag);
      opt::optional<encfs::Path> path;
      try {
        path = p.get_last_known_path();
      }
      catch (const std::exception & err) {
        lbx_log_error("Error while trying to get path: %s", err.what());
      }

      if (path) item.set_tooltip(*path);

      item.set_property(TrayMenuProperty::MAC_FILE_TYPE, "public.folder");

      ++sub_tag;
    }

    if (sub_tag) sub_menu.append_separator();

    auto item = sub_menu.append_item(get_phrase("CLEAR_MENU"), TrayMenuAction::CLEAR_RECENTS);
    if (!sub_tag) item.disable();
  }

  // Mount an Existing Bitvault
  menu.append_item(get_phrase("MOUNT_EXISTING"), TrayMenuAction::MOUNT);

  // Create a New Bitvault
  menu.append_item(get_phrase("CREATE_NEW"), TrayMenuAction::CREATE);

  menu.append_separator();

  // About Bitvault
  menu.append_item(get_phrase("ABOUT") PRODUCT_NAME_A, TrayMenuAction::ABOUT_APP);

  menu.append_item(SAFE_TRAY_ICON_SEND_FEEDBACK, TrayMenuAction::SEND_FEEDBACK);

  menu.append_item(get_phrase("RUN") " " PRODUCT_NAME_A " " get_phrase("AT_LOGIN"),
                     TrayMenuAction::TOGGLE_RUN_AT_LOGIN)
    .set_checked(startup_enabled);

#ifndef NDEBUG
  menu.append_separator();

  // Test Bubble
  menu.append_item(get_phrase("TEST_BUBBLE"), TrayMenuAction::TEST_BUBBLE);

  menu.append_item(get_phrase("TRIGGER_BREAKPOINT"), TrayMenuAction::TRIGGER_BREAKPOINT);

  menu.append_item(get_phrase("THROW_EXCEPTION"), TrayMenuAction::THROW_EXCEPTION);
#endif

  menu.append_separator();

  menu.append_item(get_phrase("QUIT") " " PRODUCT_NAME_A, TrayMenuAction::QUIT_APP);
}

}

#endif
