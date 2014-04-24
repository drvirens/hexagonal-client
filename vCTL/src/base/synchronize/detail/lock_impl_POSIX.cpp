//
//  lock_impl_POSIX.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/23/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include <errno.h>
#include "base/synchronize/detail/lock_impl.h"
#include "base/logging/log.h"
#include "build/build_utils.h"

namespace vbase
{
namespace detail
{
  
  TLockImpl::TLockImpl()
  {
    int e = 0;
#if !defined(NDEBUG)
    pthread_mutexattr_t m;
    e = pthread_mutexattr_init(&m);
    if( 0 != e )
    {
      LOG_ERROR << "TLockImpl: pthread_mutexattr_init error: "  << strerror(e);
      //ha constructors cant return so use 2-phase construction later
    }
    e = pthread_mutexattr_settype(&m, PTHREAD_MUTEX_ERRORCHECK);
    if( 0 != e )
    {
      LOG_ERROR << "TLockImpl: pthread_mutexattr_settype error: "  << strerror(e);
    }
    e = pthread_mutex_init(&mNativeLock, &m);
    if( 0 != e )
    {
      LOG_ERROR << "TLockImpl: pthread_mutex_init error: " << strerror(e);
    }
    e = pthread_mutexattr_destroy(&m);
    if( 0 != e )
    {
      LOG_ERROR << "TLockImpl: pthread_mutexattr_destroy error: " << strerror(e);
    }
#else
    e = pthread_mutex_init(&mNativeLock, 0);
    if( 0 != e )
    {
      LOG_ERROR << "TLockImpl: pthread_mutex_init error: "  << strerror(e);
    }
#endif
  }
  TLockImpl::~TLockImpl()
  {
    int e = pthread_mutex_destroy(&mNativeLock);
    if( 0 != e )
    {
      LOG_ERROR << "TLockImpl: pthread_mutex_destroy error: "  << strerror(e);
    }
  }
  bool TLockImpl::DoTry()
  {
    int e = pthread_mutex_trylock(&mNativeLock);
    if( 0 != e && EBUSY != e )
    {
      LOG_ERROR << "TLockImpl: pthread_mutex_trylock error: "  << strerror(e);
    }
    return (0 == e);
  }
  void TLockImpl::DoLock()
  {
    int e = pthread_mutex_lock(&mNativeLock);
    if( 0 != e )
    {
      LOG_ERROR << "TLockImpl: pthread_mutex_lock error: "  << strerror(e);
    }
  }
  void TLockImpl::DoUnLock()
  {
    int e = pthread_mutex_unlock(&mNativeLock);
    if( 0 != e )
    {
      LOG_ERROR << "TLockImpl: pthread_mutex_unlock error: "  << strerror(e);
    }
  }
  
} //vbase
} //detail