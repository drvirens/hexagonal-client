//
//  http_actual_CURL.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/26/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/decorate/impl/http_actual_CURL.h"

namespace vctl
{
namespace net
{
namespace http
{
namespace detail
{

void CCurlHttpActualSenderReceiver::DoSend(CHttpContext* aHttpContext,
        IHttpRequest* aHttpRequest)
    {
    LOG_INFO << "CCurlHttpActualSenderReceiver::DoSend";
    
    }
    
void CCurlHttpActualSenderReceiver::DoReceive()
    {
    }
    
void CCurlHttpActualSenderReceiver::Execute()
    {
    }
    
void CCurlHttpActualSenderReceiver::PreProcess()
    {
    }
    
void CCurlHttpActualSenderReceiver::PostProcess()
    {
    }
    
CCurlHttpActualSenderReceiver::~CCurlHttpActualSenderReceiver()
    {
    }
    
void CCurlHttpActualSenderReceiver::Construct()
    {
    }
    
CCurlHttpActualSenderReceiver::CCurlHttpActualSenderReceiver()
    {
    }
    
CCurlHttpActualSenderReceiver* CCurlHttpActualSenderReceiver::New()
    {
    CCurlHttpActualSenderReceiver* obj = new CCurlHttpActualSenderReceiver();
    if( obj )
        {
        obj->Construct();
        }
    return obj;
    }
    
    

} //namespace detail
} //namespace http
} //namespace net
} //namespace vctl
