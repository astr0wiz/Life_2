#ifndef PUBSUB_H
#define PUBSUB_H
#include <SFML/Window/Event.hpp>
#include <list>

namespace Life
{
    class EventSubscriber; // fwd dec

    class EventPublisher
    {
    public:
        EventPublisher()
        {
            notifyEnabled = true;
        }
        virtual ~EventPublisher() {}
        void subscribe( EventSubscriber* sub )
        {
            subscribers.push_back( sub );
        }
        void unsubscribe( EventSubscriber* sub )
        {
            subscribers.remove( sub );
        }
        void notifyEvent( sf::Event* what = 0, EventSubscriber* sub = 0 );
        void setNotifyEnabled( bool flag )
        {
            notifyEnabled = flag;
        }
        bool getNotifyEnabled()
        {
            return notifyEnabled;
        }
    private:
        bool notifyEnabled;
        std::list<EventSubscriber*> subscribers;
    };

    class EventSubscriber
    {
    public:
        virtual ~EventSubscriber() {}
        virtual void updateEvent( EventPublisher* who, sf::Event* what = 0 ) = 0;
    };

}

#endif // PUBSUB_H
