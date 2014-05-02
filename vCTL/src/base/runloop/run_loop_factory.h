//
//  run_loop_factory.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/1/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_run_loop_factory_h
#define vClientTemplateLib_run_loop_factory_h

namespace vbase
{

class IRunLoopBase;

class TRunLoopFactory
    {
public:
    //get platform specific runloop
    static IRunLoopBase* PlatformRunLoop();
    };
    
}

#endif
