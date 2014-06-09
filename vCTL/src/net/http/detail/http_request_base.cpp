//
//  http_request_base.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 6/4/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/detail/http_request_base.h"

namespace vctl
{
namespace net
{
namespace http
{

static const char* kHttp = "http";

std::string CHttpRequestBase::GetUrl() const
    {
    return iUrl;
    }

CHttpRequestBase::~CHttpRequestBase()
    {
    }
    
CHttpRequestBase::CHttpRequestBase(const std::string& aUri)
    : iProtocolVersion()
    , iIsCancelledTag(false)
    , iHttpHeadersMap(0)
    {
    }
    
void CHttpRequestBase::Cancel()
    {
    iIsCancelledTag = true;
    }
    
bool CHttpRequestBase::IsCancelled() const
    {
    return iIsCancelledTag;
    }
    
void CHttpRequestBase::GetConfig(TRequestConfig& aTRequestConfig) const
    {
    }
    
TProtocolVersion CHttpRequestBase::Version() const
    {
    return iProtocolVersion;
    }
    
void CHttpRequestBase::AddHeader(const THeader& aHeader)
    {
    if( !iHttpHeadersMap.Get() )
        {
        iHttpHeadersMap = CHttpHeadersMap::New();
        }
    iHttpHeadersMap->Add( aHeader );
    }
    
void CHttpRequestBase::RemoveHeader(const THeader& aHeader)
    {
    
    }
    
bool CHttpRequestBase::HasHeader(const std::string& aHeaderName) const
    {
    return false;
    }
    
vctl::TStrongPointer<CHttpHeadersMap> CHttpRequestBase::GetAllHeaders() const
    {
    return iHttpHeadersMap;
    }

} //namespace http
} //namespace net
} //namespace vctl