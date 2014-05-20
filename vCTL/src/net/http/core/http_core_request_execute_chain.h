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


namespace vctl
{
namespace net
{
namespace http
{

class CHttpContext;


class IHttpRequestExecuteChain
    {
public:
    virtual ~IHttpRequestExecuteChain() {}

    virtual void ExecuteOrPassOn(CHttpContext* aHttpContext,
        IHttpRequest* aHttpRequest,
        IFutureCallBack* aFutureCallBack) = 0;
     };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_core_request_chain__) */