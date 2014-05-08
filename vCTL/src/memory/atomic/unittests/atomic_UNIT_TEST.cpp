//
//  atomic_UNIT_TEST.c
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/7/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "memory/atomic/atomic.h"
#include "3p/google/gtest/include/gtest/gtest.h"

namespace vctl
{

TEST(UT_TAtomicOperation, Trivial)
    {
    TAtomicInt32 valuetoincrement = 68;
    TAtomicInt32 incrementbyamount = 1;
    TAtomicInt32 r = TAtomicOperation::BarrieredAtomicIncrement(&valuetoincrement, incrementbyamount);
    
    EXPECT_TRUE( r == 69);
    }

} //namespace vbase

