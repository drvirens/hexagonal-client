//
//  http_hooks.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_hooks__
#define __vClientTemplateLib__http_hooks__

#include "memory/ref/rc_thread_safe.h"
#include "memory/smart_pointer/strong_pointer.h"

namespace vctl
{
namespace net
{
namespace http
{

class IHttpHookOutgoingPacket;

class IHttpHooks : public vctl::CReferenceThreadSafe<IHttpHooks>
    //
    // incoming pakcet = http response coming from remote server
    // for client apps, this hooks is generally not needed
    //
    {
public:
        //transfers ownership
    virtual void Add(vctl::TStrongPointer<IHttpHookOutgoingPacket> aHook) = 0;

protected:
    virtual ~IHttpHooks() {}
    
        
    friend class vctl::CReferenceThreadSafe<IHttpHooks>;
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_hooks__) */
