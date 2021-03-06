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
#include "base/task/task_queue.h"
#include "base/eventdispatcher/event_dispatcher_destructor_spectator.h"

namespace vbase
{

class TTimeDelta;
class CLambda;
class ITaskPendingQueueListener;

class TPendingTasksQ : public TNonCopyable<TPendingTasksQ>, public IEventDispatcherDestructorSpectator
    {
public:
    explicit TPendingTasksQ(ITaskPendingQueueListener& aTaskListListener);
    virtual ~TPendingTasksQ();
    bool Add(CLambda& aLambda, const TTimeDelta& aDelay);
    void PourAllTasksInto(TTaskQueue& aQueue);
    size_t Size() const { return iPendingTasksQ.size(); }
    
    virtual void WillDeleteEventDispatcherOfThisThread();
    
private:
    bool DoAdd(TTask* aTask);
    
private:
    TLock iLock; //locks iPendingTasksQ
    TTaskQueue iPendingTasksQ;
    int iUniqueNumber;
    ITaskPendingQueueListener* iOurListener;
    };
    
} //namespace vbase

#endif /* defined(__vClientTemplateLib__task_pending_queue__) */
