//
//  thread_un_safe_debug.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/26/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__thread_un_safe_debug__
#define __vClientTemplateLib__thread_un_safe_debug__

namespace vbase
{

class TThreadUnSafe_Debug
{
public:
  static void AssertValidThreadCall() {}
  static void DisOwnThread() {}
};

} //namespace vbase

#endif /* defined(__vClientTemplateLib__thread_un_safe_debug__) */
