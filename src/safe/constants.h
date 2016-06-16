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

#ifndef _safe_constants_h
#define _safe_constants_h

#include <safe/product_name.h>
#include <safe/version.h>
#include "language.hpp"

#define SAFE_APP_STARTED_COOKIE_FILENAME "AppStarted"
#define SAFE_RECENTLY_USED_PATHS_DB_FILE_NAME "RecentPaths.db"
#define SAFE_REMEMBER_PASSWORD_COOKIE_FILENAME "RememberPasswordChecked"
#define SAFE_DONT_SHOW_SYSTEM_CHANGES_INSTALL_COOKIE_FILENAME "DontShowSystemChangesInstall"
#define SAFE_DONT_SHOW_WINXP_WARNING_COOKIE_FILENAME "DontShowWindowsXPWarning"

enum {
  SAFE_RECENTLY_USED_PATHS_MENU_NUM_ITEMS=10,
};

#define SAFE_SOURCE_CODE_WEBSITE "http://getsafe.org/app/get_source_code"
#define SAFE_SEND_FEEDBACK_WEBSITE "http://getsafe.org/app/send_feedback"
#define SAFE_WINDOWS_SYSTEM_CHANGES_INFO_WEBSITE "http://getsafe.org/app/windows_system_changes_more_info"
#define SAFE_MAC_SYSTEM_CHANGES_INFO_WEBSITE "http://getsafe.org/app/mac_system_changes_more_info"
#define SAFE_REPORT_EXCEPTION_WEBSITE "http://getsafe.org/app/report_exception"
#define SAFE_VISIT_WEBSITE_WEBSITE "http://getsafe.org/app/visit_website"
#define SAFE_WINXP_MORE_INFO_WEBSITE "http://getsafe.org/app/winxp_more_info"

/* UI Strings follow */

#define SAFE_TRAY_ICON_TOOLTIP PRODUCT_NAME_A

#define SAFE_PROGRESS_CREATING_TITLE (get_phrase("CREATING_NEW") " " ENCRYPTED_STORAGE_NAME_A "...")
#define SAFE_PROGRESS_CREATING_MESSAGE (get_phrase("CREATING_NEW") " " ENCRYPTED_STORAGE_NAME_A "...")

#define SAFE_PROGRESS_MOUNTING_TITLE (get_phrase("MOUNTING_NEW") " " ENCRYPTED_STORAGE_NAME_A "...")
#define SAFE_PROGRESS_MOUNTING_MESSAGE (get_phrase("MOUNTING_NEW") " " ENCRYPTED_STORAGE_NAME_A "...")

#define SAFE_PROGRESS_MOUNTING_EXISTING_TITLE (get_phrase("MOUNTING_EXISTING") " " ENCRYPTED_STORAGE_NAME_A "...")
#define SAFE_PROGRESS_MOUNTING_EXISTING_MESSAGE (get_phrase("MOUNTING_EXISTING") " " ENCRYPTED_STORAGE_NAME_A "...")

#define SAFE_PROGRESS_VERIFYING_PASS_TITLE (get_phrase("VERIFYING") " " ENCRYPTED_STORAGE_NAME_A " " get_phrase("PASSWORD_UPPERCASE"))
#define SAFE_PROGRESS_VERIFYING_PASS_MESSAGE (get_phrase("VERIFYING") " " ENCRYPTED_STORAGE_NAME_A " " get_phrase("PASSWORD_LOWERCASE"))

#define SAFE_PROGRESS_READING_CONFIG_TITLE (get_phrase("READING") " " ENCRYPTED_STORAGE_NAME_A " " get_phrase("CONFIGURATION"))
#define SAFE_PROGRESS_READING_CONFIG_MESSAGE (get_phrase("READING") " " ENCRYPTED_STORAGE_NAME_A " " get_phrase("CONFIGURATION"))

#define SAFE_DIALOG_PASS_INCORRECT_TITLE get_phrase("PASSWORD_IS_INCORRECT")
#define SAFE_DIALOG_PASS_INCORRECT_MESSAGE get_phrase("THE_PASSWORD_YOU_HAVE_ENTERED_IS_INCORRECT")

#define SAFE_DIALOG_NO_CONFIG_EXISTS_TITLE (get_phrase("NOT_A")" " ENCRYPTED_STORAGE_NAME_A)
#define SAFE_DIALOG_NO_CONFIG_EXISTS_MESSAGE (get_phrase("THE_LOCATION_YOU_SELECTED_IS_NOT_A")" " ENCRYPTED_STORAGE_NAME_A ".")

#define SAFE_DIALOG_QUIT_CONFIRMATION_TITLE (get_phrase("QUIT") PRODUCT_NAME_A " " get_phrase("NOW_QUESTIONMARK"))
#define SAFE_DIALOG_QUIT_CONFIRMATION_MESSAGE (get_phrase("YOU_CURRENTLY_HAVE_ONE_OR_MORE") " " ENCRYPTED_STORAGE_NAME_A get_phrase("S_MOUNTED",_IF_YOU_QUIT_THEY_WILL_NOT_BE_ACCESSIBLE_UNTIL_YOU_RUN) " " PRODUCT_NAME_A " " get_phrase("AGAIN") " " get_phrase("QUIT") PRODUCT_NAME_A " " get_phrase("NOW_QUESTIONMARK"))

#define SAFE_DIALOG_UNKNOWN_CREATE_ERROR_TITLE get_phrase("UNKNOWN_ERROR")
#define SAFE_DIALOG_UNKNOWN_CREATE_ERROR_MESSAGE (get_phrase("UNKNOWN_ERROR_OCCURRED_WHILE_CREATING_NEW") " " ENCRYPTED_STORAGE_NAME_A ".")

#define SAFE_DIALOG_UNKNOWN_MOUNT_ERROR_TITLE get_phrase("UNKNOWN_ERROR")
#define SAFE_DIALOG_UNKNOWN_MOUNT_ERROR_MESSAGE (get_phrase("UNKNOWN_ERROR_OCCURRED_WHILE_MOUNTING_EXISTING")" " ENCRYPTED_STORAGE_NAME_A ".")

#define SAFE_DIALOG_ABOUT_TITLE (get_phrase("ABOUT") " " PRODUCT_NAME_A)
#define SAFE_DIALOG_WELCOME_TITLE (get_phrase("WELCOME_TO") " " PRODUCT_NAME_A "!")

#define SAFE_TRAY_ICON_WELCOME_TITLE (PRODUCT_NAME_A " " get_phrase("IS_NOW_RUNNING"))

#define SAFE_TRAY_ICON_MAC_WELCOME_MSG \
  (get_phrase("SAFE_TRAY_ICON_MAC_WELCOME_MSG_A") \
    PRODUCT_NAME_A get_phrase("SAFE_TRAY_ICON_MAC_WELCOME_MSG_B") \
    PRODUCT_NAME_A get_phrase("SAFE_TRAY_ICON_MAC_WELCOME_MSG_C"))

#define SAFE_DIALOG_WELCOME_TEXT \
  (PRODUCT_NAME_A " " get_phrase("SAFE_DIALOG_WELCOME_TEXT_A")
    PRODUCT_NAME_A " "get_phrase("SAFE_DIALOG_WELCOME_TEXT_B"))

#define SAFE_DIALOG_WELCOME_TEXT_POST_DRIVER_INSTALL \
  (get_phrase("SAFE_DIALOG_WELCOME_TEXT_POST_DRIVER_INSTALL_A") PRODUCT_NAME_A ". " \
   get_phrase("SAFE_DIALOG_WELCOME_TEXT_POST_DRIVER_INSTALL_B"))

#define SAFE_DIALOG_WELCOME_CREATE_BUTTON \
  (get_phrase("CREATE_NEW") ENCRYPTED_STORAGE_NAME_A "...")
#define SAFE_DIALOG_WELCOME_MOUNT_BUTTON \
  (get_phrase("MOUNT_EXISTING") ENCRYPTED_STORAGE_NAME_A "...")

#define SAFE_NOTIFICATION_TEST_TITLE get_phrase("SAFE_NOTIFICATION_TEST_TITLE")
#define SAFE_NOTIFICATION_TEST_MESSAGE get_phrase("SAFE_NOTIFICATION_TEST_MESSAGE")

#define SAFE_DIALOG_ABOUT_TAGLINE get_phrase("SAFE_DIALOG_ABOUT_TAGLINE")
#define SAFE_DIALOG_ABOUT_VERSION get_phrase("SAFE_DIALOG_ABOUT_VERSION") " " SAFE_VERSION_STR

#define SAFE_DIALOG_ABOUT_BYLINE (PRODUCT_NAME_A " " get_phrase("SAFE_DIALOG_ABOUT_BYLINE"))

#define SAFE_TRAY_ICON_SEND_FEEDBACK get_phrase("SAFE_TRAY_ICON_SEND_FEEDBACK")

#define SAFE_DIALOG_REBOOT_CONFIRMATION_TITLE get_phrase("SAFE_DIALOG_REBOOT_CONFIRMATION_TITLE")
#define SAFE_DIALOG_REBOOT_CONFIRMATION_MESSAGE  (get_phrase("SAFE_DIALOG_REBOOT_CONFIRMATION_MESSAGE_A")   PRODUCT_NAME_A get_phrase("SAFE_DIALOG_REBOOT_CONFIRMATION_MESSAGE_B"))
#define SAFE_DIALOG_REBOOT_CONFIRMATION_MESSAGE_MAC  \
  (get_phrase("SAFE_DIALOG_REBOOT_CONFIRMATION_MESSAGE_MAC_A")" " \
  PRODUCT_NAME_A get_phrase("SAFE_DIALOG_REBOOT_CONFIRMATION_MESSAGE_MAC_B") PRODUCT_NAME_A\
  " " get_phrase("SAFE_DIALOG_REBOOT_CONFIRMATION_MESSAGE_MAC_C"))


#define SAFE_DIALOG_SYSTEM_CHANGES_TITLE get_phrase("SAFE_DIALOG_SYSTEM_CHANGES_TITLE") 
#define SAFE_DIALOG_SYSTEM_CHANGES_HEADER get_phrase("SAFE_DIALOG_SYSTEM_CHANGES_HEADER")  
#define SAFE_DIALOG_SYSTEM_CHANGES_BULLET "•"
#define SAFE_DIALOG_SYSTEM_CHANGES_FOOTER get_phrase("SAFE_DIALOG_SYSTEM_CHANGES_FOOTER")  
#define SAFE_DIALOG_SYSTEM_CHANGES_MAKE_CHANGES get_phrase("SAFE_DIALOG_SYSTEM_CHANGES_MAKE_CHANGES") 
#define SAFE_DIALOG_SYSTEM_CHANGES_DONT_MAKE_CHANGES get_phrase("SAFE_DIALOG_SYSTEM_CHANGES_DONT_MAKE_CHANGES") 
#define SAFE_DIALOG_SYSTEM_CHANGES_MORE_INFO get_phrase("SAFE_DIALOG_SYSTEM_CHANGES_MORE_INFO") 

#define SAFE_PROGRESS_SYSTEM_CHANGES_TITLE get_phrase("SAFE_PROGRESS_SYSTEM_CHANGES_TITLE") 
#define SAFE_PROGRESS_SYSTEM_CHANGES_MESSAGE get_phrase("SAFE_PROGRESS_SYSTEM_CHANGES_MESSAGE") 

#endif
