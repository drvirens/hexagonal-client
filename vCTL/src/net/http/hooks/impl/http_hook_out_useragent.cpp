//
//  http_hook_out_useragent.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/22/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//


#include "net/http/hooks/impl/http_hook_out_useragent.h"

namespace vctl
{
namespace net
{
namespace http
{

CHttpHookOutgoingUserAgent* CHttpHookOutgoingUserAgent::New()
    {
    CHttpHookOutgoingUserAgent* obj = new CHttpHookOutgoingUserAgent();
    if( obj )
        {
        obj->Construct();
        }
    return obj;
    }
    
bool CHttpHookOutgoingUserAgent::ProcessPacketHeader(IHttpRequest& aHttpRequest)
    {
    return false;
    }
    
CHttpHookOutgoingUserAgent::~CHttpHookOutgoingUserAgent()
    {
    }
    
CHttpHookOutgoingUserAgent::CHttpHookOutgoingUserAgent()
    {
    }
    
void CHttpHookOutgoingUserAgent::Construct()
    {
    }
    

} //namespace http
} //namespace net
} //namespace vctl