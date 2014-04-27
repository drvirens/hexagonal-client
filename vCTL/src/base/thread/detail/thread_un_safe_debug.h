//
//  thread_un_safe_debug.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/26/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__thread_un_safe_debug__
#define __vClientTemplateLib__thread_un_safe_debug__

#include "base/thread/thread_platform.h"
#include "base/synchronize/lock.h"

namespace vbase
{

class TThreadUnSafe_Debug
{
public:
  TThreadUnSafe_Debug();
  ~TThreadUnSafe_Debug();
  bool AssertValidThreadCall();
  void DisOwnThread();
private:
  void CheckThreadIdAssigned() const;
private:
  //CheckThreadIdAssigned() is const and AutoLock does not have any ctor with const Lock&
  mutable TLock mLock; //protects mValidThreadId
  mutable TPlatformThreadID mValidThreadId;
};

} //namespace vbase

#endif /* defined(__vClientTemplateLib__thread_un_safe_debug__) */
