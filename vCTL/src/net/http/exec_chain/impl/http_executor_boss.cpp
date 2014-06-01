//
//  http_executor_boss.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/exec_chain/http_executor_boss.h"

namespace vctl
{
namespace net
{
namespace http
{

CHttpRequestExecutorBoss* CHttpRequestExecutorBoss::New(vctl::TStrongPointer<detail::IHttpActualSenderReceiver> aIHttpActualSenderReceiver,
             vctl::TStrongPointer<IConnectionReuseStrategy> aIConnectionReuseStrategy,
             vctl::TStrongPointer<IConnectionKeepAliveStrategy> aIConnectionKeepAliveStrategy,
             vctl::TStrongPointer<IAuthenticationStrategy> aIAuthenticationStrategy)
    {
    CHttpRequestExecutorBoss* obj = new CHttpRequestExecutorBoss();
    if( obj )
        {
        obj->Construct();
        }
    return obj;
    }
    
void CHttpRequestExecutorBoss::ExecuteOrPassOn(CHttpContext* aHttpContext,
            IHttpRequest* aHttpRequest,
            IFutureCallBack* aFutureCallBack)
    {
    }
    
CHttpRequestExecutorBoss::~CHttpRequestExecutorBoss()
    {
    }
    
void CHttpRequestExecutorBoss::Construct()
    {
    }
    
CHttpRequestExecutorBoss::CHttpRequestExecutorBoss()
    {
    }
    

} //namespace http
} //namespace net
} //namespace vctl

