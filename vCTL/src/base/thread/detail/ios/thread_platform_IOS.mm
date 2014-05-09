//
//  thread_platform_IOS.mm
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/24/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include <stdio.h>

#include "base/thread/thread_platform.h"
#include "build/build_utils.h"
#include "base/error_handler.h"

//
// NOTE NOTE NOTE NOTE :::: NOTE NOTE NOTE NOTE
//
// DO NOT USE LOG_XXX or LOG(XXX) in here...it will lead to deadlock
//
// NOTE NOTE NOTE NOTE :::: NOTE NOTE NOTE NOTE
//

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
  V_PTHREAD_CALL( pthread_getname_np(pthread_self(), name, kMaxThreadNameLength) );
  return name;
}

} //namespace vbase
