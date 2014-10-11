//
//  http_core_request_line.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/17/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_core_request_line__
#define __vClientTemplateLib__http_core_request_line__

#include <string>
#include "net/http/core/http_core_protocol_version.h"
#include "net/http/core/http_core_method_type.h"

namespace vctl
{
namespace net
{
namespace http
{

class TRequestLine
    {
public:
    TRequestLine(const TProtocolVersion& aProtocolVersion, const EHttpMethodType& aMethod, std::string& aUri);
    
    const TProtocolVersion& ProtocolVersion() const;
    EHttpMethodType Method() const;
    const std::string& Uri() const;
    
private:
    TProtocolVersion iProtocolVersion;
    EHttpMethodType iMethod;
    std::string iUri;
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_core_request_line__) */
