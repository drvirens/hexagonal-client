//
//  thread_un_safe.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/26/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__thread_un_safe__
#define __vClientTemplateLib__thread_un_safe__

#if !defined(NDEBUG)
#include "base/thread/detail/thread_un_safe_debug.h"
#else
#include "base/thread/detail/thread_un_safe_production.h"
#endif

#include "build/build_utils.h"
#include "base/logging/log.h"


//find out if a given class is calling the methods on valid thread
//DESIGN: this framework supports message-passing as a way of communicating between multiple threads.
//        synchronisation using locking for shared data structures is not be used while using this framework.
//        hence, your code MUST NOT be threadsafe.
//        instead, your code must be thread-unsafe.
//        since it is going to be thread-unsafe code, we need to put some basic assumptions regarding
//        the communication between threads.
//        the rule of thumb to follow: your c++ objects must live on ONLY ONE thread.
//        if you want to talk with other threads to do some work, then you do that by using
//        the messages. (link here to message class later when it is designed)
//        the messages are generally POSTED to other threads, alongiwth callbacks, if any.
//        the other thread will do the job and call your callback (on your own thread).

namespace vbase
{
  template<class THREAD_UNSAFE>
  class TThreadUnSafe
  {
  public:
    TThreadUnSafe()
    {
      
    }
    ~TThreadUnSafe()
    {
      mThreadSafe.AssertValidThreadCall();
    }
    //assert that c++ object is calling the method on same thread on which its' constructor ran
    void AssertValidThreadCall()
    {
      bool r = mThreadSafe.AssertValidThreadCall();
      ASSERT(r == true);
      if( r == false )
      {
        LOG_FATAL << "AssertValidThreadCall failed indicating : you can call methods on the thread that created it unless you disown the thread";
      }
    }
    
  protected:
    //disown the thread on which the object was created. this is
    //more like what Siddhartha did lol disowned his family
    //after this call, the c++ object will be able to call its methods
    //on different thread.
    //this method is protected and the derivers of this class
    //should prolly always keep this method private and not expose
    //to outside world. but the flexibility is given here to do
    //whatever the fuck you wanna do with your derived class object.
    void DisOwnThread()
    {
      mThreadSafe.DisOwnThread();
    }
    
  private:
    THREAD_UNSAFE mThreadSafe;
  };
  

#if !defined(NDEBUG)
  typedef TThreadUnSafe<TThreadUnSafe_Debug> TNotThreadSafe;
#else
  typedef TThreadUnSafe<TThreadUnSafe_Production> TNotThreadSafe;
#endif
} //namespace vbase

#endif /* defined(__vClientTemplateLib__thread_un_safe__) */
