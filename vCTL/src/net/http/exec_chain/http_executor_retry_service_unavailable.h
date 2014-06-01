//
//  http_executor_retry_service_unavailable.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_executor_retry_service_unavailable__
#define __vClientTemplateLib__http_executor_retry_service_unavailable__

#include "net/http/exec_chain/http_executor_interface.h"

namespace vctl
{
namespace net
{
namespace http
{

class CRetryServiceUnavailableExecutor : public IHttpRequestExecutionChain
    {
public:
    static CRetryServiceUnavailableExecutor* New();
    
    virtual void ExecuteOrPassOn(CHttpContext* aHttpContext,
        IHttpRequest* aHttpRequest,
        IFutureCallBack* aFutureCallBack);
        
protected:
    virtual ~CRetryServiceUnavailableExecutor();
    void Construct();
    CRetryServiceUnavailableExecutor();
    
    };

} //namespace http
} //namespace net
} //namespace vctl

#endif /* defined(__vClientTemplateLib__http_executor_retry_service_unavailable__) */
