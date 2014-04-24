//
//  condition_variable_impl.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/24/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_condition_variable_impl_h
#define vClientTemplateLib_condition_variable_impl_h

#include "base/non_copyable.h"
#include "build/build_config.h"

#if defined(V_PLATFORM_POSIX)
#include <pthread.h>
#elif defined(V_PLATFORM_WIN)
#include <windows.h>
#endif


namespace vbase
{
class TLock;
namespace detail
{
  
  class CConditionVariableImpl : private TNonCopyable<CConditionVariableImpl>
  {
  public:
    virtual ~CConditionVariableImpl() {}
    
    virtual void DoWait() = 0;
    virtual void DoNotifyOne() = 0;
    virtual void DoNotifyAll() = 0;
  };
  
#if defined(V_PLATFORM_POSIX)
  class MConditionVariablePosixImpl
    : public CConditionVariableImpl
    , private TNonCopyable<MConditionVariablePosixImpl>
  {
  public:
    explicit MConditionVariablePosixImpl(TLock* aLock);
    virtual ~MConditionVariablePosixImpl();
    
    virtual void DoWait();
    virtual void DoNotifyOne();
    virtual void DoNotifyAll();
  private:
    pthread_cond_t mCondition;
    pthread_mutex_t* mMutex;
  };
#elif defined(V_PLATFORM_WIN)
#endif
  
} //namespace detail
} //namespace vbase

#endif
