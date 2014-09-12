//
//  http_auth_strategy_nope.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/27/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_auth_strategy_nope__
#define __vClientTemplateLib__http_auth_strategy_nope__

#include "net/http/auth/http_auth_strategy.h"

namespace vctl
{
namespace net
{
namespace http
{

class CNopeAuthenticationStrategy: public IAuthenticationStrategy
    {
public:
    static CNopeAuthenticationStrategy* New();
    virtual bool IsAuthRequested();
    virtual void GetChallenges();
    virtual void ChooseChallenge();
    
protected:
    virtual ~CNopeAuthenticationStrategy();
    CNopeAuthenticationStrategy();
    void Construct();
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_auth_strategy_nope__) */
