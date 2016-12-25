//
//  ReflexCpp.cpp
//  ogresdk
//
//  Created by liu enbao on 12/24/16.
//  Copyright © 2016 liu enbao. All rights reserved.
//

#include "ReflexCpp.h"

#include <map>

static std::map<std::string, ClassInfo*> *classInfoMap = NULL;

bool Register(ClassInfo* ci) {
    if (!classInfoMap) {
        //这里我们是通过map来存储这个映射的。
        classInfoMap = new std::map<std::string, ClassInfo*>();
    }

    if (ci) {
        if (classInfoMap->find(ci->m_className) == classInfoMap->end()) {
            // 类名 <-> classInfo
            classInfoMap->insert(std::map< std::string, ClassInfo*>::value_type(ci->m_className, ci));
        }
    }
    
    return true;
}

Any CreateObject(std::string name) {
    std::map< std::string, ClassInfo*>::const_iterator iter = classInfoMap->find(name);
    if (classInfoMap->end() != iter) {
        //当传入字符串name后,通过name找到info,然后调用对应的CreatObject()即可
        return iter->second->CreateObject();
    }
    return NULL;
}
