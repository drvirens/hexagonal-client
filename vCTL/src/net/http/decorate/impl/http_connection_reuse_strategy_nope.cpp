//
//  http_connection_reuse_strategy_nope.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/27/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/decorate/impl/http_connection_reuse_strategy_nope.h"

namespace vctl
{
namespace net
{
namespace http
{

bool CNopeConnectionReuseStrategy::KeepAlive(const IHttpResponse& aResponse,
CHttpContext& aContext)
    {
    return false;
    }
    
CNopeConnectionReuseStrategy::~CNopeConnectionReuseStrategy()
    {
    }
    
CNopeConnectionReuseStrategy::CNopeConnectionReuseStrategy()
    {
    }
    
void CNopeConnectionReuseStrategy::Construct()
    {
    }
    
CNopeConnectionReuseStrategy* CNopeConnectionReuseStrategy::New()
    {
    CNopeConnectionReuseStrategy* obj = new CNopeConnectionReuseStrategy();
    if( obj )
        {
        obj->Construct();
        }
    return obj;
    }

} //namespace http
} //namespace net
} //namespace vctl