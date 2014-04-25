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
#include "base/logging/log.h"
#include "base/error_handler.h"

namespace vbase
{
namespace detail
{

MConditionVariablePosixImpl::MConditionVariablePosixImpl(TLock* aLock)
  : mMutex(aLock->mImpl.GetHandle())
{
  //Research Android support for support for this
  V_PTHREAD_CALL( pthread_cond_init(&mCondition, 0) );
}

MConditionVariablePosixImpl::~MConditionVariablePosixImpl()
{
  V_PTHREAD_CALL( pthread_cond_destroy(&mCondition) );
}

void MConditionVariablePosixImpl::DoWait()
{
  V_PTHREAD_CALL( pthread_cond_wait(&mCondition, mMutex) );
}

void MConditionVariablePosixImpl::DoNotifyOne()
{
  V_PTHREAD_CALL( pthread_cond_signal(&mCondition) );
}

void MConditionVariablePosixImpl::DoNotifyAll()
{
  V_PTHREAD_CALL( pthread_cond_broadcast(&mCondition) );
}


} //namespace detail
} //namespace vbase