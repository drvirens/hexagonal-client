//
//  thread_loopful_UNIT_TEST.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/4/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//


#include <string>
#include "base/thread/thread_loopful.h"
#include "base/lambda/lambda_functor.h"
#include "base/lambda/lambda.h"
#include "base/non_copyable.h"
#include "3p/google/gtest/include/gtest/gtest.h"

namespace vbase
{

TEST(UT_TThread, Trivial)
    {
    std::string tname("UT_TThread");
    TThread thread(tname);
    thread.Start();
    }

} // namespace vbase