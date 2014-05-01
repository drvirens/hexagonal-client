//
//  run_loop.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/26/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__run_loop__
#define __vClientTemplateLib__run_loop__

#include "base/thread/thread_un_safe.h"

namespace vbase
{

class IWorkLoad
    //
    // Typically, one work-load will have multiple tasks in it
    //
    {
public:
    virtual ~IWorkLoad() {}
    virtual bool PerformWork() = 0;
    virtual bool PerformIdleWork() = 0;
    };


class IRunLoopBase : public TNotThreadSafe
    {
public:
    virtual ~IRunLoopBase() {}
    virtual void Run(IWorkLoad* aWorkLoad) = 0;
    virtual void Stop() = 0; //can only be called from thread that called Run()
    virtual void ScheduleWork() = 0;
    };
    
        
} //namespace vbase

#endif /* defined(__vClientTemplateLib__run_loop__) */
