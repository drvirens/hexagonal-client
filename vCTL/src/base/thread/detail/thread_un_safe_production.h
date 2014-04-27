//
//  thread_un_safe_production.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/26/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__thread_un_safe_production__
#define __vClientTemplateLib__thread_un_safe_production__

namespace vbase
{
  
  class TThreadUnSafe_Production
  {
  public:
    static void AssertValidThreadCall() {}
    static void DisOwnThread() {}
  };
  
} //namespace vbase


#endif /* defined(__vClientTemplateLib__thread_un_safe_production__) */
