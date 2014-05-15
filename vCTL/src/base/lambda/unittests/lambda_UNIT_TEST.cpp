//
//  lambda_UNIT_TEST.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/14/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//


#include "base/eventdispatcher/event_dispatcher.h"
#include "base/lambda/lambda.h"
#include "base/thread/thread_loopless.h"
#include "3p/google/gtest/include/gtest/gtest.h"

namespace vbase
{

class MyLambda : public CLambda
    {
public:
    MyLambda() {}
    int Value() const
        {
        return iTester;
        }

private:
    virtual void DoRun()
        {
        iTester = 69;
        }
        
private:
    int iTester;
    };

TEST(UT_CLambda, Trivial)
    {
    CLambda* lambda = new MyLambda();
    lambda->Run();
    EXPECT_EQ(69, ((MyLambda*)lambda)->Value());
    }

}
