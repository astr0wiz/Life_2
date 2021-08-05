#include "Life/pubsub.h"

namespace Life
{
    void EventPublisher::notifyEvent( sf::Event* what, EventSubscriber* sub )
    {
        if( notifyEnabled )
        {
            std::list<EventSubscriber*>::iterator p;
            for( p = subscribers.begin(); p != subscribers.end(); p++ )
            {
                if( *p != sub )
                {
                    ( *p )->updateEvent( this, what );
                }
            }
        }
        notifyEnabled = true;
    }
}
