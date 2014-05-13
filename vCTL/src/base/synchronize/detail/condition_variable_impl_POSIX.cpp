//
//  condition_variable_impl_POSIX.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/24/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include <errno.h>
#include "base/synchronize/lock.h"
#include "base/synchronize/detail/condition_variable_impl.h"
#include "base/error_handler.h"
#include "base/thread_syn_logger/macrologger.h"

namespace vbase
{
namespace detail
{

MConditionVariablePosixImpl::MConditionVariablePosixImpl(TLock* aLock)
    : mMutex(aLock->mImpl.GetHandle())
    {
    //Research Android support for support for this
    int e = pthread_cond_init(&mCondition, 0);
    if( 0 != e )
        {
        KERNEL_LOG_ERROR("pthread_cond_init error = [%s]", strerror(errno));
        }
    }

MConditionVariablePosixImpl::~MConditionVariablePosixImpl()
    {
    int e = pthread_cond_destroy(&mCondition);
    if( 0 != e )
        {
        KERNEL_LOG_ERROR("pthread_cond_destroy error = [%s]", strerror(errno));
        }
    }

void MConditionVariablePosixImpl::DoWait()
    {
    int e = pthread_cond_wait(&mCondition, mMutex);
    if ( 0 != e )
        {
        KERNEL_LOG_ERROR("pthread_cond_wait error = [%s]", strerror(errno));
        }
    }

void MConditionVariablePosixImpl::DoNotifyOne()
    {
    int e = pthread_cond_signal(&mCondition);
    if( 0 != e )
        {
        KERNEL_LOG_ERROR("pthread_cond_signal error = [%s]", strerror(errno));
        }
    }

void MConditionVariablePosixImpl::DoNotifyAll()
    {
    int e = pthread_cond_broadcast(&mCondition);
    if( 0 != e )
        {
        KERNEL_LOG_ERROR("pthread_cond_broadcast error = [%s]", strerror(errno));
        }
    }


} //namespace detail
} //namespace vbase