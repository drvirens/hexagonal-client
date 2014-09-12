//
//  http_executor_redirect.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_executor_redirect__
#define __vClientTemplateLib__http_executor_redirect__

#include "net/http/exec_chain/http_executor_interface.h"

namespace vctl
{
namespace net
{
namespace http
{

class CRedirectExecutor : public IHttpRequestExecutionChain
    {
public:
    static CRedirectExecutor* New(IHttpRequestExecutionChain* aChain);
    
    virtual void ExecuteOrPassOn(CHttpContext* aHttpContext,
        IHttpRequest* aHttpRequest,
        IFutureCallBack* aFutureCallBack);
        
protected:
    virtual ~CRedirectExecutor();
    void Construct();
    CRedirectExecutor(IHttpRequestExecutionChain* aChain);
    
    };

} //namespace http
} //namespace net
} //namespace vctl

#endif /* defined(__vClientTemplateLib__http_executor_redirect__) */
