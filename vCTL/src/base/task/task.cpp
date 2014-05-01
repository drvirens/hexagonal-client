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
    TTask::TTask()
        : iUniqueId(-1) //not used currently
        , iTaskName("") //not used currently
        {}
    
    TTask::~TTask()
        {}
        
    TTask::TTask(const TTask& aRhs)
        : iUniqueId(aRhs.iUniqueId)
        , iTaskName(aRhs.iTaskName)
        {}
}
