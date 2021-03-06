//
//  http_core_protocol_version.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/16/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_core_protocol_version__
#define __vClientTemplateLib__http_core_protocol_version__

#include <string>

namespace vctl
{
namespace net
{
namespace http
{

typedef unsigned char TVersion;

class TProtocolVersion
    {
public:
    TProtocolVersion();
    TProtocolVersion(std::string& aProtocolName, TVersion aMajor, TVersion aMinor);
    
    const std::string& ProtocolName() const;
    TVersion Major() const;
    TVersion Minor() const;
    
private:
    std::string iProtocolName;
    TVersion iMajor;
    TVersion iMinor;
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_core_protocol_version__) */
