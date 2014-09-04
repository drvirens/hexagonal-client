//
//  http_hook_out.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_hook_out__
#define __vClientTemplateLib__http_hook_out__

#include "memory/ref/rc_thread_safe.h"

namespace vctl
{
namespace net
{
namespace http
{

class IHttpRequest;

class IHttpHookOutgoingPacket : public vctl::CReferenceThreadSafe<IHttpHookOutgoingPacket>
    //
    // outgoing packet = outgoing http request
    // this hook will add a http request header to outgoing http packet
    // clients can provide their own hooks, hence ref-counted thread-safety
    //
    {
public:
    virtual bool ProcessPacketHeader(IHttpRequest& aHttpRequest) = 0;
    
protected:
    virtual ~IHttpHookOutgoingPacket() {}
        
    friend class vctl::CReferenceThreadSafe<IHttpHookOutgoingPacket>;
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_hook_out__) */
