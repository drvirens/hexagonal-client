//
//  semaphore_impl.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/11/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__semaphore_impl__
#define __vClientTemplateLib__semaphore_impl__

#include "build/build_config.h"
#include "base/non_copyable.h"
#include "base/synchronize/semaphore_value.h"

namespace vbase
{

class TSemaphore;

namespace detail
{

#if defined(V_PLATFORM_POSIX)
    
    #if defined(V_PLATFORM_DARWIN)
        class TSemaphorePosixCompatible;
    
    #elif defined(V_PLATFORM_ANDROID)
        #error Android Semaphore research for posix support
    #else //Posix
        #include <semaphore.h>
        typedef sem_t TNativeSemaphore;
    #endif
    
#elif defined(V_PLATFORM_WIN)
    #error define semaphore for windows. not implemented yet file: semaphore_impl.h
#endif

class TSemaphoreImpl : private TNonCopyable<TSemaphoreImpl>
    {
friend class vbase::TSemaphore;
private:
    explicit TSemaphoreImpl(TSemaphoreValue aValue);
    ~TSemaphoreImpl();
    
    void DoWait();
    bool DoTryWait();
    void DoSignal();
    
    bool DoGetValue(int& aValue) const;
    
private:
#if defined(V_PLATFORM_DARWIN)
    mutable TSemaphorePosixCompatible* iPosixSemaphore;
#else // #if defined(V_PLATFORM_DARWIN)
    mutable TNativeSemaphore iSemaphore;
#endif
    };

} //namespace vbase
} //namespace detail

#endif /* defined(__vClientTemplateLib__semaphore_impl__) */
