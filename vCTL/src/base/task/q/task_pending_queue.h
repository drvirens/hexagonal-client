//
//  task_pending_queue.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/30/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__task_pending_queue__
#define __vClientTemplateLib__task_pending_queue__

#include "base/non_copyable.h"
#include "base/task/task.h"
#include "base/synchronize/lock.h"

namespace vbase
{

class TTimeDelta;

//todo:
class TLambda
    {
        
    };

class TPendingTasksQ : public TNonCopyable<TPendingTasksQ>
    {
public:
    TPendingTasksQ(); //mainly for unit-testing
    virtual ~TPendingTasksQ();
    
    bool Add(const TLambda& aLambda, const TTimeDelta& aDelay);
private:
    TLock iLock; //locks iPendingTasksQ
    TTaskQueue iPendingTasksQ;
    };
    
} //namespace vbase

#endif /* defined(__vClientTemplateLib__task_pending_queue__) */
