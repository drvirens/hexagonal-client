//
//  http_core_header.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/16/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_core_header__
#define __vClientTemplateLib__http_core_header__

#include <string>

namespace vctl
{
namespace net
{
namespace http
{

class THeader
    {
public:
    std::string Describe() const;
    };

} //namespace http
} //namespace net
} //namespace vctl

#endif /* defined(__vClientTemplateLib__http_core_header__) */
