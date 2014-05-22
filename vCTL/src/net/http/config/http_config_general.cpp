//
//  http_config_general.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/config/http_config_general.h"

namespace vctl
{
namespace net
{
namespace http
{

bool TGeneralHttpConfig::IsKeepAliveEnabled() const
    {
    return false;
    }
    
bool TGeneralHttpConfig::IsAuthenticaionNeeded() const
    {
    return false;
    }

} //namespace http
} //namespace net
} //namespace vctl

