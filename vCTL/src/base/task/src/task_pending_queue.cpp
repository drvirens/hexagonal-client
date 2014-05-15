//
//  task_pending_queue.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/30/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "base/task/task_pending_queue.h"
#include "build/build_utils.h"
#include "logging/log_logger.h"
#include "base/task/task_pending_q_listener.h"

namespace vbase
{

TPendingTasksQ::TPendingTasksQ(ITaskPendingQueueListener& aTaskListListener)
    : iLock()
    , iPendingTasksQ()
    , iUniqueNumber(0)
    , iOurListener(&aTaskListListener)
    {
    }

TPendingTasksQ::~TPendingTasksQ()
    {
    
    }

bool TPendingTasksQ::Add(CLambda& aLambda, const TTimeDelta& aDelay)
    {
    TAutoLock lock( iLock );
    TTask task(aLambda);
    return DoAdd(&task);
    }

bool TPendingTasksQ::DoAdd(TTask* aTask)
    {
    bool ret = false;
    ASSERT( aTask != 0 );
    iLock.AssertAcquired();
    
    ++iUniqueNumber;
    aTask->SetUniqueId(iUniqueNumber);
    
    iPendingTasksQ.push( *aTask );
    iOurListener->OnTaskAdded(aTask);
    
    return ret;
    }
    
void TPendingTasksQ::PourAllTasksInto(TTaskQueue& aQueue)
    {
    ASSERT(aQueue.empty());
    
    TAutoLock lock( iLock );
    if(!iPendingTasksQ.empty())
        {
        iPendingTasksQ.Swap(&aQueue); //O(1)
        }
    ASSERT(iPendingTasksQ.empty());
    }
    
void TPendingTasksQ::WillDeleteEventDispatcherOfThisThread()
    {
    TAutoLock lock( iLock );
    }
    
} //namespace vbase
