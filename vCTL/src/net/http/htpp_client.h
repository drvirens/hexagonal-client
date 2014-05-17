//
//  htpp_client.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/16/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__htpp_client__
#define __vClientTemplateLib__htpp_client__

#include "net/http/http_method_get.h"
#include "net/http/core/http_core_request.h"

namespace vctl
{
namespace net
{
namespace http
{

class CHttpClient
    {
public:
    void Start();
    void Stop();
    
    void Execute(const IHttpRequest& aHttpRequest);
    };

} //namespace http
} //namespace net
} //namespace vctl

#endif /* defined(__vClientTemplateLib__htpp_client__) */
