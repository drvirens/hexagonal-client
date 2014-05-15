//
//  lambda.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/5/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_lambda_h
#define vClientTemplateLib_lambda_h

#include "memory/ref/rc_thread_safe.h"
#include "memory/ref/rc.h"

namespace vbase
{

class CLambda : public vctl::CReferenceBaseThreadSafe
    {
public:
    virtual ~CLambda() {}
    void Run()
        {
        DoRun();
        }
private:
    virtual void DoRun() = 0;
    };

    
}

#endif
