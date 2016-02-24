#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "ievent.h"
#include "fastdelegate.h"
#include <list>
#include <unordered_map>
#include <memory>

typedef fastdelegate::FastDelegate1<IEvent*> EventListener;

const unsigned int NUM_EVENT_QUEUES = 2;

// We use objects as our event mechanism so we can pass state around
// These objects are pointers only because we need to store them in a queue together
class EventManager
{
public:
    enum Constants{ eINFINITE = 0xFFFFFFFF };
    // The event manager can either be used as a straight object or a singleton
    // This gives the freedom to use multiple instances for other subsystems
    // while allowing easy access to the main event system
    EventManager(const char* name, bool setAsGlobal);
    ~EventManager();

    // Use these functions to manage your listeners.
    bool AddListener(const EventListener& listener, const EventType& type);
    bool RemoveListener(const EventListener& listener, const EventType& type);

    // Calls the listeners for the event, bypassing the queuing mechanism
	// This will also delete the event
	bool Trigger(IEvent* eventData);

    // Queues up an event to be fired off on the next update
    // This mechanism takes running time into account and makes sure we don't get caught in endless event handling
	// The event manager will delete the event once all listeners are triggered, so don't hang on to it
    bool Queue(IEvent* eventData);

    // Removes the first event of the given type from the queue, or all of the given type if that's enabled
    // Returns whether any events are removed or not, safe to call up to the point when the event is being processed
    bool Abort(const EventType& type, bool all = false);

    // Processes the event queue and optionally sets a maximum on execution time
    // returns true if all events were processed false on timeout
    // if you start getting false too often on this function it's a sign to optimize
    bool Update(unsigned long maxTime = eINFINITE);

    // Returns the global event manager used by the core of the engine
    static EventManager* Get();

private:
    typedef std::list<EventListener> ListenerList;
    typedef std::unordered_map<EventType, ListenerList> ListenerMap;
    typedef std::list<IEvent*> EventQueue;

    ListenerMap mListeners;

    // Since an event listener is likely to trigger new events we keep multiple queues
    // to avoid infinite event processing
    EventQueue mQueues[NUM_EVENT_QUEUES];
    int mActiveQueue;
};

#endif