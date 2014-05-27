//
//  http_executor_boss.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_executor_boss__
#define __vClientTemplateLib__http_executor_boss__

#include "net/http/exec_chain/http_executor_interface.h"

namespace vctl
{
namespace net
{
namespace http
{

class CHttpRequestExecutorBoss : public IHttpRequestExecutionChain
    {
public:
    static CHttpRequestExecutorBoss*New();
    
    virtual void ExecuteOrPassOn(CHttpContext* aHttpContext,
        IHttpRequest* aHttpRequest,
        IFutureCallBack* aFutureCallBack) = 0;
        
protected:
    virtual ~CHttpRequestExecutorBoss();
    void Construct();
    CHttpRequestExecutorBoss();
    
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_executor_boss__) */
