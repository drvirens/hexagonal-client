//
//  http_manager.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/19/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/detail/http_manager.h"


namespace vctl
{
namespace net
{
namespace http
{

CHttpManager* CHttpManager::New()
    {
    CHttpManager* obj = new CHttpManager();
    if( obj )
        {
        obj->Construct();
        }
    return obj;
    }
    
void CHttpManager::Construct()
    {
    }

CHttpManager::CHttpManager()
    {
    }
    
CHttpManager::~CHttpManager()
    {}
    
void CHttpManager::Execute(CHttpContext* aHttpContext,
    IHttpRequest* aHttpRequest,
    IFutureCallBack* aFutureCallBack)
    {
    }

} //namespace http
} //namespace net
} //namespace vctl
