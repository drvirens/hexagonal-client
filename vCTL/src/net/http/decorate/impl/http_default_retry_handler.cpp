//
//  http_default_retry_handler.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/30/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/decorate/impl/http_default_retry_handler.h"

namespace vctl
{
namespace net
{
namespace http
{

CDefaultRetryHandler* CDefaultRetryHandler::New()
    {
    CDefaultRetryHandler* obj = new CDefaultRetryHandler();
    if( obj )
        {
        obj->Construct();
        }
    return obj;
    }
    
bool CDefaultRetryHandler::Retry(EHttpStatusCode aPreviousError, int aAttemptedRetries, IHttpContext& aContext)
    {
    return false;
    }
    
CDefaultRetryHandler::~CDefaultRetryHandler()
    {
    }
    
CDefaultRetryHandler::CDefaultRetryHandler()
    {
    }
    
void CDefaultRetryHandler::Construct()
    {
    }
    

} //namespace http
} //namespace net
} //namespace vctl


