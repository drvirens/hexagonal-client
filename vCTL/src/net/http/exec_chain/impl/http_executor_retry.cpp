//
//  http_executor_retry.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/exec_chain/http_executor_retry.h"

namespace vctl
{
namespace net
{
namespace http
{

CRetryExecutor* CRetryExecutor::New(IHttpRequestExecutionChain* aChainLink, IRetryHandler* aIRetryHandler)
    {
    CRetryExecutor* obj = new CRetryExecutor();
    if( obj )
        {
        obj->Construct();
        }
    return obj;
    }
    
void CRetryExecutor::ExecuteOrPassOn(CHttpContext* aHttpContext,
                        IHttpRequest* aHttpRequest,
                        IFutureCallBack* aFutureCallBack)
    {
    }
    
CRetryExecutor::~CRetryExecutor()
    {
    }
    
void CRetryExecutor::Construct()
    {
    }
    
CRetryExecutor::CRetryExecutor()
    {
    }
    
 
} //namespace http
} //namespace net
} //namespace vctl

