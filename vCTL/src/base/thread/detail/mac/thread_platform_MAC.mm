//
//  thread_platform_IOS.mm
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/24/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

//#include <stdio.h>
#import <Foundation/Foundation.h>
#include <mach/mach.h>
#include <mach/thread_policy.h>
#include <string>

#include "base/thread/thread_platform.h"
#include "build/build_utils.h"
#include "base/error_handler.h"
#include "base/thread_syn_logger/macrologger.h"

    //
    // NOTE NOTE NOTE NOTE :::: NOTE NOTE NOTE NOTE
    //
    // DO NOT USE LOG_XXX or LOG(XXX) in here...it will lead to deadlock
    //
    // NOTE NOTE NOTE NOTE :::: NOTE NOTE NOTE NOTE
    //

namespace vbase
{
// private iOS functions
static void DoSetNormalPriority(mach_port_t aMachThreadPriority);

    //
    // ---------------------------------------------------------- thread name
    //
static const int kMaxThreadNameLength = 63;

void TPlatformThread::SetName(const char* aName)
    {
    std::string clippedThreadName = std::string(aName).substr(0, kMaxThreadNameLength);
    int e = pthread_setname_np(clippedThreadName.c_str());
    if( 0 != e )
        {
        KERNEL_LOG_ERROR("pthread_setname_np error = [%s]", strerror(errno));
        }
    }

const char* TPlatformThread::Name()
    {
    char* name = new char[kMaxThreadNameLength + 1];
    int e = pthread_getname_np(pthread_self(), name, kMaxThreadNameLength);
    if( 0 != e )
        {
        KERNEL_LOG_ERROR("pthread_getname_np error = [%s]", strerror(errno));
        }
    return name;
    }
    
    
    //
    // ---------------------------------------------------------- thread priority
    //


void TPlatformThread::SetPriority(TPlatformThreadHandle aThreadHandle, EThreadPriority aPriority)
    {
    mach_port_t machthreadid = pthread_mach_thread_np(aThreadHandle.RawHandle());
    switch(aPriority)
        {
    case EThreadPriority_Background:
    case EThreadPriority_Display:
    case EThreadPriority_Realtime:
        //for now, we support only normal
    case EThreadPriority_Normal:
        {
        DoSetNormalPriority(machthreadid);
        } break;
    default:
        {
        
        } break;
        } //switch end
    }
    
void DoSetNormalPriority(mach_port_t aMachThreadPriority)
    {
    thread_standard_policy policy;
    
    thread_act_t thread                     = aMachThreadPriority;
    thread_policy_flavor_t flavor           = THREAD_STANDARD_POLICY;
    thread_policy_t policy_info             = (thread_policy_t)&policy;
    mach_msg_type_number_t policy_infoCnt   = THREAD_STANDARD_POLICY_COUNT;
    
    kern_return_t r = thread_policy_set(thread, flavor, policy_info, policy_infoCnt);
    if(KERN_SUCCESS != r)
        {
        KERNEL_LOG_ERROR( "thread_policy_set failed, error = %d", r );
        }
    }


    
} //namespace vbase
