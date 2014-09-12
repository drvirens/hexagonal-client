//
//  http_core_entity_inputstream.cpp
//  Discount
//
//  Created by Virendra Shakya on 6/9/14.
//  Copyright (c) 2014 Justin. All rights reserved.
//

#include "net/http/detail/http_core_entity_inputstream.h"

namespace vctl
{
namespace net
{
namespace http
{

CHttpEntityInputStream* CHttpEntityInputStream::New(IInputStream* aInputStream, long long aLen)
    {
    CHttpEntityInputStream* obj = new CHttpEntityInputStream(aInputStream, aLen);
    if( obj )
        {
        obj->Construct(aInputStream, aLen);
        }
    return obj;
    }
    
void CHttpEntityInputStream::Construct(IInputStream* aInputStream, long long aLen)
    {
    iContentLength = aLen;
    iContent = new IInputStream[aLen];
    memcpy( iContent, aInputStream, aLen );
    }

long long CHttpEntityInputStream::ContentLength() const
    {
    return iContentLength;
    }
    
bool CHttpEntityInputStream::IsRepeatable() const
    {
    return false;
    }
    
IInputStream* CHttpEntityInputStream::ReadContents()
    {
    return iContent;
    }
    
void CHttpEntityInputStream::WriteContents(IOutputStream* aOutputStream)
    {
    }
    
bool CHttpEntityInputStream::IsStreaming() const
    {
    return true;
    }
    
CHttpEntityInputStream::~CHttpEntityInputStream()
    {
    }

CHttpEntityInputStream::CHttpEntityInputStream(IInputStream* aInputStream, long long aLen)
    : iContent(0) //COnstruct will copy everything internally
    , iContentLength(aLen)
    {}

} //namespace http
} //namespace net
} //namespace vctl
