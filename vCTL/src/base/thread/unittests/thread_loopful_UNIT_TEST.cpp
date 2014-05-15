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

//template <class T, typename OUTPUT>
//class Increment : public CLambda
//    {
//public:
//    Increment( T a, OUTPUT aOutput )
//        : iArgument(a)
//        , iOutput(aOutput)
//        {}
//    
//    //template<typename OUTPUT>
//    T operator() ( T& aValue, OUTPUT& aOutput )
//        {
//        aValue = aValue + iArgument;
//        aOutput = aValue;
//        return 1;
//        }
//        
//    virtual void Run()
//        {
//        *this(iArgument, iOutput);
//        }
//    
//private:
//    T iArgument;
//    OUTPUT iOutput;
//    };

/*
 Increment<int> addone(1);
    Assign<Increment, int> f(addone);
    
    std::vector<int> v;
    auto out = std::back_inserter(v);
    
    int i = 10;
    int ret = f(i, out);
*/

TEST(UT_TThread, DISABLED_Trivial)
    {
    std::string tname("UT_TThread");
    TThread thread(tname);
    thread.Start();
    //thread.Stop();
    //thread.Join();
//    
//    Increment<int> incre(10);
//    TAssign<Increment, int> functor(incre);
//    
//    CLambda lambda(functor);
//    
//    thread.FireAndForgetLambda(lambda);
    
    
    }

} // namespace vbase