//
//  task_queue.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/30/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__task_queue__
#define __vClientTemplateLib__task_queue__

#include <queue>
#include "base/task/task.h"

namespace vbase
{

class TTaskQueue : public std::queue<TTask>
    {
public:
    void Swap(TTaskQueue* aQueue)
        {
        c.swap(aQueue->c); // O(1)
        }
    };
    
} //namespace vbase

#endif /* defined(__vClientTemplateLib__task_queue__) */
