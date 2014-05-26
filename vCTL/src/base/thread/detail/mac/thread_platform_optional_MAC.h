//
//  thread_platform_optional_MAC.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/25/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_thread_platform_optional_MAC_h
#define vClientTemplateLib_thread_platform_optional_MAC_h

class MacThreadOptionalImpl
{
public:
  static void OnPreThreadCreate();
  static void OnThreadMainEnter();
  static void OnThreadMainExit();
  static size_t GetDefaultStackSize(const pthread_attr_t& aAttributes);
};


#endif
