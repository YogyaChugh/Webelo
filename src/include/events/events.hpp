#ifndef "EVENTS_DOM"
#define "EVENTS_DOM"

#include "../base.hpp"
#include <vector>
#include <variant>
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
struct path_structs;
class Event;
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

        void addEventListener(DOMString &type, EventListener* callback, std::variant<AddEventListenerOptions,bool> options);
        void removeEventListener(DOMString &type, EventListener* callback, std::variant<AddEventListenerOptions,bool> &options);
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
    NONE,
    CAPTURING_PHASE, //top to bottom
    AT_TARGET, //reached
    BUBBLING_PHASE //bottom to top again !
};

// *Structs to be stored in path for Event !
struct path_structs{
    EventTarget* invocation_target;
    bool invocation_target_in_shadow_tree;
    EventTarget *shadow_adjusted_target;
    EventTarget *related_target;
    std::vector<EventTarget*> touch_target_list = {};
    bool root_of_closed_tree;
    bool slot_in_closed_tree;

    path_structs(EventTarget *it, bool itst, EventTarget *sat, EventTarget *rt, std::vector<EventTarget*> ttl, bool rct, bool sct){
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
        DOMString type = "";
        EventTarget *target = nullptr;
        EventTarget *relatedTarget = nullptr;
        EventTarget *currentTarget = nullptr;
        enum event_phase eventPhase = NONE;
        bool bubbles;
        bool cancelable;

        // ! Ommitted for function: bool defaultPrevented

        bool composed;
        bool isTrusted = false;
        DOMHighResTimeStamp timeStamp;

    public:

        // Constructor
        Event(DOMString const &type, bool bubbles = false, bool cancelable = false, bool composed = false);
        Event(Event* temp);

        void inner_event_creation_steps(Event* event, Realm* realm, DOMHighResTimeStamp &time, bool bubbles = false, bool cancelable = false, bool composed = false);

        // FLAGS BRO !!
        bool stop_propagation_flag = false;
        bool stop_immediate_propagation_flag = false;
        bool canceled_flag = false;
        bool in_passive_listener_flag = false;
        bool composed_flag = false;
        bool initialized_flag = false;
        bool dispatch_flag = false;

        // See path_structs for more reference future me :) ! Also, this is 
        std::vector<std::unique_ptr<path_structs>> path = {};

        std::vector<EventTarget*> touch_target_list = {}; //mostly no use until TouchEvent Interface

        void initEvent(DOMString const &type, bool bubbles = false, bool cancelable = false); // legacy
        void stopPropagation() inline;
        void stopImmediatePropagation() inline;
        void preventDefault();
        std::vector<EventTarget*> composedPath();
        void set_canceled_flag() inline;

        // *GETTER-SETTER METHODS

        // Read-only !!
        DOMString gettype() const{
            return this->type;
        };
        EventTarget* gettarget() const{
            return this->target;
        };
        EventTarget* getsrcElement() const{
            return this->target;
        }
        EventTarget* getrelatedTarget() const{
            return this->relatedTarget;
        };
        EventTarget* getcurrentTarget() const{
            return this->currentTarget;
        };
        enum event_phase geteventPhase() const{
            return this->eventPhase;
        };
        bool getbubbles() const{
            return this->bubbles;
        };
        bool getcancelable() const{
            return this->cancelable;
        };
        bool getdefaultPrevented() const{
            return this->canceled_flag;
        };
        bool getcomposed() const{
            return this->composed_flag;
        };
        bool getisTrusted() const{
            return this->isTrusted;
        };
        DOMHighResTimeStamp gettimeStamp() const{
            return this->timeStamp;
        };

        bool getcancelBubble() const{
            return this->stop_propagation_flag;
        }
        void setcancelBubble(bool value){
            if (value){
                this->stop_propagation_flag = true;
            }
        };

        bool getreturnValue() const{
            return !this->canceled_flag;
        };
        void setreturnValue(bool value){
            if (!value){
                this->set_canceled_flag();
            }
        };
};


class CustomEvent: public Event{
    protected:
        std::any detail = nullptr;
    public:
        CustomEvent(DOMString &type, bool bubbles = false, bool cancelable = false, bool composed = false, std::any &detail = nullptr);
        void initCustomEvent(DOMString &type, bool bubbles = false, bool cancelable = false, std::any &detail = nullptr);

        std::any getdetail(){
            return this->detail;
        }

        CustomEvent(CustomEvent* temp): Event(temp->type, temp->bubbles, temp->cancelable, temp->composed){
            this->detail = temp->detail;
        };
};


#endif