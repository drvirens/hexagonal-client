//
//  http_executor_hooks.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/exec_chain/http_executor_hooks.h"

namespace vctl
{
namespace net
{
namespace http
{

CHooksExecutor* CHooksExecutor::New(IHttpRequestExecutionChain* aChainNext,
    IHttpHooks* aIHttpHooks)
    {
    CHooksExecutor* obj = new CHooksExecutor();
    if( obj )
        {
        obj->Construct();
        }
    return obj;
    }
    
void CHooksExecutor::ExecuteOrPassOn(CHttpContext* aHttpContext,
IHttpRequest* aHttpRequest,
IFutureCallBack* aFutureCallBack)
    {
    }
    
CHooksExecutor::~CHooksExecutor()
    {
    }
    
void CHooksExecutor::Construct()
    {
    }
    
CHooksExecutor::CHooksExecutor()
    {
    }
    

} //namespace http
} //namespace net
} //namespace vctl