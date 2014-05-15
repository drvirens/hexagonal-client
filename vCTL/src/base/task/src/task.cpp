//
//  task.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/30/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "base/task/task.h"

namespace vbase
{

TTask::TTask(CLambda& aLambda)
    : iUniqueId(-1) //not used currently
    , iTaskName("") //not used currently
    , iLambda(aLambda) //copy-ctor of tlambda
    {}

TTask::~TTask()
    {}
//    
//TTask::TTask(const TTask& aRhs)
//    {
//    if( &aRhs != this )
//        {
//        iUniqueId = aRhs.iUniqueId)
//        iTaskName = aRhs.iTaskName)
//        iLambda(aRhs.iLambda);
//        }
//    }
//    
//void TTask::Execute()
//    {
//    iLambda->Run();
//    }
//

//class Foo : public CLambda{
//public:
//void Run(int& a)
//    {
//    }
//    };

void TTask::Execute()
    {
    iLambda.Run();
    }
   
} //namespace vbase


