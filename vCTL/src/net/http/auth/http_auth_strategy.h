//
//  http_auth_strategy.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/20/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_http_auth_strategy_h
#define vClientTemplateLib_http_auth_strategy_h

#include "base/thread/thread_un_safe.h"

namespace vctl
{
namespace net
{
namespace http
{

class IHttpResponse;

class IAuthenticationStrategy : private vbase::TNotThreadSafe
    {
public:
    virtual ~IAuthenticationStrategy() {}
    
    virtual bool IsAuthRequested() = 0;
    virtual void GetChallenges() = 0;
    virtual void ChooseChallenge() = 0;
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif
