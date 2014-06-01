//
//  http_default_connection_keep_alive_strategy.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/29/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/decorate/impl/http_default_connection_keep_alive_strategy.h"

namespace vctl
{
namespace net
{
namespace http
{

CDefaultConnectionKeepAliveStrategy* CDefaultConnectionKeepAliveStrategy::New()
    {
    CDefaultConnectionKeepAliveStrategy* obj = new CDefaultConnectionKeepAliveStrategy();
    if( obj )
        {
        obj->Construct();
        }
    return obj;
    }
    
long CDefaultConnectionKeepAliveStrategy::GetKeepAliveDuration(const IHttpResponse& aResponse, CHttpContext& aContext)
    {
    return 0L;
    }
    
CDefaultConnectionKeepAliveStrategy::~CDefaultConnectionKeepAliveStrategy()
    {
    }
    
CDefaultConnectionKeepAliveStrategy::CDefaultConnectionKeepAliveStrategy()
    {
    }
    
void CDefaultConnectionKeepAliveStrategy::Construct()
    {
    }
    

} //namespace http
} //namespace net
} //namespace vctl