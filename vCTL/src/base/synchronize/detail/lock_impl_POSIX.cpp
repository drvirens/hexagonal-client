//
//  lock_impl_POSIX.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/23/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//
#include <string.h>
#include <errno.h>
#include "base/synchronize/detail/lock_impl.h"
#include "build/build_utils.h"
#include "base/error_handler.h"
#include "base/thread_syn_logger/macrologger.h"

namespace vbase
{
namespace detail
{

TLockImpl::TLockImpl()
    {
#if !defined(NDEBUG)
    pthread_mutexattr_t m;
    int e = pthread_mutexattr_init(&m);
    if( 0 != e )
        {
        KERNEL_LOG_ERROR("pthread_mutexattr_init error = [%s]", strerror(errno));
        }
        
    e = pthread_mutexattr_settype(&m, PTHREAD_MUTEX_ERRORCHECK) ;
    if( 0 != e )
        {
        KERNEL_LOG_ERROR("pthread_mutexattr_settype error = [%s]", strerror(errno));
        }

    e = pthread_mutex_init(&mNativeLock, &m);
    if( 0 != e )
        {
        KERNEL_LOG_ERROR("pthread_mutex_init error = [%s]", strerror(errno));
        }

    e = pthread_mutexattr_destroy(&m);
    if( 0 != e )
        {
        KERNEL_LOG_ERROR("pthread_mutexattr_destroy error = [%s]", strerror(errno));
        }

#else
    e = pthread_mutex_init(&mNativeLock, 0);
    if( 0 != e )
        {
        KERNEL_LOG_ERROR("pthread_mutex_init error = [%s]", strerror(errno));
        }
#endif
    }

TLockImpl::~TLockImpl()
    {
    int e =pthread_mutex_destroy(&mNativeLock);
    if( 0 != e )
        {
        KERNEL_LOG_ERROR("pthread_mutex_destroy error = [%s]", strerror(errno));
        }
    }

bool TLockImpl::DoTry()
    {
    int e = pthread_mutex_trylock(&mNativeLock);
    if( 0 != e )
        {
        KERNEL_LOG_ERROR("pthread_mutex_trylock error = [%s]", strerror(errno));
        }

    return (0 == e);
    }

void TLockImpl::DoLock()
    {
    int e = pthread_mutex_lock(&mNativeLock);
    if( 0 != e )
        {
        KERNEL_LOG_ERROR("pthread_mutex_lock error = [%s]", strerror(errno));
        }
    }

void TLockImpl::DoUnLock()
    {
    int e = pthread_mutex_unlock(&mNativeLock);
    if( 0 != e )
        {
        KERNEL_LOG_ERROR("pthread_mutex_unlock error = [%s]", strerror(errno));
        }
    }

} //vbase
} //detail