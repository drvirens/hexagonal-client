//
//  run_loop_cocoa_DARWIN.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/29/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include <limits>
#include "base/runloop/detail/darwin/run_loop_cocoa_DARWIN.h"

namespace vbase
    {
namespace detail
    {
    
    static const CFTimeInterval kCFTimeIntervalDistantFuture = std::numeric_limits<CFTimeInterval>::max();
    
    CRunLoopCFRunLoop::CRunLoopCFRunLoop()
        : iStopSource (0)
        , iRunTag (false)
        {}
        
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
                CFTimeInterval  seconds                   = kCFTimeIntervalDistantFuture;
                Boolean         returnAfterSourceHandled  = false;
                
                ret = CFRunLoopRunInMode(mode, seconds, returnAfterSourceHandled);
                LOG_INFO << "CFRunLoopRunInMode returend " << ret;
                }
            }
        while ( kCFRunLoopRunStopped != ret && kCFRunLoopRunFinished != ret);
        }
        
    void CRunLoopCFRunLoop::Stop()
        {
        CFRunLoopStop( NativeRunLoop() );
        iRunTag = true;
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