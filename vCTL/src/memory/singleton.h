//
//  singleton.h
//  Discount
//
//  Created by Virendra Shakya on 6/8/14.
//  Copyright (c) 2014 Justin. All rights reserved.
//

#ifndef Discount_singleton_h
#define Discount_singleton_h

#include "base/synchronize/lock.h"
#include "base/non_copyable.h"

namespace vctl
{

template <typename T>
class CSingleton : public TNonCopyable< CSingleton<T> >
    {
public:
    static T& Instance()
        {
        vbase::TAutoLock guard(iLock);
        T* instance = iInstance;
        if(!instance)
            {
            instance = new T();
            iInstance = instance;
            }
        return *instance;
        }
        
    static bool HasInstance()
        {
        vbase::TAutoLock guard(iLock);
        return iInstance != 0;
        }
        
protected:
    CSingleton() {}
    ~CSingleton() {}

private:
    static vbase::TLock iLock;
    static T* iInstance;
    };
    
#define SINGLETON_INSTANCE(T)       \
    template<> vbase::TLock vctl::CSingleton< T >::iLock; \
    template<> T* vctl::CSingleton< T >::iInstance(0); \
    template class vctl::CSingleton< T >;
    
}

#endif
