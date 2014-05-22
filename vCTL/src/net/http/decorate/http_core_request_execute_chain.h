//
//  http_core_request_chain.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/19/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_core_request_chain__
#define __vClientTemplateLib__http_core_request_chain__


#include "net/http/core/http_core_request.h"
#include "net/http/core/http_core_response.h"
#include "net/http/async/http_future_callback.h"
#include "base/thread/thread_un_safe.h"
#include "memory/ref/rc_thread_safe.h"

namespace vctl
{
namespace net
{
namespace http
{

class CHttpContext;


class IHttpRequestExecutionChain : private vctl::CReferenceThreadSafe<IHttpRequestExecutionChain>
    {
public:
    virtual void ExecuteOrPassOn(CHttpContext* aHttpContext,
        IHttpRequest* aHttpRequest,
        IFutureCallBack* aFutureCallBack) = 0;
        
protected:
    virtual ~IHttpRequestExecutionChain() {}
    friend class vctl::CReferenceThreadSafe<IHttpRequestExecutionChain>;
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_core_request_chain__) */
