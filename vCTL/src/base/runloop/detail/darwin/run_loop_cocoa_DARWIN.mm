//
//  run_loop_cocoa_DARWIN.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/29/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "base/runloop/detail/darwin/run_loop_cocoa_DARWIN.h"

namespace vbase
    {
namespace detail
    {
        
    CRunLoopCFRunLoop::CRunLoopCFRunLoop()
        : iStopSource (0)
        , iRunTag (false)
        {
            
        }
    CRunLoopCFRunLoop::~CRunLoopCFRunLoop()
        {}
    void CRunLoopCFRunLoop::DoRun(IWorkItem* aWorkItem)
        {
        SInt32 ret;
        do
            {
             @autoreleasepool
                {
                CFStringRef     mode                      = kCFRunLoopDefaultMode;
                CFTimeInterval  seconds                   = ;
                Boolean         returnAfterSourceHandled  = false;
                ret = CFRunLoopRunInMode(mode, seconds, returnAfterSourceHandled);
                }
            }
        while ( kCFRunLoopRunStopped != ret && kCFRunLoopRunFinished != ret);
        }
    void CRunLoopCFRunLoop::Stop()
        {
            
        }
        
    CRunLoopNSRunLoop::CRunLoopNSRunLoop()
        {
            
        }
    CRunLoopNSRunLoop::~CRunLoopNSRunLoop()
        {
            
        }
    void CRunLoopNSRunLoop::DoRun(IWorkItem* aWorkItem)
        {
            
        }
    void CRunLoopNSRunLoop::Stop()
        {
            
        }

    }
    }