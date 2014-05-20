//
//  http_config_request.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/17/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/config/http_config_request.h"

namespace vctl
{
namespace net
{
namespace http
{

bool TRequestConfig::IsSSLVerificationDisabled() const
    {
    return true;
    }
    
const std::string& TRequestConfig::CertificatesPath() const
    {
    return "";
    }
    
long TRequestConfig::ConnectTimeout() const
    {
    return 10;
    }
    
long TRequestConfig::DnsCacheTimeout() const
    {
    return 10;
    }
    
long TRequestConfig::MaxRedirects() const
    {
    return 10;
    }
    
long TRequestConfig::FollowLocation() const
    {
    return 10;
    }
    

} //namespace http
} //namespace net
} //namespace vctl
