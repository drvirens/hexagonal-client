//
//  http_hook_out_defaultheaders.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/29/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_hook_out_defaultheaders__
#define __vClientTemplateLib__http_hook_out_defaultheaders__


#include "net/http/hooks/http_hooks.h"
#include "net/http/core/http_core_header_map.h"

namespace vctl
{
namespace net
{
namespace http
{

class CHttpHookOutgoingDefaultHeaders : public IHttpHookOutgoingPacket
    {
public:
    static CHttpHookOutgoingDefaultHeaders* New(vctl::TStrongPointer<CHttpHeadersMap> aCHttpHeadersMap);
    virtual bool ProcessPacketHeader(IHttpRequest& aHttpRequest);

protected:
    virtual ~CHttpHookOutgoingDefaultHeaders();
    CHttpHookOutgoingDefaultHeaders();
    void Construct();

private:
    };

} //namespace http
} //namespace net
} //namespace vctl

#endif /* defined(__vClientTemplateLib__http_hook_out_defaultheaders__) */
