//
//  semaphore_value.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/12/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_semaphore_value_h
#define vClientTemplateLib_semaphore_value_h

#include "build/build_config.h"

#if defined(V_PLATFORM_DARWIN)
typedef int TSemaphoreValue;
#elif defined(V_PLATFORM_ANDROID)
typedef unsigned int TSemaphoreValue;
#else
#error defined typedef for TSemaphoreValue
#endif


#endif
