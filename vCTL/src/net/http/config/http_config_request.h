//
//  http_config_request.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/17/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_config_request__
#define __vClientTemplateLib__http_config_request__

#include <string>

namespace vctl
{
namespace net
{
namespace http
{

class TRequestConfig
    {
public:
    bool IsSSLVerificationDisabled() const;
    const std::string& CertificatesPath() const;
    long ConnectTimeout() const;
    long DnsCacheTimeout() const;
    long MaxRedirects() const;
    long FollowLocation() const;
    
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_config_request__) */
