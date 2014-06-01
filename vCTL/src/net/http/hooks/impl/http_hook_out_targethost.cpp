//
//  http_hook_out_targethost.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/22/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/hooks/impl/http_hook_out_targethost.h"

namespace vctl
{
namespace net
{
namespace http
{

CHttpHookOutgoingTargetHost* CHttpHookOutgoingTargetHost::New()
    {
    CHttpHookOutgoingTargetHost* obj = new CHttpHookOutgoingTargetHost();
    if( obj )
        {
        obj->Construct();
        }
    return obj;
    }
    
bool CHttpHookOutgoingTargetHost::ProcessPacketHeader(IHttpRequest& aHttpRequest)
    {
    return false;
    }
    
CHttpHookOutgoingTargetHost::~CHttpHookOutgoingTargetHost()
    {
    }
    
CHttpHookOutgoingTargetHost::CHttpHookOutgoingTargetHost()
    {
    }
    
void CHttpHookOutgoingTargetHost::Construct()
    {
    }
    

} //namespace http
} //namespace net
} //namespace vctl
