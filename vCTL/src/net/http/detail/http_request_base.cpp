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

CHttpRequestBase::~CHttpRequestBase()
    {
    }
    
CHttpRequestBase::CHttpRequestBase(const std::string& aUri)
    : iProtocolVersion()
    , iIsCancelledTag(false)
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
    
IHttpEntity* CHttpRequestBase::HttpEntity() const
    {
    IHttpEntity* entity = 0;
    return entity;
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
    vbase::TAutoLock guard(iLock);
    iHttpHeadersMap->Add( aHeader );
    }
    
void CHttpRequestBase::RemoveHeader(const THeader& aHeader)
    {
    vbase::TAutoLock guard(iLock);
    }
    
vctl::TStrongPointer<CHttpHeadersMap> CHttpRequestBase::GetAllHeaders() const
    {
    return iHttpHeadersMap;
    }

} //namespace http
} //namespace net
} //namespace vctl