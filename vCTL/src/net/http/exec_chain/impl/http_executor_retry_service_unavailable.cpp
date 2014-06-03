//
//  http_executor_retry_service_unavailable.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/exec_chain/http_executor_retry_service_unavailable.h"

namespace vctl
{
namespace net
{
namespace http
{

CRetryServiceUnavailableExecutor* CRetryServiceUnavailableExecutor::New(IHttpRequestExecutionChain* aChain)
    {
    CRetryServiceUnavailableExecutor* obj = new CRetryServiceUnavailableExecutor(aChain);
    if( obj )
        {
        obj->Construct();
        }
    return obj;
    }
    
void CRetryServiceUnavailableExecutor::ExecuteOrPassOn(CHttpContext* aHttpContext,
                                    IHttpRequest* aHttpRequest,
                                    IFutureCallBack* aFutureCallBack)
    {
    LOG_INFO << "CRetryServiceUnavailableExecutor::ExecuteOrPassOn";
    
    PassOn(aHttpContext, aHttpRequest, aFutureCallBack);
    }
    
CRetryServiceUnavailableExecutor::~CRetryServiceUnavailableExecutor()
    {
    }
    
void CRetryServiceUnavailableExecutor::Construct()
    {
    }
    
CRetryServiceUnavailableExecutor::CRetryServiceUnavailableExecutor(IHttpRequestExecutionChain* aChain)
    : IHttpRequestExecutionChain(aChain)
    {
    }
    
  
} //namespace http
} //namespace net
} //namespace vctl
