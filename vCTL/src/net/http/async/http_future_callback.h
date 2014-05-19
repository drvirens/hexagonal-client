//
//  http_future_callback.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/16/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_future_callback__
#define __vClientTemplateLib__http_future_callback__

//#include "base/lambda/lambda.h"
#include "memory/smart_pointer/strong_pointer.h"
#include "memory/ref/rc_thread_safe.h"

namespace vctl
{
namespace net
{
namespace http
{

//TODO: Make T as strong pointer
template < class HTTP_RESPONSE >
class IFutureCallBack : public vctl::CReferenceThreadSafe<IFutureCallBack <HTTP_RESPONSE> >
    {
public:
    virtual void Failed(int aError) = 0;
    //HTTP_RESPONSE will be in a strong-pointer
    
    virtual void Succeeded(vctl::TStrongPointer<HTTP_RESPONSE> aResponse) = 0;
    virtual void Cancelled() = 0;
    
protected:
    virtual ~IFutureCallBack() {}
    friend class vctl::CReferenceThreadSafe<IFutureCallBack>;
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_future_callback__) */
