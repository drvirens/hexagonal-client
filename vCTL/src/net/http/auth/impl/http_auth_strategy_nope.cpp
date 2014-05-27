//
//  http_auth_strategy_nope.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/27/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/auth/impl/http_auth_strategy_nope.h"

namespace vctl
{
namespace net
{
namespace http
{

CNopeAuthenticationStrategy* CNopeAuthenticationStrategy::New()
    {
    CNopeAuthenticationStrategy* obj = new CNopeAuthenticationStrategy();
    if( obj )
        {
        obj->Construct();
        }
    return obj;
    }
    
bool CNopeAuthenticationStrategy::IsAuthRequested()
    {
    return true;
    }
    
void CNopeAuthenticationStrategy::GetChallenges()
    {
    }
    
void CNopeAuthenticationStrategy::ChooseChallenge()
    {
    }
    
CNopeAuthenticationStrategy::~CNopeAuthenticationStrategy()
    {
    }
    
CNopeAuthenticationStrategy::CNopeAuthenticationStrategy()
    {
    }
    
void CNopeAuthenticationStrategy::Construct()
    {
    }
    

} //namespace http
} //namespace net
} //namespace vctl
