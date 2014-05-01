//
//  run_loop_cocoa_DARWIN.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/29/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__run_loop_cocoa_DARWIN__
#define __vClientTemplateLib__run_loop_cocoa_DARWIN__

#include "base/runloop/detail/darwin/run_loop_DARWIN.h"

namespace vbase
{
namespace detail
{

    class CRunLoopCFRunLoop : public CRunLoopCFRunLoopBase, TNonCopyable<CRunLoopCFRunLoop>
    //
    // CFRunLoop abstraction
    //
        {
    public:
        static CRunLoopCFRunLoop* New();
        virtual ~CRunLoopCFRunLoop();
        virtual void DoRun(IWorkItem* aWorkItem);
        virtual void Stop();
    private:
        CRunLoopCFRunLoop();
        void Construct();
    private:
        CFRunLoopSourceRef iStopSource;
        bool iRunTag;
        };
    
    
    class CRunLoopNSRunLoop : public CRunLoopCFRunLoopBase, TNonCopyable<CRunLoopNSRunLoop>
    //
    // NSRunLoop abstraction
    //
        {
    public:
        static CRunLoopNSRunLoop* New();
        
        virtual ~CRunLoopNSRunLoop();
        virtual void DoRun(IWorkItem* aWorkItem);
        virtual void Stop();
    private:
        CRunLoopNSRunLoop();
        void Construct();
    private:
        CFRunLoopSourceRef iStopSource;
        bool iRunTag;
        };
    
}
}

#endif /* defined(__vClientTemplateLib__run_loop_cocoa_DARWIN__) */
