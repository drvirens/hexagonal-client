//
//  run_loop_scoped_autorelease_pool.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/28/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_run_loop_scoped_autorelease_pool_h
#define vClientTemplateLib_run_loop_scoped_autorelease_pool_h

#if defined(V_PLATFORM_IOS)
#import <Foundation/Foundation.h>

#include "base/runloop/detail/darwin/run_loop_DArWIN.h"

namespace vbase {
namespace detail {

//RAII
#if 0 //use @autoreleasepool block
class TScopedAutoreleasePool
{
public:
  explicit TScopedAutoreleasePool(CRunLoopCFRunLoopBase* aCRunLoopCFRunLoopBase)
    : mPool( aCRunLoopCFRunLoopBase->CreateAutoreleasePool() )
  {
    
  }
  
  ~TScopedAutoreleasePool()
  {
    [mPool drain];
  }
private:
  NSAutoreleasePool* mPool;
};
#endif
  
} //namespace detail
} // namespace vbase

#endif

#endif
