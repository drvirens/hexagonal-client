//
//  http_future_callback.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/16/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_future_callback__
#define __vClientTemplateLib__http_future_callback__

#include "memory/ref/rc_thread_safe.h"

namespace vctl
{
namespace net
{
namespace http
{

class IHttpResponse;

class IFutureCallBack : public vctl::CReferenceThreadSafe<IFutureCallBack>
    {
public:
    virtual void Failed(int aError) = 0;
    virtual void Succeeded(IHttpResponse* aResponse) = 0;
    virtual void Cancelled() = 0;
    
protected:
    virtual ~IFutureCallBack() {}
    friend class vctl::CReferenceThreadSafe<IFutureCallBack>;
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_future_callback__) */
