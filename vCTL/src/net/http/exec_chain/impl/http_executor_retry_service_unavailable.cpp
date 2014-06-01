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

CRetryServiceUnavailableExecutor* CRetryServiceUnavailableExecutor::New()
    {
    CRetryServiceUnavailableExecutor* obj = new CRetryServiceUnavailableExecutor();
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
    }
    
CRetryServiceUnavailableExecutor::~CRetryServiceUnavailableExecutor()
    {
    }
    
void CRetryServiceUnavailableExecutor::Construct()
    {
    }
    
CRetryServiceUnavailableExecutor::CRetryServiceUnavailableExecutor()
    {
    }
    
  
} //namespace http
} //namespace net
} //namespace vctl
