//
//  http_executor_backoff.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_executor_backoff_strategy__
#define __vClientTemplateLib__http_executor_backoff_strategy__

#include "net/http/exec_chain/http_executor_interface.h"

namespace vctl
{
namespace net
{
namespace http
{

class CBackoffExecutor : public IHttpRequestExecutionChain
    {
public:
    static CBackoffExecutor* New();
    
    virtual void ExecuteOrPassOn(CHttpContext* aHttpContext,
        IHttpRequest* aHttpRequest,
        IFutureCallBack* aFutureCallBack);
        
protected:
    virtual ~CBackoffExecutor();
    void Construct();
    CBackoffExecutor();
    
    };

} //namespace http
} //namespace net
} //namespace vctl

#endif /* defined(__vClientTemplateLib__http_executor_backoff_strategy__) */
