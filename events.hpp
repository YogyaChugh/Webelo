#include "base.hpp"
#include <vector>

class EventTarget{};

enum event_phase: unsigned int{
    NONE = 0;
    CAPTURING_PHASE = 1;
    AT_TARGET = 2;
    BUBBLING_PHASE = 3;
}

typedef double DOMHighResTimeStamp; //Should represent a time in milliseconds !

struct EventInit{
    bool bubbles = false,
    bool canceable = false,
    bool composed = false
}

struct path_structs{
    EventTarget invocation_target;
    bool invocation_target_in_shadow_tree;
    EventTarget shadow_adjusted_target; //Can be null
    EventTarget related_target; //Can be null
    std::vector<EventTarget> touch_target_list = {};
    bool root_of_closed_tree;
    bool slot_in_closed_tree;
}

class Event{
    private:
        //Read-only
        DOMString type = ""; //e.g. "click", "haschange" or "submit"

        //This stores a potential event target ! either null or an EventTarget object !
        EventTarget target = null; //can be null
        EventTarget target = null; //can be null //legacy

        //This also stores an event target but it is for related targets like for mouse events
        //it stores like the element the mouse came from or is going to ! mainly for reference !
        EventTarget relatedTarget = null; //can be null
        EventTarget currentTarget; //can be null  // Returns the object whose event listener’s callback is currently being invoked.
        enum event_phase eventPhase = NONE; // one of the top definitions
        bool bubbles;
        bool cancelable;
        bool defaultPrevented;
        bool composed;
        bool isTrusted; //LEGACY UNFORGEABLE
        DOMHighResTimeStamp timeStamp;

        // NOTE: a potential event target is null or an EventTarget object !


        //Full power baby !!
        bool returnValue; //legacy
        std::vector<EventTarget> composedPath(); //legacy

        void stopPropagation();
        void stopImmediatePropagation();
        void preventDefault();
        void initEvent(DOMString type, bool bubbles = false, bool cancelable = false) //legacy

        bool stop_propagation_flag, stop_immediate_propagation_flag, canceled_flag, in_passive_listener_flag, composed_flag, initialized_flag, dispatch_flag;

    public:

        std::vector<struct> path;
        std::vector<EventTarget> touch_target_list = {};

        void set_canceled_flag();

        Event(DOMString temptype, EventInit eventInitDict = {});

        // GETTER-SETTER METHODS

        //Read-only !!
        DOMString type(){
            return type;
        };
        EventTarget target(){
            return target;
        };
        EventTarget relatedTarget(){
            return relatedTarget;
        };

        EventTarget srcElement(){
            //legacy
            return target;
        };
        EventTarget currentTarget(){
            return currentTarget;
        };
        unsigned short eventPhase(){
            return eventPhase;
        };
        bool bubbles(){
            return bubbles;
        };
        bool cancelable(){
            return cancelable;
        };
        bool defaultPrevented(){
            return canceled_flag;
        };
        bool composed(){
            return composed_flag;
        };
        bool isTrusted(){
            return isTrusted;
        };
        DOMHighResTimeStamp timeStamp(){
            return timeStamp;
        };

        //Full power ones !

        //this bubble is legacy alias so remember for js !
        bool cancelBubble(){
            return stop_propagation_flag;
        };
        void setcancelBubble(bool value){
            if (value){
                stop_propagation_flag = true;
            }
        };

        bool returnValue(){
            return !canceled_flag;
        };
        void setreturnValue(bool value){
            if (!value){
                set_canceled_flag();
            }
        };
}

void Event::Event(DOMString temptype, EventInit eventInitDict = {}){
    type = temptype;
    if (eventInitDict!={}){
        bubbles = eventInitDict.bubbles;
        cancelable = eventInitDict.cancelable;
    }
};

void Event::stopPropagation(){
    stop_propagation_flag = true;
};

void Event::stopImmediatePropagation(){
    stop_propagation_flag = true;
    stop_immediate_propagation_flag = true;
};

void Event::set_canceled_flag(){
    if (cancelable and !in_passive_listener_flag){
        canceled_flag = true;
    }
}

void Event::preventDefault(){
    set_canceled_flag();
};

void initEvent(DOMString type, bool bubbles = false, bool cancelable = false){
    if (dispatch_flag){
        return;
    }
    isTrusted = false;
    initialized_flag = true;
    stop_propagation_flag = false;
    stop_immediate_propagation_flag = false;
    canceled_flag = false;
    target = null;
    type = temptype;
    bubbles = eventInitDict.bubbles;
    cancelable = eventInitDict.cancelable;
}