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
    CRetryExecutor* obj = new CRetryExecutor(aChainLink, aIRetryHandler);
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
    LOG_INFO << "CRetryExecutor::ExecuteOrPassOn";
    
    PassOn(aHttpContext, aHttpRequest, aFutureCallBack);
    }
    
CRetryExecutor::~CRetryExecutor()
    {
    }
    
void CRetryExecutor::Construct()
    {
    }
    
CRetryExecutor::CRetryExecutor(IHttpRequestExecutionChain* aChainLink, IRetryHandler* aIRetryHandler)
    : IHttpRequestExecutionChain(aChainLink)
    , iIRetryHandler(aIRetryHandler)
    {
    }
    
 
} //namespace http
} //namespace net
} //namespace vctl

