//
//  lock.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/23/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__lock__
#define __vClientTemplateLib__lock__

#include "build/build_config.h"
#include "base/non_copyable.h"
#include "base/synchronize/detail/lock_impl.h" //this breaks DIP (dependency-inversion-principle), but we want to keep all the threading-sync module as compact as possible
#include "base/thread/thread_platform.h"

namespace vbase
{

namespace detail
{
  class MConditionVariablePosixImpl;
}
  
// ------------------------------------------------- TLock
  class TLock : private TNonCopyable<TLock>
  {
  public:
    TLock();
    ~TLock();
    void Acquire();
    void Release();
    bool Try();
    void AssertAcquired() const;
    
  private:
    detail::TLockImpl mImpl;
    
#if !defined(NDEBUG)
    void CheckHeldAndUnMark();
    void CheckUnHeldAndMark();
  
    bool mOwnedByThread;               //am I owned by any thread?
    TPlatformThreadID mOwningThreadId; //if yes, who owes me?
#endif

#if defined(V_PLATFORM_POSIX)
    friend class detail::MConditionVariablePosixImpl;
#endif

  };
  
// ------------------------------------------------- TAutoLock
  class TAutoLock //lock-RAII
  {
  public:
    explicit TAutoLock(TLock& aLock)
      : mLock(aLock)
    {
      mLock.Acquire();
    }
    ~TAutoLock()
    {
      mLock.AssertAcquired();
      mLock.Release();
    }
  private:
    TLock& mLock;
  };
}

#endif /* defined(__vClientTemplateLib__lock__) */
