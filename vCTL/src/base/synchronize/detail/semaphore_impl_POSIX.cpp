//
//  semaphore_impl.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/11/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "build/build_config.h"

#if defined(V_PLATFORM_LINUX)

#include <string.h>
#include <errno.h>
#include "base/synchronize/detail/semaphore_impl.h"
#include "base/thread_syn_logger/macrologger.h"

namespace vbase
{
namespace detail
{

static const int kSharedAmongProcesses = 0; //0 = not shared among processes

TSemaphoreImpl::TSemaphoreImpl(TSemaphoreValue aValue)
    {
    int e = sem_init(&iSemaphore, kSharedAmongProcesses, aValue);
    if( e != 0 ) 
        {
        KERNEL_LOG_ERROR("sem_init ERROR: %s", strerror(errno));
        }
    }
    
TSemaphoreImpl::~TSemaphoreImpl()
    {
    int e = sem_destroy(&iSemaphore);
    if( e != 0 )
        {
        KERNEL_LOG_ERROR("sem_destroy ERROR: %s", strerror(errno));
        }
    }
    
void TSemaphoreImpl::DoWait()
    {
    int e = sem_wait(&iSemaphore);
    if( e != 0 )
        {
        KERNEL_LOG_ERROR("sem_wait ERROR: %s", strerror(errno));
        }
    }

// sem_trywait() is similar to sem_wait() except that if the
// semaphore value is not greater than 0, it returns an error.
bool TSemaphoreImpl::DoTryWait()
    {
    return ( sem_trywait(&iSemaphore) == 0 );
    }
    
void TSemaphoreImpl::DoSignal()
    {
    int e = sem_post(&iSemaphore);
    if( e != 0 )
        {
        KERNEL_LOG_ERROR("sem_post ERROR: %s", strerror(errno));
        }
    }

bool TSemaphoreImpl::DoGetValue(int& aValue) const
    {
    int e = sem_getvalue(&iSemaphore, &aValue);
    if( e != 0 )
        {
        KERNEL_LOG_ERROR("sem_post ERROR: %s", strerror(errno));
        return false;
        }
    return true;
    }

} //namespace vbase
} //namespace detail

#endif //#if defined(V_PLATFORM_POSIX)

