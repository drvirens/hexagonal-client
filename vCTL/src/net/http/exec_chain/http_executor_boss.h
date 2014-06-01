//
//  http_executor_boss.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_executor_boss__
#define __vClientTemplateLib__http_executor_boss__

#include "memory/smart_pointer/strong_pointer.h"
#include "net/http/exec_chain/http_executor_interface.h"

#include "net/http/decorate/http_actual.h"
#include "net/http/decorate/http_connection_reuse_strategy.h"
#include "net/http/decorate/http_connection_keep_alive_strategy.h"
#include "net/http/auth/http_auth_strategy.h"

namespace vctl
{
namespace net
{
namespace http
{

class CHttpRequestExecutorBoss : public IHttpRequestExecutionChain
    {
public:
    static CHttpRequestExecutorBoss* New(vctl::TStrongPointer<detail::IHttpActualSenderReceiver> aIHttpActualSenderReceiver,
                             vctl::TStrongPointer<IConnectionReuseStrategy> aIConnectionReuseStrategy,
                             vctl::TStrongPointer<IConnectionKeepAliveStrategy> aIConnectionKeepAliveStrategy,
                             vctl::TStrongPointer<IAuthenticationStrategy> aIAuthenticationStrategy);
    
    virtual void ExecuteOrPassOn(CHttpContext* aHttpContext,
        IHttpRequest* aHttpRequest,
        IFutureCallBack* aFutureCallBack);
        
protected:
    virtual ~CHttpRequestExecutorBoss();
    void Construct();
    CHttpRequestExecutorBoss();
    
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_executor_boss__) */
