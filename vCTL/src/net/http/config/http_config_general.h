//
//  http_config_general.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_config_general__
#define __vClientTemplateLib__http_config_general__

#include <string>

namespace vctl
{
namespace net
{
namespace http
{

class TGeneralHttpConfig
    {
public:
    bool IsKeepAliveEnabled() const;
    bool IsAuthenticaionNeeded() const;
    bool IsAutomaticRetriesEnabled() const;
    bool IsRedirectEnabled() const;
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_config_general__) */
