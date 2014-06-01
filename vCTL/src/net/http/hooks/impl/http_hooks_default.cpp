//
//  http_hooks_default.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/29/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/hooks/impl/http_hooks_default.h"

namespace vctl
{
namespace net
{
namespace http
{

CDefaultHttpHooks* CDefaultHttpHooks::New()
    {
    CDefaultHttpHooks* obj = new CDefaultHttpHooks();
    if( obj )
        {
        obj->Construct();
        }
    return obj;
    }
    
void CDefaultHttpHooks::Add(vctl::TStrongPointer<IHttpHookOutgoingPacket> aHook)
    {
    vbase::TAutoLock autolock( iLock );
    iHooksList.push_back(aHook);
    }
   

CDefaultHttpHooks::~CDefaultHttpHooks()
    {
    vbase::TAutoLock autolock( iLock );
    while(! iHooksList.empty())
        {
        iHooksList.pop_back();
        }
    }
    
CDefaultHttpHooks::CDefaultHttpHooks()
    {
    }
    
void CDefaultHttpHooks::Construct()
    {
    }
    

} //namespace http
} //namespace net
} //namespace vctl
