//
//  build_config.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_build_config_h
#define vClientTemplateLib_build_config_h

#if defined(__APPLE__)
#include <TargetConditionals.h>
#endif

#if defined(ANDROID)
  #define       V_PLATFORM_ANDROID 1
#elif defined(__APPLE__)
  #define       V_PLATFORM_DARWIN 1

  #if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
    #define       V_PLATFORM_IOS 1
  #endif
#elif defined(__linux__)
  #define       V_PLATFORM_LINUX 1

  //TODO: Add support for Tizen here
  #if defined(TAGRGET_OS_TIZEN) && TARGET_OS_TIZEN)
    #define       V_PLATFORM_TIZEN 1
  #endif
#elif defined(_WIN32)
  #define       V_PLATFORM_WIN 1
#else
  #error No support for your platform yet. ha ha ha
#endif

//Posix features
#if defined(V_PLATFORM_DARWIN) ||     \
    defined(V_PLATFORM_LINUX)  ||     \
    defined(V_PLATFORM_ANDROID)

  #define V_PLATFORM_POSIX 1
#endif

//Add exceptions for platforms here...


#endif
