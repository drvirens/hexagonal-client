//
//  http_auth_strategy.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/20/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_http_auth_strategy_h
#define vClientTemplateLib_http_auth_strategy_h

#include "memory/ref/rc_thread_safe.h"

namespace vctl
{
namespace net
{
namespace http
{

class IHttpResponse;

class IAuthenticationStrategy : private vctl::CReferenceThreadSafe<IAuthenticationStrategy>
    {
public:
    virtual bool IsAuthRequested() = 0;
    virtual void GetChallenges() = 0;
    virtual void ChooseChallenge() = 0;
    
protected:
    virtual ~IAuthenticationStrategy() {}
    friend class vctl::CReferenceThreadSafe<IAuthenticationStrategy>;
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif
