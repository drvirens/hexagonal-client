//
//  semaphore_impl.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/11/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "build/build_config.h"

#if defined(V_PLATFORM_DARWIN)

#include <string.h>
#include <errno.h>
#include "base/synchronize/detail/semaphore_impl.h"
#include "base/thread_syn_logger/macrologger.h"
#include "base/synchronize/detail/semaphore_impl_compatible_POSIX.h"

namespace vbase
{
namespace detail
{

TSemaphoreImpl::TSemaphoreImpl(TSemaphoreValue aValue)
    : iPosixSemaphore(0)
    {
    iPosixSemaphore = new TSemaphorePosixCompatible(aValue);
    }
    
TSemaphoreImpl::~TSemaphoreImpl()
    {
    delete iPosixSemaphore; iPosixSemaphore = 0;
    }
    
void TSemaphoreImpl::DoWait()
    {
    iPosixSemaphore->DoWait();
    }

// sem_trywait() is similar to sem_wait() except that if the
// semaphore value is not greater than 0, it returns an error.
bool TSemaphoreImpl::DoTryWait()
    {
    //return ( sem_trywait(&iSemaphore) == 0 );
    return false;
    }
    
void TSemaphoreImpl::DoSignal()
    {
    iPosixSemaphore->DoSignal();
    }

bool TSemaphoreImpl::DoGetValue(int& aValue) const
    {
//    int e; // = sem_getvalue(&iSemaphore, &aValue);
//    if( e != 0 )
//        {
////        KERNEL_LOG_ERROR("sem_post ERROR: %s", strerror(errno));
//        return false;
//        }
//    return true;
    
    return false;
    }

} //namespace vbase
} //namespace detail

#endif //V_PLATFORM_DARWIN
