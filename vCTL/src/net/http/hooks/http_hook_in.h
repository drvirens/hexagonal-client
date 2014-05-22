//
//  http_hook_in.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_hook_in__
#define __vClientTemplateLib__http_hook_in__

#include "memory/ref/rc_thread_safe.h"

namespace vctl
{
namespace net
{
namespace http
{

class IHttpResponse;

class IHttpHookIncomingPacket : private vctl::CReferenceThreadSafe<IHttpHookIncomingPacket>
    //
    // incoming pakcet = http response coming from remote server
    // for client apps, this hooks is generally not needed
    //
    {
public:
    virtual bool ProcessPacketHeader(IHttpResponse& aHttpResponse) = 0;
protected:
    virtual ~IHttpHookIncomingPacket() {}
        
    friend class vctl::CReferenceThreadSafe<IHttpHookIncomingPacket>;
    };

} //namespace http
} //namespace net
} //namespace vctl

#endif /* defined(__vClientTemplateLib__http_hook_in__) */
