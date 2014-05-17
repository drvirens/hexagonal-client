//
//  http_future_callback.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/16/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_future_callback__
#define __vClientTemplateLib__http_future_callback__

#include "base/lambda/lambda.h"

namespace vctl
{
namespace net
{
namespace http
{

template <class T>
class CFutureCallBack : public vbase::CLambda
    {
public:
    virtual void Failed(int aError) = 0;
    virtual void Succeeded(T& aResponse) = 0;
    virtual void Cancelled() = 0;
    
protected:
    virtual void DoRun();
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_future_callback__) */
