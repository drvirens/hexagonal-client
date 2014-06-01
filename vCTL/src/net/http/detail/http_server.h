//
//  http_server.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/19/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_server__
#define __vClientTemplateLib__http_server__

#include <string>
#include "base/thread/thread_un_safe.h"
#include "memory/ref/rc_thread_safe.h"
#include "memory/smart_pointer/strong_pointer.h"

#include "net/http/exec_chain/http_executor_interface.h"
#include "net/http/auth/http_auth_scheme_provider.h"
#include "net/http/auth/http_credentials_provider.h"

namespace vctl
{
namespace net
{
namespace http
{

namespace detail
{

class CHttpServer : public vctl::CReferenceThreadSafe<CHttpServer>
    {
public:
    static CHttpServer* New();
    static CHttpServer* New(IHttpRequestExecutionChain* aIHttpRequestExecutionChain,
                            ICredentialsProvider* aICredentialsProvider,
                            IAuthSchemeProvider* aIAuthSchemeProvider);
    
protected:
    CHttpServer();
    CHttpServer(IHttpRequestExecutionChain* aIHttpRequestExecutionChain,
                            ICredentialsProvider* aICredentialsProvider,
                            IAuthSchemeProvider* aIAuthSchemeProvider);
    void Construct();
    virtual ~CHttpServer();
    friend class vctl::CReferenceThreadSafe<CHttpServer>;
    
private:
    vctl::TStrongPointer<IAuthSchemeProvider> iIAuthSchemeProvider;
    vctl::TStrongPointer<ICredentialsProvider> iICredentialsProvider;
    vctl::TStrongPointer<IHttpRequestExecutionChain> iIHttpRequestExecutionChain;
    };

} //namespace detail
} //namespace http
} //namespace net
} //namespace vctl



#endif /* defined(__vClientTemplateLib__http_server__) */
