#pragma once

#include "../base.hpp"
#include <vector>
#include <variant>
#include <string>
#include <optional>
#include <any>
#include <functional>
#include <memory>


class EventListener;
struct event_listener;
struct EventListenerOptions;
struct AddEventListenerOptions;
class EventTarget;
class AbortSignal;
class AbortController;
struct EventInit;
struct path_structs;
class Event;
class MouseEvent;
struct CustomEventInit;
class CustomEvent;


// EVENT -TARGET STUFF

class EventListener{
    public:
    void handleEvent(Event event);
};

struct event_listener{
    DOMString type;
    EventListener *callback;
    bool capture = false;
    std::optional<bool> passive = std::nullopt;
    bool once = false;
    AbortSignal *signal;
    bool removed = false;

    bool operator==(event_listener &ev) const{
        return (type==ev.type && callback==ev.callback && capture==ev.capture && passive==ev.passive && once==ev.once && signal==ev.signal && removed==ev.removed);
    }
    bool operator!=(event_listener &ev) const{
        return (type!=ev.type || callback!=ev.callback || capture!=ev.capture || passive!=ev.passive || once!=ev.once || signal!=ev.signal || removed!=ev.removed);
    }
    ~event_listener(){
        callback = nullptr;
        signal = nullptr;
    }
};


struct EventListenerOptions {
    bool capture = false;
};

struct AddEventListenerOptions: EventListenerOptions{
    bool passive;
    bool once = false;
    AbortSignal *signal;
};

class EventTarget{
    public:
        bool has_activation_behavior = false;
        bool has_legacy_canceled_activation_behavior = false;
        bool has_legacy_pre_activation_behavior = false;

        std::function<void()> activation_behavior_algorithm;
        std::function<void()> legacy_canceled_activation_behavior_algorithm;
        std::function<void()> legacy_pre_activation_behavior_algorithm;

        std::vector<event_listener*> event_listener_list = {};

        EventTarget(){};

        void addEventListener(DOMString type, EventListener* callback, std::variant<AddEventListenerOptions,bool> options);
        void removeEventListener(DOMString& type, EventListener* callback, std::variant<AddEventListenerOptions,bool> &options);
        void removeAllEventListeners();
        bool dispatchEvent(Event* event);

        bool dispatch_an_event(Event* event, bool legacy_target_override_flag);

        bool operator==(EventTarget a){
            if (event_listener_list.size()!=a.event_listener_list.size()){
                return false;
            }
            for (size_t i=0; i<event_listener_list.size(); i++){
                if (*(event_listener_list[i])!=*(a.event_listener_list[i])){
                    return false;
                }
            }
            return true;
        }

        event_listener* flatten(DOMString type, EventListener *callback, std::variant<AddEventListenerOptions,bool> options){
            event_listener* temp = new event_listener();
            temp->type = type;
            temp->callback = callback;
            temp->once = false;
            temp->passive = std::nullopt;
            temp->signal = nullptr;
            if (std::holds_alternative<bool>(options)){
                temp->capture = std::get<bool>(options);
            }
            else if (std::holds_alternative<AddEventListenerOptions>(options)){
                auto& opts = std::get<AddEventListenerOptions>(options);
                temp->once = opts.once;
                if (opts.passive){
                    temp->passive = opts.passive;
                }
                if (opts.signal){
                    temp->signal = opts.signal;
                }
            }
            return temp;
        }

        virtual EventTarget* get_the_parent(Event* event){
            return nullptr;
        }
};

class AbortSignal: public EventTarget{
    public:
        bool aborted;
        std::optional<std::any> reason;

        //NEW-OBJECT
        static AbortSignal* abort(std::optional<std::any> reason);
        //TODO: Expose to only Window and Worker
        //TODO: EnforceRange
        static AbortSignal* timeout(unsigned long long milliseconds);
        static AbortSignal* _any(std::vector<AbortSignal*> signals);


        void throwIfAborted();
        EventHandler onabort; //TODO: event handler IDL attribute whose event handler evnet type is abort.
        bool dependent = false;
        std::vector<AbortSignal*> source_signals = {};
        std::vector<AbortSignal*> dependent_signals = {};

        std::vector<std::function<void()>> abort_algos = {};

        AbortSignal* create_object() {
            return new AbortSignal();
        }
};

class AbortController{
    public:
        AbortSignal* signal;
        AbortController();
        void abort(std::optional<std::any> reason = std::nullopt) const;
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
    bool bubbles;
    bool cancelable;
    bool composed;

    EventInit(bool bubb = false, bool canc = false, bool comp = false){
        bubbles = bubb;
        cancelable = canc;
        composed = comp;
    }
};


// *Structs to be stored in path for Event !
struct path_structs{
    EventTarget *invocation_target; // the actual EventTarget object where a listener might run
    bool invocation_target_in_shadow_tree; //true if this target is inside a shadow tree
    EventTarget *shadow_adjusted_target; //Can be null - The visible target (may be host if shadow is closed)
    EventTarget *related_target; //Can be null - Another relevant node (e.g. for mouseover/mouseout events)
    std::vector<EventTarget*> touch_target_list = {}; //Touch-specific list of targets (for TouchEvents only)
    bool root_of_closed_tree; // true if the target is the root of a closed shadow DOM
    bool slot_in_closed_tree; // true if the node is a <slot> in a closed shadow DOM

    path_structs(EventTarget *it, bool itst, EventTarget *sat, EventTarget *rt, std::vector<EventTarget*> ttl, bool rct, bool sct){
        invocation_target = it;
        invocation_target_in_shadow_tree = itst;
        shadow_adjusted_target = sat;
        related_target = rt;
        touch_target_list = ttl;
        root_of_closed_tree = rct;
        slot_in_closed_tree = sct;
    }

    ~path_structs(){
        invocation_target = nullptr;
        shadow_adjusted_target = nullptr;
        related_target = nullptr;
        size_t i = 0;
        while (i<touch_target_list.size()){
            touch_target_list[i] = nullptr;
            i++;
        }
    }
};

class Event{
    public:
        // * NOTE: a potential event target is null or an EventTarget object !

        //* Read-only
        DOMString type = "";
        EventTarget *target = nullptr;

        // ! Ommited: EventTarget? srcElement; it's legacy alias for `target`

        EventTarget *relatedTarget = nullptr;
        EventTarget *currentTarget = nullptr;
        enum event_phase eventPhase = NONE;
        bool bubbles;
        bool cancelable;

        // ! Ommitted for function: bool defaultPrevented

        bool composed;
        bool isTrusted = false; //LEGACY UNFORGEABLE
        DOMHighResTimeStamp timeStamp;

        //*Editable

        // ! Ommitted for function: bool returnV

        // Constructor
        Event(DOMString type, std::unique_ptr<EventInit> eventInitDict = nullptr);

        Event* create_object() {
            return new Event(type);
        }

        // FLAGS BRO !!
        bool stop_propagation_flag = false;
        bool stop_immediate_propagation_flag = false;
        bool canceled_flag, in_passive_listener_flag = false;
        bool composed_flag = false;
        bool initialized_flag = false;
        bool dispatch_flag = false;

        virtual Event* new_instance(){
            return new Event(this->type, std::make_unique<EventInit>(this->bubbles,this->cancelable,this->composed));
        };
        std::vector<std::unique_ptr<path_structs>> path;
        std::vector<EventTarget*> touch_target_list = {}; //mostly no use until TouchEvent Interface

        void initEvent(DOMString &type, bool bubbles = false, bool cancelable = false); // legacy
        void stopPropagation();
        void stopImmediatePropagation();
        void preventDefault();
        std::vector<EventTarget*> composedPath();
        void set_canceled_flag();

        void inner_event_creation_steps(Realm* realm, DOMHighResTimeStamp time, std::unique_ptr<EventInit> dictionary = nullptr);

        // *GETTER-SETTER METHODS

        // Read-only !!
        DOMString gettype(){
            return this->type;
        };
        EventTarget* gettarget(){
            return target;
        };
        EventTarget* getsrcElement(){
            return target;
        }
        EventTarget* getrelatedTarget(){
            return relatedTarget;
        };
        EventTarget* getcurrentTarget(){
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

struct CustomEventInit: public EventInit{
    std::optional<std::any> detail; //will change later

    CustomEventInit(bool bubb=false,bool canc=false,bool comp=false,std::optional<std::any> detail = std::nullopt): EventInit(bubb,canc,comp){
        detail = detail;
    }
};

class CustomEvent: public Event{
    protected:
        std::optional<std::any> detail;
    public:
        CustomEvent(DOMString type, std::unique_ptr<CustomEventInit> eventInitDict = nullptr, std::optional<std::any> detail = std::nullopt);
        void initCustomEvent(DOMString type, bool bubbles = false, bool cancelable = false, std::optional<std::any> detail = std::nullopt); //legacy

        std::optional<std::any> getdetail(){
            return detail;
        }

        CustomEvent* new_instance() override{
            return new CustomEvent(this->type, std::make_unique<CustomEventInit>(this->bubbles,this->cancelable,this->composed,this->detail),this->detail);
        };
};
