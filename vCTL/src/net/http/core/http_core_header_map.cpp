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
    return iMap.Size();
    }
    
void CHttpHeadersMap::Add(const THeader& aHeader)
    {
    iMap.Add(iHeaderId, aHeader);
    
    iHeaderId++; //TODO: this needs to be atomic increment
    }
    
bool CHttpHeadersMap::GetHeader(int aIndex, THeader& aHeaderReturn)
    {
    if( iMap.Size() <= 0 )
        {
        return false;
        }
    aHeaderReturn = iMap.Get(aIndex);
    return true;
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
    : iHeaderId(0)
    {
    }
    

} //namespace http
} //namespace net
} //namespace vctl
