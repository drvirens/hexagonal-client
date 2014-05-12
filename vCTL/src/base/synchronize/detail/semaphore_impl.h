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

namespace vbase
{

#if defined(V_PLATFORM_POSIX)
typedef unsigned int TSemaphoreValue;
#else //V_PLATFORM_POSIX
#error defined typedef for TSemaphoreValue
#endif

class TSemaphore;

namespace detail
{

#if defined(V_PLATFORM_POSIX)
    #include <sys/semaphore.h>

    typedef sem_t TNativeSemaphore;
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
    
private:
    TNativeSemaphore iSemaphore;
    };

} //namespace vbase
} //namespace detail

#endif /* defined(__vClientTemplateLib__semaphore_impl__) */
