//
//  http_executor_backoff.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/exec_chain/http_executor_backoff.h"

namespace vctl
{
namespace net
{
namespace http
{

CBackoffExecutor* CBackoffExecutor::New(IHttpRequestExecutionChain* aChain)
    {
    CBackoffExecutor* obj = new CBackoffExecutor(aChain);
    if( obj )
        {
        obj->Construct();
        }
    return obj;
    }
    
void CBackoffExecutor::ExecuteOrPassOn(CHttpContext* aHttpContext,
                IHttpRequest* aHttpRequest,
                IFutureCallBack* aFutureCallBack)
    {
    LOG_INFO << "CBackoffExecutor::ExecuteOrPassOn";
    
    PassOn(aHttpContext, aHttpRequest, aFutureCallBack);
    }
    
CBackoffExecutor::~CBackoffExecutor()
    {
    }
    
void CBackoffExecutor::Construct()
    {
    }
    
CBackoffExecutor::CBackoffExecutor(IHttpRequestExecutionChain* aChain)
    : IHttpRequestExecutionChain(aChain)
    {
    }
    

} //namespace http
} //namespace net
} //namespace vctl