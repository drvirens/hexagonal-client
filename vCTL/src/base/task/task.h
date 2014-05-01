//
//  task.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/30/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__task__
#define __vClientTemplateLib__task__

#include <queue>
#include <string>

#include "base/task/task_lambda.h"

namespace vbase
{

class TTask
    {
public:
    TTask(const TLambda& aLambda);
    ~TTask();
    TTask(const TTask& aRhs);
    void SetUniqueId(int aUniqueId) { iUniqueId = aUniqueId; }
    int UniqueId() const { return iUniqueId; }
        
private:
    int iUniqueId;
    std::string iTaskName;
    TLambda iLambda;
    };
    
typedef std::queue<TTask> TTaskQueue;

} //namespace vbase

#endif /* defined(__vClientTemplateLib__task__) */
