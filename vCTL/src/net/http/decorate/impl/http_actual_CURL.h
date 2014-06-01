//
//  http_actual_CURL.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/26/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_actual_CURL__
#define __vClientTemplateLib__http_actual_CURL__

#include "net/http/decorate/http_actual.h"

namespace vctl
{
namespace net
{
namespace http
{
namespace detail
{
class CCurlHttpActualSenderReceiver : public IHttpActualSenderReceiver 
    //
    //actual interface to send/recv http traffic
    //first phase will have cross-platform impl using CURL
    //
    {
public:
    static CCurlHttpActualSenderReceiver* New();
    virtual void DoSend(CHttpContext* aHttpContext, //TODO: remove this. server will create it internally
        IHttpRequest* aHttpRequest);
    virtual void DoReceive();
    virtual void Execute();
    virtual void PreProcess();
    virtual void PostProcess();
    
protected:
    virtual ~CCurlHttpActualSenderReceiver();
    void Construct();
    CCurlHttpActualSenderReceiver();
   // friend class vctl::CReferenceThreadSafe<IHttpActualSenderReceiver>;
    
    };

} //namespace detail
} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_actual_CURL__) */
