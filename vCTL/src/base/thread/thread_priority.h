//
//  thread_priority.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/8/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_thread_priority_h
#define vClientTemplateLib_thread_priority_h


namespace vbase
{

enum EThreadPriority
    {
    EThreadPriority_Normal,
    EThreadPriority_Realtime,   //e.g. low-latency, glitch-resistant audio
    EThreadPriority_Display,    //threads that generate data for UI
    EThreadPriority_Background  //threads that should not disrupt high priority work
    };

} //namespace vbase


#endif
