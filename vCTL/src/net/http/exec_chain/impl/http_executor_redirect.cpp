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

 CRedirectExecutor* CRedirectExecutor::New()
    {
    CRedirectExecutor* obj = new CRedirectExecutor();
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
    }
    
 CRedirectExecutor::~CRedirectExecutor()
    {
    }
    
void CRedirectExecutor::Construct()
    {
    }
    
CRedirectExecutor::CRedirectExecutor()
    {
    }
    

} //namespace http
} //namespace net
} //namespace vctl