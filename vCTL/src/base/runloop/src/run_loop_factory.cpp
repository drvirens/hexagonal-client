//
//  run_loop_factory.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/1/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "base/runloop/run_loop.h"
#include "base/runloop/run_loop_factory.h"
#include "build/build_config.h"

#if defined(V_PLATFORM_DARWIN)
#include "base/runloop/detail/darwin/run_loop_cocoa_DARWIN.h"
#else
#error Add support for RunLoop for non-Darwin platforms
#endif

namespace vbase
{

IRunLoopBase* TRunLoopFactory::PlatformRunLoop()
    {
    IRunLoopBase* runloop;
#if defined(V_PLATFORM_DARWIN)
    runloop = detail::CRunLoopCFRunLoop::New();
#else
    runloop = 0; //support for other platforms 
#endif
    return runloop;
    }

}
