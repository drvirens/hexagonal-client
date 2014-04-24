//
//  lock_impl.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/23/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "base/synchronize/lock.h"
#include "build/build_utils.h" //mainly for ASSERT

namespace vbase
{

const TPlatformThreadID kNoThreadId = static_cast<TPlatformThreadID>(0);
  
  TLock::TLock()
    : mImpl()
  {
#if defined(DEBUG)
    mOwnedByThread = false;
    mOwningThreadId = kNoThreadId;
#endif
  }
  
  TLock::~TLock()
  {
#if defined(DEBUG)
    ASSERT( !mOwnedByThread ); //should not be owned by any thread when exitting
    ASSERT( kNoThreadId == mOwningThreadId );
#endif
  }
  
  void TLock::Acquire()
  {
    mImpl.DoLock();
#if defined(DEBUG)
    CheckUnHeldAndMark();
#endif
  }
  
  void TLock::Release()
  {
#if defined(DEBUG)
    CheckHeldAndUnMark();
#endif
    mImpl.DoUnLock();
  }
  
  bool TLock::Try()
  {
    bool r = mImpl.DoTry();
#if defined(DEBUG)
    if( r )
    {
      CheckUnHeldAndMark();
    }
#endif
    return r;
  }
  
  void TLock::AssertAcquired() const
  {
#if defined(DEBUG)
#else
//do nothing
#endif
  }
  
#if defined(DEBUG)
  void TLock::CheckHeldAndUnMark()
  {
    mOwnedByThread = false;
    mOwningThreadId = kNoThreadId;
  }
  
  void TLock::CheckUnHeldAndMark()
  {
    mOwnedByThread = true;
    mOwningThreadId = TPlatformThread::CurrentID();
  }
#endif

} //namespace vbase
