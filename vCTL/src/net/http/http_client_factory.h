//
//  http_client_factory.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/16/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_client_factory__
#define __vClientTemplateLib__http_client_factory__

#include "net/http/htpp_client_default.h"

namespace vctl
{
namespace net
{
namespace http
{

class THttpClientsFactory
    {
public:
    static THttpClientsFactory& Instance();
    
    CHttpClient& DefaultHttpClient();
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_client_factory__) */
