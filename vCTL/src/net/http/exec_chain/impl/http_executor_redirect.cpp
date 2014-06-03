//
//  http_executor_redirect.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/exec_chain/http_executor_redirect.h"

namespace vctl
{
namespace net
{
namespace http
{

 CRedirectExecutor* CRedirectExecutor::New(IHttpRequestExecutionChain* aChain)
    {
    CRedirectExecutor* obj = new CRedirectExecutor(aChain);
    if( obj )
        {
        obj->Construct();
        }
    return obj;
    }
    
 void CRedirectExecutor::ExecuteOrPassOn(CHttpContext* aHttpContext,
                            IHttpRequest* aHttpRequest,
                            IFutureCallBack* aFutureCallBack)
    {
    LOG_INFO << "CRedirectExecutor::ExecuteOrPassOn";
    
    PassOn(aHttpContext, aHttpRequest, aFutureCallBack);
    }
    
 CRedirectExecutor::~CRedirectExecutor()
    {
    }
    
void CRedirectExecutor::Construct()
    {
    }
    
CRedirectExecutor::CRedirectExecutor(IHttpRequestExecutionChain* aChain)
    : IHttpRequestExecutionChain(aChain)
    {
    }
    

} //namespace http
} //namespace net
} //namespace vctl