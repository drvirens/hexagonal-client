//
//  condition_variable.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/24/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__condition_variable__
#define __vClientTemplateLib__condition_variable__

#include "base/non_copyable.h"
#include "base/thread/thread_platform.h"

namespace vbase
{
  class TLock;
namespace detail
{
  class CConditionVariableImpl;
}

  class TConditionVariable : private TNonCopyable<TConditionVariable>
  {
  public:
    explicit TConditionVariable(TLock* aLock);
    ~TConditionVariable();
    void Wait();
    void NotifyOne();
    void NotifyAll();
    
  private:
    detail::CConditionVariableImpl* mImpl;
  };
  
} //namespace vbase

#endif /* defined(__vClientTemplateLib__condition_variable__) */
