//
//  event_dispatcher.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/30/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "base/eventdispatcher/event_dispatcher.h"

namespace vbase
{

MEventDispatcher::~MEventDispatcher()
    {
        
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
    
bool MEventDispatcher::PerformWork()
    {
    return true;
    }
    
bool MEventDispatcher::PerformIdleWork()
    {
    return true;
    }
    
void MEventDispatcher::OnTaskAdded(TTask* aTask)
    {
        
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
    
void MEventDispatcher::ExecuteAsynch(const TLambda& aLambda)
    {
        
    }
    
void MEventDispatcher::ExecuteAsynchAfterDelay(const TLambda& aLambda, const TTimeDelta& aTimeDelta)
    {
        
        
    }
    
MEventDispatcher::MEventDispatcher()
    : iPendingTasksQ(*this)
    {
        
    }
    
void MEventDispatcher::Construct()
    {
        
    }

} //namespace vbase