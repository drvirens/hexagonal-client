//
//  lock_impl.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/23/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__lock_impl__
#define __vClientTemplateLib__lock_impl__

#include "build/build_config.h"

#if defined(V_PLATFORM_POSIX)
#include <pthread.h>
#if defined(V_PLATFORM_IOS)
#include <sys/types.h> //for pid_t
#endif
#elif defined(V_PLATFORM_WIN)
#include <windows.h>
#endif

#include "base/non_copyable.h"

namespace vbase
{
namespace detail
{
    // -------------------------------------------------------------- typedefs
#if defined(V_PLATFORM_POSIX)
  typedef pthread_mutex_t TNativeLock;
#elif defined(V_PLATFORM_WIN)
  typedef CRITICAL_SECTION TNativeLock;
#endif

  class TLockImpl : private TNonCopyable<TLockImpl>
  {
  public:
    TLockImpl();
    ~TLockImpl();
    
    bool DoTry();
    void DoLock();
    void DoUnLock();
    
  private:
    TNativeLock mNativeLock;
  };
  
} //namespace detail
} //namespace vbase

#endif /* defined(__vClientTemplateLib__lock_impl__) */
