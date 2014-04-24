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

//NOTE: If your code is trying to depend on this detail, then you're doing
//      something wrong with your architecture. This compilation unit
//      is a detail, and hence should not be depended upon. Rather, use
//      the asbtraction for Lock defined in base/synchronize/lock.h
//CAVEAT: Per Dependency Inversion Principle: abstractions should not depend
//        on details, but the other way round i.e. details should depend
//        on abstractions. Since lock.h is supposed to be a "pure" interface(abstraction),
//        it should not include this file in it (detail). Currently, it does
//        and thus breaks the DIP. This needs to be fixed in future. But
//        until that is fixed, just make sure not to #include this file
//        anywhere in your code except lock-detail module

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
    
#if defined(V_PLATFORM_POSIX)
    TNativeLock* GetHandle() { return &mNativeLock; }
#endif
    
  private:
    TNativeLock mNativeLock;
  };
  
} //namespace detail
} //namespace vbase

#endif /* defined(__vClientTemplateLib__lock_impl__) */
