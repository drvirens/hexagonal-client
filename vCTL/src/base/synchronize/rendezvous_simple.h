//
//  rendezvous_simple.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/11/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__rendezvous_simple__
#define __vClientTemplateLib__rendezvous_simple__

#include "base/non_copyable.h"
#include "base/synchronize/semaphore.h"

namespace vbase
{

//intended to work with 2 threads only
class TRendezvous : private TNonCopyable<TRendezvous>
    {
public:
    enum ECheckpointType
        {
        ECheckpoint_First_Arrived,
        ECheckpoint_Second_Arrived
        };
    TRendezvous();
    ~TRendezvous();
    
    void Rendezvous(const ECheckpointType& aCheckpoint);
    
private:
    TSemaphore iSemaphoreA;
    TSemaphore iSemaphoreB;
    };

} //namespace vbase

#endif /* defined(__vClientTemplateLib__rendezvous_simple__) */
