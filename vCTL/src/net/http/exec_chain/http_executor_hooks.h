//
//  http_executor_hooks.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_executor_hooks__
#define __vClientTemplateLib__http_executor_hooks__

#include "net/http/exec_chain/http_executor_interface.h"
#include "net/http/hooks/http_hooks.h"

#include "memory/smart_pointer/strong_pointer.h"

namespace vctl
{
namespace net
{
namespace http
{

class CHooksExecutor : public IHttpRequestExecutionChain
    {
public:
    static CHooksExecutor* New(IHttpRequestExecutionChain* aChainNext,
                                IHttpHooks* aIHttpHooks);
    
    virtual void ExecuteOrPassOn(CHttpContext* aHttpContext,
        IHttpRequest* aHttpRequest,
        IFutureCallBack* aFutureCallBack);
        
protected:
    virtual ~CHooksExecutor();
    void Construct();
    CHooksExecutor(IHttpRequestExecutionChain* aChainNext,
                                IHttpHooks* aIHttpHooks);
    
private:
    vctl::TStrongPointer<IHttpHooks> iIHttpHooks;
    };

} //namespace http
} //namespace net
} //namespace vctl

#endif /* defined(__vClientTemplateLib__http_executor_hooks__) */
