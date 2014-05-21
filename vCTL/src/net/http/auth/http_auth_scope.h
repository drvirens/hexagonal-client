//
//  http_auth_scope.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_http_auth_scope_h
#define vClientTemplateLib_http_auth_scope_h

#include <string>
#include "base/thread/thread_un_safe.h"

namespace vctl
{
namespace net
{
namespace http
{

class TAuthScope //: private vbase::TNotThreadSafe
    {
public:

private:
    std::string iScheme;
    std::string iRealm;
    std::string iHost;
    int iPort;
    };

} //namespace http
} //namespace net
} //namespace vctl

#endif
