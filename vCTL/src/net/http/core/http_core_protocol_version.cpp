//
//  http_core_protocol_version.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/16/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/core/http_core_protocol_version.h"


namespace vctl
{
namespace net
{
namespace http
{

TProtocolVersion::TProtocolVersion()
    {
    }
    
TProtocolVersion::TProtocolVersion(std::string& aProtocolName, TVersion aMajor, TVersion aMinor)
    : iProtocolName(aProtocolName)
    , iMajor(aMajor)
    , iMinor(aMinor)
    {
    }

const std::string& TProtocolVersion::ProtocolName() const
    {
    return iProtocolName;
    }
    
TVersion TProtocolVersion::Major() const
    {
    return iMajor;
    }
    
TVersion TProtocolVersion::Minor() const
    {
    return iMinor;
    }

} //namespace http
} //namespace net
} //namespace vctl
