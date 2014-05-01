//
//  task_pending_q_listener.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/30/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_task_pending_q_listener_h
#define vClientTemplateLib_task_pending_q_listener_h

namespace vbase
{

class TTask;
    
class ITaskPendingQueueListener
    {
public:
    virtual ~ITaskPendingQueueListener() {}
    virtual void OnTaskAdded(TTask* aTask) = 0;
    virtual void OnTaskRemoved(TTask* aTask) = 0;
    };

} //namespace vbase

#endif