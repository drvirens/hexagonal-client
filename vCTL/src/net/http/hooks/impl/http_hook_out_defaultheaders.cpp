//
//  http_hook_out_defaultheaders.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/29/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/hooks/impl/http_hook_out_defaultheaders.h"

namespace vctl
{
namespace net
{
namespace http
{

CHttpHookOutgoingDefaultHeaders* CHttpHookOutgoingDefaultHeaders::New(vctl::TStrongPointer<CHttpHeadersMap> aCHttpHeadersMap)
    {
    CHttpHookOutgoingDefaultHeaders* obj = new CHttpHookOutgoingDefaultHeaders();
    if( obj )
        {
        obj->Construct();
        }
    return obj;
    }
    
bool CHttpHookOutgoingDefaultHeaders::ProcessPacketHeader(IHttpRequest& aHttpRequest)
    {
    return true;
    }

CHttpHookOutgoingDefaultHeaders::~CHttpHookOutgoingDefaultHeaders()
    {
    }
    
CHttpHookOutgoingDefaultHeaders::CHttpHookOutgoingDefaultHeaders()
    {
    }
    
void CHttpHookOutgoingDefaultHeaders::Construct()
    {
    }
    

} //namespace http
} //namespace net
} //namespace vctl
