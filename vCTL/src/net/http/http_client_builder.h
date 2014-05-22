//
//  http_client_factory.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/16/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_client_factory__
#define __vClientTemplateLib__http_client_factory__

#include "net/http/htpp_client.h"
#include "memory/smart_pointer/strong_pointer.h"

namespace vctl
{
namespace net
{
namespace http
{

class THttpClientBuilder //thread unsafe
    {
public:
    static THttpClientBuilder& Instance();
    
    IHttpClient* DefaultHttpClient();
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_client_factory__) */
