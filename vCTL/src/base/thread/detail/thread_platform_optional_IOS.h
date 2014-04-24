//
//  thread_platform_optional_IOS.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/22/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_thread_platform_optional_IOS_h
#define vClientTemplateLib_thread_platform_optional_IOS_h

class IOSThreadOptionalImpl
{
public:
  static void OnPreThreadCreate();
  static void OnThreadMainEnter();
  static void OnThreadMainExit();
  static size_t GetDefaultStackSize(const pthread_attr_t& aAttributes);
};


#endif
