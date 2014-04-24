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
    LOG_ERROR << "pthread_cond_init error: " << strerror(e);
  }
}

MConditionVariablePosixImpl::~MConditionVariablePosixImpl()
{
  int e = pthread_cond_destroy(&mCondition);
  if( 0 != e )
  {
    LOG_ERROR << "pthread_cond_destroy error: " << strerror(e);
  }
}

void MConditionVariablePosixImpl::DoWait()
{
  int e = pthread_cond_wait(&mCondition, mMutex);
  if( 0 != e )
  {
    LOG_ERROR << "pthread_cond_wait error: " << strerror(e);
  }
}

void MConditionVariablePosixImpl::DoNotifyOne()
{
  int e = pthread_cond_signal(&mCondition);
  if( 0 != e )
  {
    LOG_ERROR << "pthread_cond_signal error: " << strerror(e);
  }
}

void MConditionVariablePosixImpl::DoNotifyAll()
{
  int e = pthread_cond_broadcast(&mCondition);
  if( 0 != e )
  {
    LOG_ERROR << "pthread_cond_brodcast error: " << strerror(e);
  }
}


} //namespace detail
} //namespace vbase