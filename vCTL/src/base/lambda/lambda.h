//
//  task_lambda.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/30/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__task_lambda__
#define __vClientTemplateLib__task_lambda__

#include "base/lambda/lambda_functor.h"

namespace vbase
{

class TLambda
    {
public:
    virtual ~TLambda() {}
    virtual void Run() = 0;
    virtual TLambda* CreateCopy() = 0;
    };

} //namespace vbase

#endif /* defined(__vClientTemplateLib__task_lambda__) */
