//
//  rendezvous_simple.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/11/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "base/synchronize/rendezvous_simple.h"
#include "base/thread_syn_logger/macrologger.h"

namespace vbase
{

static const TSemaphoreValue kRendezvousSimpleValue = 0;

TRendezvous::TRendezvous()
    : iSemaphoreA(kRendezvousSimpleValue)
    , iSemaphoreB(kRendezvousSimpleValue)
    {
    }
    
TRendezvous::~TRendezvous()
    {
    }
    
void TRendezvous::Rendezvous(const ECheckpointType& aCheckpoint)
    {
    
    switch (aCheckpoint) {
    
    case ECheckpoint_First_Arrived: //first == A
        {
        iSemaphoreA.Signal();
        iSemaphoreB.Wait();
        } break;
        
    case ECheckpoint_Second_Arrived: //second == B
        {
        iSemaphoreB.Signal();
        iSemaphoreA.Wait();
        } break;

    default:
        {
        KERNEL_LOG_ERROR("ERROR: Wrong value passed to Rendezvous");
        } break;
    }
    }

} //namespace vbase
