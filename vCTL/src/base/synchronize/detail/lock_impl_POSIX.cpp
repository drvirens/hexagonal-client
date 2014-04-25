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
#include "base/error_handler.h"


namespace vbase
{
namespace detail
{
  
  TLockImpl::TLockImpl()
  {
#if !defined(NDEBUG)
    pthread_mutexattr_t m;
    V_PTHREAD_CALL( pthread_mutexattr_init(&m) );
    V_PTHREAD_CALL( pthread_mutexattr_settype(&m, PTHREAD_MUTEX_ERRORCHECK) );
    V_PTHREAD_CALL( pthread_mutex_init(&mNativeLock, &m) );
    V_PTHREAD_CALL( pthread_mutexattr_destroy(&m) );
#else
    V_PTHREAD_CALL( pthread_mutex_init(&mNativeLock, 0) );
#endif
  }
  TLockImpl::~TLockImpl()
  {
    V_PTHREAD_CALL( pthread_mutex_destroy(&mNativeLock) );
  }
  bool TLockImpl::DoTry()
  {
    int e = 0;
    V_PTHREAD_CALL_RET_ERROR( pthread_mutex_trylock(&mNativeLock), e );
    return (0 == e);
  }
  void TLockImpl::DoLock()
  {
    V_PTHREAD_CALL( pthread_mutex_lock(&mNativeLock) );
  }
  void TLockImpl::DoUnLock()
  {
    V_PTHREAD_CALL( pthread_mutex_unlock(&mNativeLock) );
  }
  
} //vbase
} //detail