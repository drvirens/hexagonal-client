    //
    //  thread_un_safe_debug.cpp
    //  vClientTemplateLib
    //
    //  Created by Virendra Shakya on 4/26/14.
    //  Copyright (c) 2014 Virendra Shakya. All rights reserved.
    //

#include "thread_un_safe_debug.h"

namespace vbase
{
    
    
TThreadUnSafe_Debug::TThreadUnSafe_Debug()
    : mValidThreadId(kInvalidThreadID)
    {
    CheckThreadIdAssigned();
    }

TThreadUnSafe_Debug::~TThreadUnSafe_Debug()
    {}

bool TThreadUnSafe_Debug::AssertValidThreadCall()
    {
    TAutoLock autoLock(mLock);
    CheckThreadIdAssigned();
    
    return ( mValidThreadId == TPlatformThread::CurrentID() );
    }

void TThreadUnSafe_Debug::DisOwnThread()
    {
    TAutoLock autoLock(mLock);
    mValidThreadId = kInvalidThreadID;
    }

void TThreadUnSafe_Debug::CheckThreadIdAssigned() const
    {
    //TAutoLock autoLock(mLock);
    if(mValidThreadId != kInvalidThreadID) //already assigned so return
        {
        return;
        }
    mValidThreadId = TPlatformThread::CurrentID();
}
    
} //namespace vbase
