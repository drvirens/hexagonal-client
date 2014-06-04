//
//  http_core_header_map.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/17/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/core/http_core_header_map.h"
#include "net/http/core/http_core_header.h"

namespace vctl
{
namespace net
{
namespace http
{

int CHttpHeadersMap::Size() const
    {
    return 6;
    }
    
THeader* CHttpHeadersMap::GetHeader(int aIndex)
    {
    THeader h;
    return &h;
    }
    

CHttpHeadersMap::~CHttpHeadersMap()
    {
    }
    
CHttpHeadersMap* CHttpHeadersMap::New()
    {
    CHttpHeadersMap* obj = new CHttpHeadersMap();
    if( obj )
        {
        obj->Construct();
        }
    return obj;
    }
    
void CHttpHeadersMap::Construct()
    {
    }
    
CHttpHeadersMap::CHttpHeadersMap()
    {
    }
    

} //namespace http
} //namespace net
} //namespace vctl
