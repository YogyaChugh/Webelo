#include "../base.hpp"
#include <vector>
#include <variant>
#include <string>
#include <optional>

class Event;


// EVENT -TARGET STUFF

class EventListener{
    public:
    void handleEvent(Event event);
};

struct event_listener{
    DOMString type;
    EventListener* callback;
    bool capture = false;
    std::optional<bool> passive = std::nullopt;
    bool once = false;
    AbortSignal* signal;
    bool removed = false;

    bool operator==(event_listener ev){
        if (type==ev.type && callback==ev.callback && capture==ev.capture && passive==ev.passive && once==ev.once && signal==ev.signal && removed==ev.removed){
            return true;
        }
        return false;
    }
};


struct EventListenerOptions {
    bool capture = false;
};

struct AddEventListenerOptions: EventListenerOptions{
    bool passive;
    bool once = false;
    AbortSignal signal;
};

class EventTarget{
    private:
        std::vector<event_listener> event_listener_list = {};
    public:
        EventTarget(){};

        void addEventListener(DOMString type, EventListener callback, std::variant<AddEventListenerOptions,bool> options);
        void removeEventListener(DOMString type, EventListener callback, std::variant<AddEventListenerOptions,bool> options);
        void removeAllEventListeners();
        bool dispatchEvent(Event& event);

        bool operator==(EventTarget a){
            return true;
        }


        //TODO: Implement the get_the_parent algo

        event_listener* flatten(DOMString type, EventListener callback, std::variant<AddEventListenerOptions,bool> options){
            event_listener* temp = new event_listener();
            temp->type = type;
            temp->callback = &callback;
            temp->once = false;
            temp->passive = std::nullopt;
            temp->signal = nullptr;
            if (std::holds_alternative<bool>(options)){
                temp->capture = false;
            }
            else if (std::holds_alternative<AddEventListenerOptions>(options)){
                auto& opts = std::get<AddEventListenerOptions>(options);
                temp->once = opts.once;
                temp->passive = opts.passive;
                temp->signal = &opts.signal;
            }
            return temp;
        }
};



// *Phase/State of the Event
enum event_phase: unsigned int{
    NONE = 0,
    CAPTURING_PHASE = 1, //top to bottom
    AT_TARGET = 2, //reached
    BUBBLING_PHASE = 3 //bottom to top again !
};

typedef double DOMHighResTimeStamp; //Should represent a time in milliseconds !

struct EventInit{
    bool bubbles = false;
    bool cancelable = false;
    bool composed = false;
};


// *Structs to be stored in path for Event !
struct path_structs{
    EventTarget invocation_target; // the actual EventTarget object where a listener might run
    bool invocation_target_in_shadow_tree; //true if this target is inside a shadow tree
    EventTarget shadow_adjusted_target; //Can be null - The visible target (may be host if shadow is closed)
    EventTarget related_target; //Can be null - Another relevant node (e.g. for mouseover/mouseout events)
    std::vector<EventTarget> touch_target_list = {}; //Touch-specific list of targets (for TouchEvents only)
    bool root_of_closed_tree; // true if the target is the root of a closed shadow DOM
    bool slot_in_closed_tree; // true if the node is a <slot> in a closed shadow DOM
};

class Event{
    protected:
        // * NOTE: a potential event target is null or an EventTarget object !

        //* Read-only
        DOMString type = "";
        EventTarget target;

        // ! Ommited: EventTarget, it's legacy alias for `target`

        EventTarget relatedTarget;
        EventTarget currentTarget;
        enum event_phase eventPhase = NONE;
        bool bubbles;
        bool cancelable;

        // ! Ommitted for function: bool defaultPrevented

        bool composed;
        bool isTrusted; //LEGACY UNFORGEABLE
        DOMHighResTimeStamp timeStamp;

        //*Editable

        // ! Ommitted for function: bool returnValue

        std::vector<EventTarget> composedPath();
        void stopPropagation();
        void stopImmediatePropagation();
        void preventDefault();
        void initEvent(DOMString type, bool bubbles, bool cancelable); // legacy

        // FLAGS BRO !!
        bool stop_propagation_flag, stop_immediate_propagation_flag, canceled_flag, in_passive_listener_flag, composed_flag, initialized_flag, dispatch_flag;

    public:

        virtual Event* new_instance(){
            EventInit tempv;
            tempv.bubbles = this->bubbles;
            tempv.cancelable = this->cancelable;
            tempv.composed = this->composed;
            return new Event(this->type,tempv);
        };
        std::vector<path_structs> path;
        std::vector<EventTarget> touch_target_list = {}; //mostly no use until TouchEvent Interface

        void set_canceled_flag();

        // Constructor
        Event(DOMString type, EventInit eventInitDict);

        void inner_event_creation_steps(Realm realm, DOMHighResTimeStamp time, EventInit dictionary);

        // *GETTER-SETTER METHODS

        // Read-only !!
        DOMString gettype(){
            return this->type;
        };
        EventTarget gettarget(){
            return target;
        };
        EventTarget getrelatedTarget(){
            return relatedTarget;
        };
        EventTarget getcurrentTarget(){
            return currentTarget;
        };
        unsigned short geteventPhase(){
            return eventPhase;
        };
        bool getbubbles(){
            return bubbles;
        };
        bool getcancelable(){
            return cancelable;
        };
        bool getdefaultPrevented(){
            return canceled_flag;
        };
        bool getcomposed(){
            return composed_flag;
        };
        bool getisTrusted(){
            return isTrusted;
        };
        DOMHighResTimeStamp gettimeStamp(){
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
};


struct CustomEventInit: EventInit{
    DOMString detail; //will change later
};

class CustomEvent: public Event{
    protected:
        DOMString detail;
    public:
        CustomEvent(DOMString type, CustomEventInit eventInitDict);
        void initCustomEvent(DOMString type, DOMString detail, bool bubbles, bool cancelable); //legacy

        DOMString getdetail(){
            return detail;
        }
};
