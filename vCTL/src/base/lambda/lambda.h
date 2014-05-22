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
//#include "memory/ref/rc.h"

namespace vbase
{

class CLambda : private vctl::CReferenceThreadSafe<CLambda>
    {
public:
    void Run()
        {
        DoRun();
        }
protected:
    virtual void DoRun() = 0;
    virtual ~CLambda() {}
    friend class vctl::CReferenceThreadSafe<CLambda>;
    };

    
}

#endif
