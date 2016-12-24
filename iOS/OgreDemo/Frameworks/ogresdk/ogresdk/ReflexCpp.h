//
//  ReflexCpp.h
//  ogresdk
//
//  Created by liu enbao on 12/24/16.
//  Copyright © 2016 liu enbao. All rights reserved.
//

#ifndef REFLEX_CPP_H
#define REFLEX_CPP_H

#include <string>

#include "Any.h"

class ClassInfo;

//注册传入一个classInfo(类信息),将这个类的信息注册到映射中
bool Register(ClassInfo* ci);

//工厂生产对象的接口
Any CreateObject(std::string name);

typedef Any (*ObjectConstructorFn)(void);

class ClassInfo {
public:
    ClassInfo(const std::string& className, ObjectConstructorFn ctor)
    :m_className(className), m_objectConstructor(ctor) {
        //classInfo的构造函数是传入类名和类对应的new函数然后自动注册进map中。
        Register(this);
    }
    
    virtual ~ClassInfo() {
    
    }
    
    Any CreateObject() const {
        return m_objectConstructor ? (*m_objectConstructor)() : 0;
    }
    
    bool IsDynamic() const {
        return NULL != m_objectConstructor;
    }
    
    const std::string GetClassName() const {
        return m_className;
    }
    
    ObjectConstructorFn GetConstructor() const {
        return m_objectConstructor;
    }
public:
    std::string m_className;
    ObjectConstructorFn m_objectConstructor;
};

//类申明中添加 classInfo 属性 和 CreatObject、GetClassInfo 方法
#define DECLARE_CLASS(name) \
    protected: \
        static ClassInfo ms_classinfo; \
    public:  \
        virtual ClassInfo* GetClassInfo() const; \
        static Any CreateObject();

//实现CreatObject 和 GetClassInfo 的两个方法
#define IMPLEMENT_CLASS_COMMON(name,func) \
        ClassInfo name::ms_classinfo((#name), \
                             (ObjectConstructorFn) func); \
                                                        \
        ClassInfo *name::GetClassInfo() const \
        {return &name::ms_classinfo;}

//classInfo 属性的初始化
#define IMPLEMENT_CLASS(name)            \
        IMPLEMENT_CLASS_COMMON(name,name::CreateObject) \
            Any name::CreateObject()                   \
            { return new name;}

#endif /* REFLEX_CPP_H */
