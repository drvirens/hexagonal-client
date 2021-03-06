//
//  http_hook_out_targethost.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/22/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_hook_out_targethost__
#define __vClientTemplateLib__http_hook_out_targethost__

#include "net/http/hooks/http_hook_out.h"

namespace vctl
{
namespace net
{
namespace http
{

class CHttpHookOutgoingTargetHost : public IHttpHookOutgoingPacket
    {
public:
    static CHttpHookOutgoingTargetHost* New();
    virtual bool ProcessPacketHeader(IHttpRequest& aHttpRequest);
    
protected:
    virtual ~CHttpHookOutgoingTargetHost();
    CHttpHookOutgoingTargetHost();
    void Construct();
        
    //friend class vctl::CReferenceThreadSafe<IHttpHookOutgoingPacket>;
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_hook_out_targethost__) */
