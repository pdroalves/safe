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
#ifndef LANGUAGE__HPP
#define LANGUAGE__HPP
#include <stdexcept>
#include <string>
#include <map>
#include "tinyxml.h"

///////////////////////////////////////////////////////////////////
// Defines the supported languages and the respective input file //
///////////////////////////////////////////////////////////////////
enum supported_languages {EN_US,LEN_SUPPORTED_LANGUAGES};
const char * const language_files[] = {"../resources/language/en-us.xml"};
typedef std::map<std::string,std::string> PhraseMap;
typedef std::map<std::string,std::string>::iterator PhraseIterator;
///////////////////////////////////////////////////////////////////

///////////////
// Functions //
///////////////
void set_language(int l);

std::string get_phrase(std::string token);

#endif