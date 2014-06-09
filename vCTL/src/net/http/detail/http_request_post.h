//
//  http_request_post.h
//  Discount
//
//  Created by Virendra Shakya on 6/9/14.
//  Copyright (c) 2014 Justin. All rights reserved.
//

#ifndef __Discount__http_request_post__
#define __Discount__http_request_post__


#include "net/http/detail/http_request_base.h"
#include "net/http/core/http_core_method_type.h"

namespace vctl
{
namespace net
{
namespace http
{

class CHttpRequestPost : public CHttpRequestBase
    {
public:
    explicit CHttpRequestPost(const std::string& aUri)
        : CHttpRequestBase(aUri)
        {}
        
    virtual EHttpMethodType HttpMethod() const
        {
        return kHttpMethodPost;
        }
        
    virtual void SetHttpEntity(IHttpEntity* aIHttpEntity)
        {
        iIHttpEntity = aIHttpEntity;
        }
        
    virtual IHttpEntity* HttpEntity() const
        {
        return iIHttpEntity;
        }
    
private:
    IHttpEntity* iIHttpEntity;
    };
    
} //namespace http
} //namespace net
} //namespace vctl



#endif /* defined(__Discount__http_request_post__) */
