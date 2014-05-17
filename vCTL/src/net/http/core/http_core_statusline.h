//
//  http_core_statusline.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/16/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_core_statusline__
#define __vClientTemplateLib__http_core_statusline__

#include <string>
#include "net/http/core/http_core_protocol_version.h"
#include "net/http/core/http_core_status.h"

namespace vctl
{
namespace net
{
namespace http
{

class TStatusLine
    {
public:
    TStatusLine(const TProtocolVersion& aProtocolVersion, const EHttpStatusCode& aStatusCode, std::string& aReasonPhrase);
    
    const TProtocolVersion& ProtocolVersion() const;
    EHttpStatusCode StatusCode() const;
    const std::string& ReasonPhrase() const;
    
private:
    TProtocolVersion iProtocolVersion;
    EHttpStatusCode iStatusCode;
    std::string iReasonPhrase;
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_core_statusline__) */
