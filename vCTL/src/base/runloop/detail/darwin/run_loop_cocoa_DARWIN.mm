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

CRunLoopCFRunLoop* CRunLoopCFRunLoop::New()
    {
    CRunLoopCFRunLoop* obj = new CRunLoopCFRunLoop();
    if( obj )
        {
        obj->Construct();
        }
    return obj;
    }
    
void CRunLoopCFRunLoop::Construct()
    {
    CRunLoopCFRunLoopBase::Construct();
    }

CRunLoopCFRunLoop::CRunLoopCFRunLoop()
    : iStopSource (0)
    , iRunTag (false)
    {}
    
CRunLoopCFRunLoop::~CRunLoopCFRunLoop()
    {}
    
void CRunLoopCFRunLoop::DoRun(IWorkLoad* aWorkLoad)
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
    
// -------------------------------------------- NSRunLoop
CRunLoopNSRunLoop* CRunLoopNSRunLoop::New()
{
    CRunLoopNSRunLoop* obj = new CRunLoopNSRunLoop();
    if( obj )
    {
        obj->Construct();
    }
    return obj;
}

void CRunLoopNSRunLoop::Construct()
{
    CRunLoopCFRunLoopBase::Construct();
}

CRunLoopNSRunLoop::CRunLoopNSRunLoop()
    : iStopSource (0)
    , iRunTag (true)
    {}

CRunLoopNSRunLoop::~CRunLoopNSRunLoop()
    {
        
    }
void CRunLoopNSRunLoop::DoRun(IWorkLoad* aWorkLoad)
    {
    while( iRunTag )
        {
        [[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode beforeDate:[NSDate distantFuture]];
        }
    iRunTag = true;
    }
void CRunLoopNSRunLoop::Stop()
    {
        
    }

}
}