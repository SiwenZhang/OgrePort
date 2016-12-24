//
//  any.h
//  DownloadEngine
//
//  Created by liu enbao on 12/2/16.
//  Copyright © 2016 xb. All rights reserved.
//

#ifndef ANY_H
#define ANY_H

// can be replaced by other error mechanism
#include <cassert>
#define SHARED_ASSERT(x)    assert(x)

class Any
{
public: // structors
    
    Any()
    : content(0)
    {
    }
    
    template<typename ValueType>
    Any(const ValueType & value)
    : content(new holder<ValueType>(value))
    {
    }
    
    Any(const Any & other)
    : content(other.content ? other.content->clone() : 0)
    {
    }
    
    ~Any()
    {
        delete content;
    }
    
public: // modifiers
    
    Any & swap(Any & rhs)
    {
        std::swap(content, rhs.content);
        return *this;
    }
    
    template<typename ValueType>
    Any & operator=(const ValueType & rhs)
    {
        Any(rhs).swap(*this);
        return *this;
    }
    
    Any & operator=(Any rhs)
    {
        rhs.swap(*this);
        return *this;
    }
    
public: // queries
    
    bool empty() const
    {
        return !content;
    }
    
    const std::type_info & type() const
    {
        return content ? content->type() : typeid(void);
    }
    
public: // types (public so any_cast can be non-friend)
    
    class placeholder
    {
    public: // structors
        
        virtual ~placeholder()
        {
        }
        
    public: // queries
        
        virtual const std::type_info & type() const = 0;
        
        virtual placeholder * clone() const = 0;
        
    };
    
    template<typename ValueType>
    class holder : public placeholder
    {
    public: // structors
        
        holder(const ValueType & value)
        : held(value)
        {
        }
        
    public: // queries
        
        virtual const std::type_info & type() const
        {
            return typeid(ValueType);
        }
        
        virtual placeholder * clone() const
        {
            return new holder(held);
        }
        
    public: // representation
        
        ValueType held;
        
    private: // intentionally left unimplemented
        holder & operator=(const holder &);
    };
    
public:
    
    placeholder * content;
    
};

template<typename ValueType>
ValueType any_cast(const Any& operand)
{
//    SHARED_ASSERT( operand.type() == typeid(ValueType) );
    return static_cast<Any::holder<ValueType> *>(operand.content)->held;
}

#endif /* any_h */
