//
//  event_dispatcher.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/30/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "base/eventdispatcher/event_dispatcher.h"
#include "base/time/time.h"
#include "base/runloop/run_loop.h"
#include "base/runloop/run_loop_factory.h"

namespace vbase
{

MEventDispatcher::~MEventDispatcher()
    {
    delete iRunLoop;
    }
    
MEventDispatcher* MEventDispatcher::New()
    {
    MEventDispatcher* obj = new MEventDispatcher();
    if( obj )
        {
        obj->Construct();
        }
    return obj;
    }
    
void MEventDispatcher::ExecuteAsynch(const TLambda& aLambda)
    {
    vbase::TTimeDelta delay(0);
    iPendingTasksQ.Add(aLambda, delay);
    }

void MEventDispatcher::ExecuteAsynchAfterDelay(const TLambda& aLambda, const TTimeDelta& aTimeDelta)
    {
    vbase::TTimeDelta delay(0);
    iPendingTasksQ.Add(aLambda, delay);
    }

MEventDispatcher::MEventDispatcher()
    : iWorkLoadItemsQ()
    , iPendingTasksQ(*this)
    , iRunLoop(0)
    {
    LOG_INFO << "MEventDispatcher ctor";
    }

void MEventDispatcher::Construct()
    {
    iRunLoop = TRunLoopFactory::PlatformRunLoop();
    ASSERT(iRunLoop); //todo: make this as scoped ptr
    }

void MEventDispatcher::Run()
    {
    if(iRunLoop)
        {
        iRunLoop->Run(this); //start spinning the runloop. calls PerformWork() when sources are attached to runloop
        }
    }
    
void MEventDispatcher::LoadTasks()
    {
    if(iWorkLoadItemsQ.empty())
        {
        iPendingTasksQ.PourAllTasksInto(iWorkLoadItemsQ);
        }
    }
    
bool MEventDispatcher::HasTasksToExecute() const
    {
    return iWorkLoadItemsQ.empty() ? false : true;
    }

bool MEventDispatcher::DoExecuteTask(TTask& aTask)
    {
    bool ret = true;
    aTask.Execute();
    return ret;
    }
    
bool MEventDispatcher::PerformWork()
    {
    //while 2 loops? in future, we are going to support delayed tasks
    bool ret = false;
    for(;;)
        {
        LoadTasks();
        if(!HasTasksToExecute())
            {
            ret = false;
            break;
            }
            
        while(HasTasksToExecute())
            {
            TTask task = iWorkLoadItemsQ.front();
            iWorkLoadItemsQ.pop();
            
            ret = DoExecuteTask(task);
            if(ret)
                {
                return ret;
                }
            }
        }
    return ret;
    }
    
bool MEventDispatcher::PerformIdleWork()
    {
    return true;
    }
    
void MEventDispatcher::ScheduleWork()
    {
    //ASSERT(iRunLoop != 0);
    if(iRunLoop)
        {
        //iRunLoop->Run(this);
        iRunLoop->ScheduleWork();
        }
    }
    
void MEventDispatcher::OnTaskAdded(TTask* aTask)
    {
//    ASSERT(aTask != 0);
    //clients can start adding tasks into the queue even before the loop is ready.
    //this is valid.
    
    if(aTask)
        {
        ScheduleWork();
        }
    }
    
void MEventDispatcher::OnTaskRemoved(TTask* aTask)
    {
        
    }
    
void MEventDispatcher::RegisterDestructorSpectator(const IEventDispatcherDestructorSpectator& aSpectator)
    {
        
    }
    
void MEventDispatcher::UnRegisterDestructorSpectator(const IEventDispatcherDestructorSpectator& aSpectator)
    {
        
    }
    
void MEventDispatcher::RegisterTaskSpectator(const ITaskSpectator& aSpectator)
    {
        
    }
    
void MEventDispatcher::UnRegisterTaskSpectator(const ITaskSpectator& aSpectator)
    {
        
    }
    
} //namespace vbase