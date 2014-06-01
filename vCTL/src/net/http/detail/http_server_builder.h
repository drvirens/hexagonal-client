//
//  http_server_builder.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_server_builder__
#define __vClientTemplateLib__http_server_builder__

#include "base/thread/thread_un_safe.h"
#include "memory/smart_pointer/strong_pointer.h"
#include "net/http/config/http_config_general.h"
#include "net/http/core/http_core_header_map.h"

#include "net/http/decorate/http_actual.h"
#include "net/http/decorate/http_retry_handler.h"
#include "net/http/decorate/http_connection_keep_alive_strategy.h"
#include "net/http/decorate/http_redirect_strategy.h"
#include "net/http/decorate/http_backoff_strategy.h"
#include "net/http/decorate/http_service_unavailable_retry_strategy.h"

#include "net/http/decorate/impl/http_actual_CURL.h"
#include "net/http/decorate/impl/http_connection_reuse_strategy_default.h"
#include "net/http/decorate/impl/http_connection_reuse_strategy_nope.h"
#include "net/http/decorate/impl/http_default_connection_keep_alive_strategy.h"

#include "net/http/auth/http_auth_scheme_provider.h"
#include "net/http/auth/http_credentials_provider.h"
#include "net/http/auth/impl/http_auth_strategy_nope.h"

#include "net/http/hooks/impl/http_hook_out_content.h"
#include "net/http/hooks/impl/http_hook_out_useragent.h"
#include "net/http/hooks/impl/http_hook_out_targethost.h"
#include "net/http/hooks/http_hooks.h"
#include "net/http/hooks/http_hook_out.h"


namespace vctl
{
namespace net
{
namespace http
{
namespace detail
{

class CHttpServer;

class THttpServerBuilder : private vbase::TNotThreadSafe
    {
public:
    THttpServerBuilder();
    ~THttpServerBuilder();
    
    //THttpServerBuilder& SetHttpActualSenderReceiver(vctl::TStrongPointer<IHttpActualSenderReceiver> aIHttpActualSenderReceiver);
    THttpServerBuilder& SetConnectionReuseStrategy(vctl::TStrongPointer<IConnectionReuseStrategy> aIConnectionReuseStrategy);
    THttpServerBuilder& SetConnectionKeepAliveStrategy(vctl::TStrongPointer<IConnectionKeepAliveStrategy> aIConnectionKeepAliveStrategy);
    THttpServerBuilder& SetAuthenticationStrategy(vctl::TStrongPointer<IAuthenticationStrategy> aIAuthenticationStrategy);
    THttpServerBuilder& SetHttpHooks(vctl::TStrongPointer<IHttpHooks> aIHttpHooks);
    THttpServerBuilder& SetRetryHandler(vctl::TStrongPointer<IRetryHandler> aIRetryHandler);
    THttpServerBuilder& SetRedirectStrategy(vctl::TStrongPointer<IRedirectStrategy> aIRedirectStrategy);
    THttpServerBuilder& SetConnectionBackoffStrategy(vctl::TStrongPointer<IConnectionBackoffStrategy> aIConnectionBackoffStrategy);
    THttpServerBuilder& SetServiceUnavailableRetryStrategy(vctl::TStrongPointer<IServiceUnavailableRetryStrategy> aIServiceUnavailableRetryStrategy);
    THttpServerBuilder& SetAuthSchemeProvider(vctl::TStrongPointer<IAuthSchemeProvider> aIAuthSchemeProvider);
    THttpServerBuilder& SetCredentialsProvider(vctl::TStrongPointer<ICredentialsProvider> aICredentialsProvider);
    THttpServerBuilder& SetDefaultHttpHeaders(vctl::TStrongPointer<CHttpHeadersMap> aCHttpHeadersMap);
    
    vctl::TStrongPointer<CHttpServer> Build();
    
protected:
	vctl::TStrongPointer<IHttpActualSenderReceiver> iIHttpActualSenderReceiver;
    vctl::TStrongPointer<IConnectionReuseStrategy> iIConnectionReuseStrategy;
    vctl::TStrongPointer<IConnectionKeepAliveStrategy> iIConnectionKeepAliveStrategy;
    vctl::TStrongPointer<IAuthenticationStrategy> iIAuthenticationStrategy;
    vctl::TStrongPointer<IHttpHooks> iIHttpHooks;
    vctl::TStrongPointer<IRetryHandler> iIRetryHandler;
    vctl::TStrongPointer<IRedirectStrategy> iIRedirectStrategy;
    vctl::TStrongPointer<IConnectionBackoffStrategy> iIConnectionBackoffStrategy;
    vctl::TStrongPointer<IServiceUnavailableRetryStrategy> iIServiceUnavailableRetryStrategy;
    vctl::TStrongPointer<IAuthSchemeProvider> iIAuthSchemeProvider;
    vctl::TStrongPointer<ICredentialsProvider> iICredentialsProvider;
    vctl::TStrongPointer<CHttpHeadersMap> iCHttpHeadersMap;
    
    TGeneralHttpConfig iGeneralHttpConfig;
    };

} //namespace detail
} //namespace http
} //namespace net
} //namespace vctl

#endif /* defined(__vClientTemplateLib__http_server_builder__) */
