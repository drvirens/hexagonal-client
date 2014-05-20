//
//  http_manager.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/19/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_manager__
#define __vClientTemplateLib__http_manager__

#include "base/thread/thread_un_safe.h"
#include "net/http/core/http_core_request.h"
#include "net/http/core/http_core_response.h"
#include "net/http/async/http_future_callback.h"
#include "net/http/core/http_core_request_execute_chain.h"

namespace vctl
{
namespace net
{
namespace http
{

class CHttpContext;
class CHttpServer;

class CHttpManager : private vbase::TNotThreadSafe
    //
    //all the functions of this class must be executed on SAME thread
    //generally the http-module will schedule an http request
    //on one of the worker threads
    //
    {
public:
    static CHttpManager* New();
    
    virtual ~CHttpManager();
    
    void Execute(CHttpContext* aHttpContext,
        IHttpRequest* aHttpRequest,
        IFutureCallBack* aFutureCallBack);
    
private:
    CHttpManager();
    void Construct();
    
private:
    CHttpServer* iHttpServer;
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_manager__) */
