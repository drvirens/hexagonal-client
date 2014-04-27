//
//  thread_un_safe_UNIT_TEST.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/26/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include <stdio.h>

#include "base/thread/thread_un_safe.h"
#include "base/thread/detail/thread_un_safe_debug.h"
#include "base/thread/detail/thread_un_safe_production.h"
#include "3p/google/gtest/include/gtest/gtest.h"

namespace vbase
{

  class MyThreadUnSafeClass : public TNotThreadSafe
  {
  public:
    MyThreadUnSafeClass()
    {
      
    }
    void Foo()
    {
      AssertValidThreadCall();
    }
    void DiwOwnThread()
    {
      DisOwnThread();
    }
  };
  
  TEST(UT_TThreadUnSafe, ThreadUnSafeTrivial)
  {
    TNotThreadSafe tud;
    tud.AssertValidThreadCall();
  }
  
  TEST(UT_TThreadUnSafe, DeriveFromThreadUnSafe)
  {
    MyThreadUnSafeClass t;
    t.Foo();
  }
  
} // namespace vbase