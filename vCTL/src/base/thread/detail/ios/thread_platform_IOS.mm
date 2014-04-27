//
//  thread_platform_IOS.mm
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/24/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include <stdio.h>

#include "base/thread/thread_platform.h"
#include "base/logging/log.h"
#include "build/build_utils.h"
#include "base/error_handler.h"


namespace vbase
{

static const int kMaxThreadNameLength = 63;
void TPlatformThread::SetName(const char* aName)
{
  std::string clippedThreadName = std::string(aName).substr(0, kMaxThreadNameLength);
  V_PTHREAD_CALL( pthread_setname_np(clippedThreadName.c_str()) );
}

const char* TPlatformThread::Name()
{
  char* name = new char[kMaxThreadNameLength + 1];
  V_PTHREAD_CALL( pthread_getname_np(TPlatformThread::CurrentHandle().RawHandle(), name, kMaxThreadNameLength) );
  //LOG_INFO << "ThreadName: " << name;
  return name;
}

} //namespace vbase
