//
//  thread_platform_optional_IOS.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/23/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "base/thread/detail/ios/thread_platform_optional_IOS.h"

/**
 For multithreaded applications, Cocoa frameworks use locks and other forms of internal synchronization to ensure they behave correctly. To prevent these locks from degrading performance in the single-threaded case, however, Cocoa does not create them until the application spawns its first new thread using the NSThread class. If you spawn threads using only POSIX thread routines, Cocoa does not receive the notifications it needs to know that your application is now multithreaded. When that happens, operations involving the Cocoa frameworks may destabilize or crash your application.
 
 To let Cocoa know that you intend to use multiple threads, all you have to do is spawn a single thread using the NSThread class and let that thread immediately exit. Your thread entry point need not do anything. Just the act of spawning a thread using NSThread is enough to ensure that the locks needed by the Cocoa frameworks are put in place.
 
 If you are not sure if Cocoa thinks your application is multithreaded or not, you can use the isMultiThreaded method of NSThread to check.
 */

void IOSThreadOptionalImpl::OnPreThreadCreate()
    {
#if defined(SIMULATE_SINGLE_THREADED)
    return;
#endif
    static BOOL multithreaded = [NSThread isMultiThreaded];
    if( !multithreaded )
        {
        [NSThread detachNewThreadSelector:@selector(class) toTarget:[NSObject class] withObject:nil];
        multithreaded = YES;
        
            // ASSERT([NSThread isMultiThreaded]);
        }
    }

void IOSThreadOptionalImpl::OnThreadMainEnter()
    {
    }

void IOSThreadOptionalImpl::OnThreadMainExit()
    {
    }

size_t IOSThreadOptionalImpl::GetDefaultStackSize(const pthread_attr_t& aAttributes)
    {
    return 0;
    }
