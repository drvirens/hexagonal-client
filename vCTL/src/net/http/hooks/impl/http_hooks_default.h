//
//  http_hooks_default.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/29/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_hooks_default__
#define __vClientTemplateLib__http_hooks_default__

#include <list>
#include "net/http/hooks/http_hooks.h"
#include "base/synchronize/lock.h"

namespace vctl
{
namespace net
{
namespace http
{

class CDefaultHttpHooks : public IHttpHooks
    {
public:
    static CDefaultHttpHooks* New();
    virtual void Add(vctl::TStrongPointer<IHttpHookOutgoingPacket> aHook);

protected:
    virtual ~CDefaultHttpHooks();
    CDefaultHttpHooks();
    void Construct();

private:
    vbase::TLock iLock; //protects access to iHooksList
    std::list< vctl::TStrongPointer<IHttpHookOutgoingPacket> > iHooksList;
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_hooks_default__) */
