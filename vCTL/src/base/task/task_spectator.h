//
//  task_spectator.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/1/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_task_spectator_h
#define vClientTemplateLib_task_spectator_h

namespace vbase
{

class TTask;

class ITaskSpectator
    {
public:
    virtual void WillExecuteTask(const TTask& aTask) = 0;
    virtual void DidExecuteTask(const TTask& aTask) = 0;
    
protected:
    virtual ~ITaskSpectator(){} //TODO: not good practice: always put virtual destructor in a cpp compilation unit to give avoid compiler a hint and avoid out-of-line copies (causing code bloat)
    };

} //namespace vbase

#endif
