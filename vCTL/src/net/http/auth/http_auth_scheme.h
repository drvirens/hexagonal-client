//
//  IAuthScheme.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/20/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_IAuthScheme_h
#define vClientTemplateLib_IAuthScheme_h

#include "base/thread/thread_un_safe.h"

namespace vctl
{
namespace net
{
namespace http
{
class IHttpContext;

class IAuthScheme
    {
public:
    virtual ~IAuthScheme() {}
    virtual const std::string& AuthSchemeName() = 0;
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif
