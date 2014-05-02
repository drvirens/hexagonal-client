//
//  event_dispatcher.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/30/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__event_dispatcher__
#define __vClientTemplateLib__event_dispatcher__

#include "base/non_copyable.h"
#include "base/runloop/run_loop.h"
#include "base/task/task_pending_q_listener.h"
#include "base/eventdispatcher/event_dispatcher_destructor_spectator.h"
#include "base/task/task_queue.h"
#include "base/task/task_pending_queue.h"

namespace vbase
{

class TLambda;
class TTimeDelta;
class ITaskSpectator;

class MEventDispatcher
    : public IWorkLoad
    , public ITaskPendingQueueListener
    , public TNonCopyable<MEventDispatcher>
    {
public:
    virtual ~MEventDispatcher();
    static MEventDispatcher* New();
    
    // IWorkLoad contract
    virtual bool PerformWork();
    virtual bool PerformIdleWork();
    
    // ITaskPendingQueueListener contract
    virtual void OnTaskAdded(TTask* aTask);
    virtual void OnTaskRemoved(TTask* aTask);
    
    void RegisterDestructorSpectator(const IEventDispatcherDestructorSpectator& aSpectator);
    void UnRegisterDestructorSpectator(const IEventDispatcherDestructorSpectator& aSpectator);
    
    void RegisterTaskSpectator(const ITaskSpectator& aSpectator);
    void UnRegisterTaskSpectator(const ITaskSpectator& aSpectator);
    
    void ExecuteAsynch(const TLambda& aLambda);
    void ExecuteAsynchAfterDelay(const TLambda& aLambda, const TTimeDelta& aTimeDelta);
    
    void ScheduleWork();
    
protected:
    MEventDispatcher();
    void Construct();
    void LoadTasks();
    bool HasTasksToExecute() const;
    bool DoExecuteTask(TTask& aTask);
    
private:
    
    
private:
    TTaskQueue iWorkLoadItemsQ; //tots internally
    TPendingTasksQ iPendingTasksQ; //client facings q that accepts and stores the tasks in it
    IRunLoopBase* iRunLoop;
    };
    
} //namespace vbase



#endif /* defined(__vClientTemplateLib__event_dispatcher__) */
