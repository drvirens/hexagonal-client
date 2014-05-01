//
//  event_dispatcher_destructor_spectator.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/1/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_event_dispatcher_destructor_spectator_h
#define vClientTemplateLib_event_dispatcher_destructor_spectator_h


namespace vbase
{
    
class IEventDispatcherDestructorSpectator
    //
    // Interested in watching the deletion of MEventDispatcher object (and take some actions accordingly)?
    // Yes? Be a spectator to a spectacular !! :)
    //
    {
public:
    virtual ~IEventDispatcherDestructorSpectator() {}
    virtual void WillDeleteEventDispatcherOfThisThread() = 0;
    };

} //namespace vbase

#endif
