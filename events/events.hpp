#pragma once

#include "../base.hpp"
#include <vector>
#include <variant>
#include <string>
#include <optional>
#include <any>

class Event;


// EVENT -TARGET STUFF

class EventListener{
    public:
    void handleEvent(Event event);
};

struct event_listener{
    DOMString type;
    std::optional<EventListener> callback;
    bool capture = false;
    std::optional<bool> passive = std::nullopt;
    bool once = false;
    std::optional<AbortSignal> signal;
    bool removed = false;

    bool operator==(event_listener ev){
        return (type==ev.type && callback==ev.callback && capture==ev.capture && passive==ev.passive && once==ev.once && signal==ev.signal && removed==ev.removed);
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
    public:
        std::vector<event_listener> event_listener_list = {};

        EventTarget(){};

        void addEventListener(DOMString type, std::optional<EventListener> callback, std::variant<AddEventListenerOptions,bool> options);
        void removeEventListener(DOMString type, std::optional<EventListener> callback, std::variant<AddEventListenerOptions,bool> options);
        void removeAllEventListeners();
        bool dispatchEvent(Event& event);

        bool operator==(EventTarget a){
            if (event_listener_list == a.event_listener_list){
                return true;
            }
            return false;
        }

        event_listener* flatten(DOMString type, EventListener callback, std::variant<AddEventListenerOptions,bool> options){
            event_listener* temp = new event_listener();
            temp->type = type;
            temp->callback = callback;
            temp->once = false;
            temp->passive = std::nullopt;
            temp->signal = std::nullopt;
            if (std::holds_alternative<bool>(options)){
                temp->capture = options;
            }
            else if (std::holds_alternative<AddEventListenerOptions>(options)){
                auto& opts = std::get<AddEventListenerOptions>(options);
                temp->once = opts.once;
                temp->passive = opts.passive;
                temp->signal = &opts.signal;
            }
            return temp;
        }

        virtual std::optional<EventTarget> get_the_parent(std::optional<Event> event){
            return std::nullopt;
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
    std::optional<EventTarget> shadow_adjusted_target; //Can be null - The visible target (may be host if shadow is closed)
    std::optional<EventTarget> related_target; //Can be null - Another relevant node (e.g. for mouseover/mouseout events)
    std::vector<std::optional<EventTarget>> touch_target_list = {}; //Touch-specific list of targets (for TouchEvents only)
    bool root_of_closed_tree; // true if the target is the root of a closed shadow DOM
    bool slot_in_closed_tree; // true if the node is a <slot> in a closed shadow DOM

    path_structs(EventTarget it, bool itst, std::optional<EventTarget> sat, std::optional<EventTarget> rt, std::vector<std::optional<EventTarget>> ttl, bool rct, bool sct){
        invocation_target = it;
        invocation_target_in_shadow_tree = itst;
        shadow_adjusted_target = sat;
        related_target = rt;
        touch_target_list = ttl;
        root_of_closed_tree = rct;
        slot_in_closed_tree = sct;
    }
};

class Event{
    protected:
        // * NOTE: a potential event target is null or an EventTarget object !

        //* Read-only
        DOMString type = "";
        std::optional<EventTarget> target = std::nullopt;

        // ! Ommited: EventTarget? srcElement; it's legacy alias for `target`

        std::optional<EventTarget> relatedTarget = std::nullopt;
        std::optional<EventTarget> currentTarget = std::nullopt;
        enum event_phase eventPhase = NONE;
        bool bubbles;
        bool cancelable;

        // ! Ommitted for function: bool defaultPrevented

        bool composed;
        bool isTrusted = false; //LEGACY UNFORGEABLE
        DOMHighResTimeStamp timeStamp;

        //*Editable

        // ! Ommitted for function: bool returnValue

    public:

        // Constructor
        Event(DOMString type, EventInit eventInitDict); //2nd arg to be made optional

        // FLAGS BRO !!
        bool stop_propagation_flag = false;
        bool stop_immediate_propagation_flag = false;
        bool canceled_flag, in_passive_listener_flag = false;
        bool composed_flag = false;
        bool initialized_flag = false;
        bool dispatch_flag = false;

        virtual Event* new_instance(){
            EventInit tempv;
            tempv.bubbles = this->bubbles;
            tempv.cancelable = this->cancelable;
            tempv.composed = this->composed;
            return new Event(this->type,tempv);
        };
        std::vector<path_structs> path;
        std::vector<std::optional<EventTarget>> touch_target_list = {}; //mostly no use until TouchEvent Interface


        void initEvent(DOMString type, bool bubbles, bool cancelable); // legacy
        void stopPropagation();
        void stopImmediatePropagation();
        void preventDefault();
        std::vector<EventTarget> composedPath();
        void set_canceled_flag();

        void inner_event_creation_steps(Realm realm, DOMHighResTimeStamp time, EventInit dictionary);

        // *GETTER-SETTER METHODS

        // Read-only !!
        DOMString gettype(){
            return this->type;
        };
        std::optional<EventTarget> gettarget(){
            return target;
        };
        std::optional<EventTarget> getsrcElement(){
            return target;
        }
        std::optional<EventTarget> getrelatedTarget(){
            return relatedTarget;
        };
        std::optional<EventTarget> getcurrentTarget(){
            return currentTarget;
        };
        enum event_phase geteventPhase(){
            return eventPhase;
        };
        bool getbubbles(){
            return bubbles;
        };
        bool getcancelable(){
            return cancelable;
        };
        bool getdefaultPrevented(){
            if (canceled_flag){
                return true;
            }
            return false;
        };
        bool getcomposed(){
            if (composed_flag){
                return true;
            }
            return false;
        };
        bool getisTrusted(){
            return isTrusted;
        };
        DOMHighResTimeStamp gettimeStamp(){
            return timeStamp;
        };




        //this bubble is legacy alias so remember for js !
        bool getcancelBubble(){
            if (stop_propagation_flag){
                return true;
            }
            return false;
        }
        void setcancelBubble(bool value){
            if (value){
                stop_propagation_flag = true;
            }
        };

        bool getreturnValue(){
            if (canceled_flag){
                return false;
            }
            return true;
        };
        void setreturnValue(bool value){
            if (!value){
                set_canceled_flag();
            }
        };
};


//*TEMPORARY AND SHOULD BE REPLACED !
class MouseEvent: public Event{};

template <typename T>
struct CustomEventInit: EventInit{
    std::optional<std::any> detail = std::nullopt; //will change later
};

class CustomEvent: public Event{
    protected:
        std::any detail;
    public:
        CustomEvent(DOMString type, CustomEventInit eventInitDict);
        void initCustomEvent(DOMString type, bool bubbles, bool cancelable, std::optional<std::any> detail); //legacy

        std::any getdetail(){
            return detail;
        }
};
