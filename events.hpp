#include "base.hpp"
#include <vector>

class EventTarget{};


// *Phase/State of the Event
enum event_phase: unsigned int{
    NONE = 0;
    CAPTURING_PHASE = 1; //top to bottom
    AT_TARGET = 2; //reached
    BUBBLING_PHASE = 3; //bottom to top again !
}

typedef double DOMHighResTimeStamp; //Should represent a time in milliseconds !

struct EventInit{
    bool bubbles = false,
    bool cancelable = false,
    bool composed = false
}


// *Structs to be stored in path for Event !
struct path_structs{
    EventTarget invocation_target; // the actual EventTarget object where a listener might run
    bool invocation_target_in_shadow_tree; //true if this target is inside a shadow tree
    EventTarget shadow_adjusted_target; //Can be null - The visible target (may be host if shadow is closed)
    EventTarget related_target; //Can be null - Another relevant node (e.g. for mouseover/mouseout events)
    std::vector<EventTarget> touch_target_list = {}; //Touch-specific list of targets (for TouchEvents only)
    bool root_of_closed_tree; // true if the target is the root of a closed shadow DOM
    bool slot_in_closed_tree; // true if the node is a <slot> in a closed shadow DOM
}

class Event{
    private:
        // * NOTE: a potential event target is null or an EventTarget object !

        //* Read-only
        DOMString type = "";
        EventTarget target = null;

        // ! Ommited: EventTarget, it's legacy alias for `target`

        EventTarget relatedTarget = null;
        EventTarget currentTarget;
        enum event_phase eventPhase = NONE;
        bool bubbles;
        bool cancelable;

        // ! Ommitted for function: bool defaultPrevented;

        // Indicating whether or not the event can bubble across the boundary between the shadow DOM and the regular DOM
        bool composed;

        // Indicates whether or not the event was initiated by the browser (after a user click, for instance) or by a script (using an event creation method, for example).
        bool isTrusted; //LEGACY UNFORGEABLE

        // The time at which the event was created (in milliseconds). 
        DOMHighResTimeStamp timeStamp;


        //*Full power baby !! Both readable and editable

        bool returnValue; //legacy

        // Returns the event's path (an array of objects on which listeners will be invoked).
        // This does not include nodes in shadow trees if the shadow root was created with its ShadowRoot.mode closed
        std::vector<EventTarget> composedPath(); //legacy


        // Stops the propagation of events further along in the DOM.
        void stopPropagation();

        // For this particular event, prevent all other listeners from being called.
        // This includes listeners attached to the same element as well as those attached
        // to elements that will be traversed later (during the capture phase, for instance).
        void stopImmediatePropagation();

        // Cancels the event (if it is cancelable).
        void preventDefault();

        // Initializes the value of an Event created. If the event has already been dispatched, this method does nothing. Use the constructor (Event() instead).
        void initEvent(DOMString type, bool bubbles = false, bool cancelable = false) // legacy

        // FLAGS BRO !!
        bool stop_propagation_flag, stop_immediate_propagation_flag, canceled_flag, in_passive_listener_flag, composed_flag, initialized_flag, dispatch_flag;

    public:

        virtual void some_function() const = 0;
        // path storing the different path_structs
        std::vector<struct> path;
        std::vector<EventTarget> touch_target_list = {}; //mostly no use until TouchEvent Interface

        void set_canceled_flag(); //

        // Constructor
        Event(DOMString temptype, EventInit eventInitDict = {});

        // GETTER-SETTER METHODS

        // Read-only !!
        DOMString type(){
            return type;
        };
        EventTarget target(){
            return target;
        };
        EventTarget relatedTarget(){
            return relatedTarget;
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