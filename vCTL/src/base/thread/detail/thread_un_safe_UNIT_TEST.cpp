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
      TNotThreadSafe::AssertValidThreadCall();
    }
  };
  
  TEST(UT_TThreadUnSafe, ThreadUnSafeTrivial)
  {
    TNotThreadSafe tud;
    //TThreadUnSafe<TThreadUnSafe_Debug> tud;
    tud.AssertValidThreadCall();
  }
  
  TEST(UT_TThreadUnSafe, DeriveFromThreadUnSafe)
  {
    MyThreadUnSafeClass t;
  }
  
} // namespace vbase