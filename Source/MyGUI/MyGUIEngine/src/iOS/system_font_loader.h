//
//  system_font_loader.h
//  mygui
//
//  Created by liu enbao on 12/24/16.
//  Copyright © 2016 liu enbao. All rights reserved.
//

#ifndef system_font_loader_h
#define system_font_loader_h

#include <string>

bool loadsystemfontData(const std::string& fontname, uint8_t*& stream, size_t& totalSize);

#endif /* system_font_loader_h */
