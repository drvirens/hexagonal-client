//
//  lock_impl_POSIX.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/23/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "base/synchronize/detail/lock_impl.h"

namespace vbase
{
namespace detail
{
  
  TLockImpl::TLockImpl()
  {
    
  }
  TLockImpl::~TLockImpl()
  {
    
  }
  bool TLockImpl::DoTry()
  {
    return false;
  }
  void TLockImpl::DoLock()
  {
    
  }
  void TLockImpl::DoUnLock()
  {
    
  }
  
} //vbase
} //detail