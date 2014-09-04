//
//  http_actual.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/19/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_actual__
#define __vClientTemplateLib__http_actual__

#include "memory/ref/rc_thread_safe.h"

namespace vctl
{
namespace net
{
namespace http
{
namespace detail
{
//todo : this must be concrete subclass of actual http send-recv e.g. curl
class IHttpActualSenderReceiver : public vctl::CReferenceThreadSafe<IHttpActualSenderReceiver>
    //
    //actual interface to send/recv http traffic
    //first phase will have cross-platform impl using CURL
    //
    {
public:
    virtual void DoSend() = 0;
    virtual void DoReceive() = 0;
    virtual void Execute() = 0;
    virtual void PreProcess() = 0;
    virtual void PostProcess() = 0;
    
protected:
    virtual ~IHttpActualSenderReceiver();
    friend class vctl::CReferenceThreadSafe<IHttpActualSenderReceiver>;
    
    };

} //namespace detail
} //namespace http
} //namespace net
} //namespace vctl




#endif /* defined(__vClientTemplateLib__http_actual__) */
