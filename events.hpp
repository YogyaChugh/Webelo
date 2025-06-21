#include "node.hpp"

struct EventInit{
    bool bubbles = false,
    bool canceable = false,
    bool composed = false
}

class Event{
public:
    Event(DOMString type, EventInit eventInitDict = {});

    // The following 2 definitions for value once with _ and once as
    // reference is done to make the values without _ read-only !
    DOMString _type;
    EventTarget _target;
    EventTarget _srcElement;

    DOMString &type = _type;
    EventTarget &target = _target; //can be null
    EventTarget &srcElement = _srcElement; //can be null

    //Legacy
    EventTarget _currentTarget;
    EventTarget &currentTarget = _currentTarget;
    EventTarget* composedPath();

    static const unsigned short NONE = 0;
    static const unsigned short CAPTURING_PHASE = 1;
    static const unsigned short AT_TARGET = 2;
    static const unsigned short BUBBLING_PHASE = 3;

    unsigned short _eventPhase;
    unsigned short &eventPhase = _eventPhase;

    void stopPropagation();
    bool cancelBubble;
    //legacy alias for stopPropagation
    void stopImmediatePropagation();

    bool _bubbles;
    bool &bubbles = _bubbles;

    bool _cancelable;
    bool &cancelable = _cancelable;

    bool returnValue;

    //legacy
    void preventDefault();

    bool _defaultPrevented;
    bool &defaultPrevented = _defaultPrevented;

    bool _composed;
    bool &composed = _composed;


}