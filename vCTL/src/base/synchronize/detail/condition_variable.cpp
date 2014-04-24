//
//  condition_variable.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/24/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "base/synchronize/condition_variable.h"
#include "base/synchronize/detail/condition_variable_impl.h"
#include "base/synchronize/lock.h"
#include "build/build_utils.h" //mainly for ASSERT

namespace vbase
{

  TConditionVariable::TConditionVariable(TLock* aLock)
    : mImpl(0)
  {
#if defined(V_PLATFORM_POSIX)
    mImpl = new detail::MConditionVariablePosixImpl(aLock);
#elif defined(V_PLATFORM_WIN)
#endif
  }
  
  TConditionVariable::~TConditionVariable()
  {
    delete mImpl; mImpl = 0;
  }
  
  void TConditionVariable::Wait()
  {
    mImpl->DoWait();
  }
  
  void TConditionVariable::NotifyOne()
  {
    mImpl->DoNotifyOne();
  }
  
  void TConditionVariable::NotifyAll()
  {
    mImpl->DoNotifyAll();
  }
  
  
} //namespace vbase

