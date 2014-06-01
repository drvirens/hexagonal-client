//
//  http_executor_retry.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_executor_retry__
#define __vClientTemplateLib__http_executor_retry__

#include "net/http/exec_chain/http_executor_interface.h"
#include "net/http/decorate/http_retry_handler.h"

namespace vctl
{
namespace net
{
namespace http
{

class CRetryExecutor : public IHttpRequestExecutionChain
    {
public:
    static CRetryExecutor* New(IHttpRequestExecutionChain* aChainLink, IRetryHandler* aIRetryHandler);
    
    virtual void ExecuteOrPassOn(CHttpContext* aHttpContext,
        IHttpRequest* aHttpRequest,
        IFutureCallBack* aFutureCallBack);
        
protected:
    virtual ~CRetryExecutor();
    void Construct();
    CRetryExecutor();
    
    };

} //namespace http
} //namespace net
} //namespace vctl

#endif /* defined(__vClientTemplateLib__http_executor_retry__) */
