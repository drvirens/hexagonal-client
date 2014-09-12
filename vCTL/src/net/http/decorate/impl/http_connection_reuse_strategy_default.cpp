//
//  http_connection_reuse_strategy_default.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/27/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/decorate/impl/http_connection_reuse_strategy_default.h"

namespace vctl
{
namespace net
{
namespace http
{

bool CDefaultConnectionReuseStrategy::KeepAlive(const IHttpResponse& aResponse,
CHttpContext& aContext)
    {
    return true;
    }
    
CDefaultConnectionReuseStrategy::~CDefaultConnectionReuseStrategy()
    {
    }
    
CDefaultConnectionReuseStrategy::CDefaultConnectionReuseStrategy()
    {
    }
    
void CDefaultConnectionReuseStrategy::Construct()
    {
    }
    
CDefaultConnectionReuseStrategy* CDefaultConnectionReuseStrategy::New()
    {
    CDefaultConnectionReuseStrategy* obj = new CDefaultConnectionReuseStrategy();
    if( obj )
        {
        obj->Construct();
        }
    return obj;
    }

} //namespace http
} //namespace net
} //namespace vctl