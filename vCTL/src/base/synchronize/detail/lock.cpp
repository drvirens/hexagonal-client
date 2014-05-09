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
#if !defined(NDEBUG)
    mOwnedByThread = false;
    mOwningThreadId = kNoThreadId;
    iThreadName = "";
#endif
    }

TLock::~TLock()
    {
#if !defined(NDEBUG)
    ASSERT( !mOwnedByThread ); //should not be owned by any thread when exitting
    ASSERT( kNoThreadId == mOwningThreadId );
#endif
    }

void TLock::Acquire()
    {
    mImpl.DoLock();
#if !defined(NDEBUG)
    CheckUnHeldAndMark();
#endif
    }

void TLock::Release()
    {
#if !defined(NDEBUG)
    CheckHeldAndUnMark();
#endif
    mImpl.DoUnLock();
    }

bool TLock::Try()
    {
    bool r = mImpl.DoTry();
#if !defined(NDEBUG)
    if( r )
        {
        CheckUnHeldAndMark();
        }
#endif
    return r;
    }

void TLock::AssertAcquired() const
    {
#if !defined(NDEBUG)
    ASSERT( mOwnedByThread == true );
    ASSERT( mOwningThreadId == TPlatformThread::CurrentID() );
#endif
    }

#if !defined(NDEBUG)
void TLock::CheckHeldAndUnMark()
    {
    ASSERT( mOwnedByThread == true );
    ASSERT( mOwningThreadId == TPlatformThread::CurrentID() );
    mOwnedByThread = false;
    mOwningThreadId = kNoThreadId;
    }

void TLock::CheckUnHeldAndMark()
    {
    ASSERT( mOwnedByThread == false );
    mOwnedByThread = true;
    mOwningThreadId = TPlatformThread::CurrentID();
    iThreadName = TPlatformThread::Name();
    }
#endif
    
} //namespace vbase
