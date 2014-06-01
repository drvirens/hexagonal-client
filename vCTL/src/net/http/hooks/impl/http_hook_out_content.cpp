//
//  http_hook_out_content.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/22/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/hooks/impl/http_hook_out_content.h"

namespace vctl
{
namespace net
{
namespace http
{

CHttpHookOutgoingContent* CHttpHookOutgoingContent::New()
    {
    CHttpHookOutgoingContent* obj = new CHttpHookOutgoingContent();
    if( obj )
        {
        obj->Construct();
        }
    return obj;
    }
    
bool CHttpHookOutgoingContent::ProcessPacketHeader(IHttpRequest& aHttpRequest)
    {
    return false;
    }
    
CHttpHookOutgoingContent::~CHttpHookOutgoingContent()
    {
    }
    
CHttpHookOutgoingContent::CHttpHookOutgoingContent()
    {
    }
    
void CHttpHookOutgoingContent::Construct()
    {
    }
    

} //namespace http
} //namespace net
} //namespace vctl