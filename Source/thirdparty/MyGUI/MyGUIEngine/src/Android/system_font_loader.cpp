//
//  system_font_loader.c
//  mygui
//
//  Created by liu enbao on 12/24/16.
//  Copyright © 2016 liu enbao. All rights reserved.
//

#include "system_font_loader.h"
#include <stdint.h>

//Reference:
//http://skia.googlecode.com/svn-history/r1473/trunk/src/ports/SkFontHost_mac_coretext.cpp

bool loadsystemfontData(const std::string& fontname, uint8_t*& stream, size_t& totalSize) {
    return false;
}
