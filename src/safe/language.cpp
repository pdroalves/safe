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

#include "language.hpp"
#include <iostream>

/////////////////////////
// Specific exceptions //
/////////////////////////

// struct InvalidLanguage: public std::runtime_error{
//   InvalidLanguage()
//   {

//   }
//   InvalidLanguage(std::string const& message)
//       : std::runtime_error(message + " Was thrown")
//   {}
// } InvalidLanguage;

// struct UnknownPhrase: public std::runtime_error{
//   UnknownPhrase()
//   {
    
//   }
//   UnknownPhrase(std::string const& message)
//       : std::runtime_error(message + " Was thrown")
//   {}
// } UnknownPhrase;

/////////////////////////
/////////////////////////


PhraseMap phrase_map;

/**
 * Defines the default language used by get_phrase()
 * @int l - supported_language value
 */
void set_language(int l){
  // Verifies if "l" is a valid language pack
  // if(l < 0 || l >= LEN_SUPPORTED_LANGUAGES)
    // throw InvalidLanguage((char)l);

  // Load the input file
  TiXmlDocument lang;
  lang.LoadFile(language_files[l]);  
  // assert(lang);

  TiXmlHandle hDoc(&lang);
  TiXmlElement* pElem;

  phrase_map.clear(); // trash existing table

  // Iterate through elements inside "Phrases" and stores each one in the map object
  pElem = hDoc.FirstChild( "Safe" ).FirstChild("Phrases").FirstChild().Element();
  for( pElem; pElem; pElem=pElem->NextSiblingElement())
  {
    const char *pKey=pElem->Value();
    const char *pText=pElem->GetText();
    if (pKey && pText) 
    {
      phrase_map[pKey] = pText;
      std::cout << pKey << " = " << pText << std::endl;
    }
  }
}

/**
 * Returns a arbitrarily string 
 * @param  token - A token relative to the desired phrase
 * @return      - A phrase relative to "code" and to the language set
 */
std::string get_phrase(std::string token){
  PhraseIterator it = phrase_map.find(token);
  if(it != phrase_map.end()){
    // Found it
    return it->second;
  }else{
    // Didn't found it
    // throw UnknownPhrase(token);
    throw std::invalid_argument(token + " phrase not found.");
  }
}