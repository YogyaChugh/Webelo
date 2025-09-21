#ifndef EVENTS_DOM
#define EVENTS_DOM

#include "base.cpp"
#include <vector>
#include <variant>
#include <algorithm>
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
        void handleEvent(const Event* event);
};

struct event_listener{
    DOMString type;
    EventListener* callback = nullptr;
    bool capture = false;
    std::optional<bool> passive = std::nullopt;
    bool once = false;
    AbortSignal *signal = nullptr;
    bool removed = false;

    event_listener(const DOMString &type, EventListener* callback = nullptr, bool capture = false,const std::optional<bool> passive = std::nullopt, bool once = false, AbortSignal *signal = nullptr, bool removed = false){
        this->type = type;
        this->callback = callback;
        this->capture = capture;
        this->passive = passive;
        this->once = once;
        this->signal = signal;
        this->removed = removed;
    }

    bool operator==(event_listener &ev) const{
        return (this->type==ev.type && this->callback==ev.callback && this->capture==ev.capture && this->passive==ev.passive && this->once==ev.once && this->signal==ev.signal && this->removed==ev.removed);
    }
    bool operator!=(event_listener &ev) const{
        return !(*this==ev);
    }
};


struct AddEventListenerOptions{
    bool capture;
    bool passive;
    bool once = false;
    AbortSignal *signal;

    AddEventListenerOptions(bool capture, bool passive, bool once, AbortSignal* signal){
        this->capture = capture;
        this->passive = passive;
        this->once = once;
        this->signal = signal;
    }
};

class EventTarget{
    public:
        bool has_activation_behavior = false;
        bool has_legacy_canceled_activation_behavior = false;
        bool has_legacy_pre_activation_behavior = false;

        // These are kept for future use-cases for specific elements in HTML
        std::function<void()> activation_behavior_algorithm = []() {};
        std::function<void()> legacy_canceled_activation_behavior_algorithm = []() {};
        std::function<void()> legacy_pre_activation_behavior_algorithm = []() {};

        std::vector<event_listener*> event_listener_list = {};

        EventTarget(){};

        void addEventListener(const DOMString &type, const EventListener* callback, const std::variant<AddEventListenerOptions,bool> &options);
        void removeEventListener(const DOMString &type, const EventListener* callback, bool capture);
        void removeAllEventListeners();
        bool dispatchEvent(const Event* event);

        bool operator==(const EventTarget &a){
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

        virtual EventTarget* get_the_parent(const Event* event){
            return nullptr;
        }
};

class AbortSignal: public EventTarget{
    protected:
        bool aborted;
        bool dependent = false;
        std::any reason = nullptr;
        EventHandler onabort; //TODO: event handler IDL attribute whose event handler event type is abort.
    public:

        //NEW-OBJECT
        static AbortSignal* abort(std::any reason = nullptr);
        static AbortSignal* timeout(unsigned long long milliseconds);
        static AbortSignal* _any(std::vector<AbortSignal*> signals);


        void throwIfAborted();


        std::vector<AbortSignal*> source_signals = {};
        std::vector<AbortSignal*> dependent_signals = {};

        std::vector<std::function<void()>> abort_algos = {};

        AbortSignal* create_object() {
            return new AbortSignal();
        }

        bool getaborted(){
            return this->aborted;
        }
        bool isaborted(){
            try{
                std::any_cast<std::nullptr_t>(this->reason);
                return false;
            }
            catch(std::bad_any_cast){
                return true;
            }
            return true;
        }
        bool getdependent(){
            return this->dependent;
        }
        bool setdependent(bool dependent){
            this->dependent = dependent;
        }
        std::any getreason(){
            return this->reason;
        }
};

class AbortController{
    protected:
        AbortSignal* signal;
    public:
        AbortController();
        void abort(std::any reason = nullptr) const;

        AbortSignal* getsignal(){
            return this->signal;
        }
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
        this->invocation_target = it;
        this->invocation_target_in_shadow_tree = itst;
        this->shadow_adjusted_target = sat;
        this->related_target = rt;
        this->touch_target_list = ttl;
        this->root_of_closed_tree = rct;
        this->slot_in_closed_tree = sct;
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
        bool composed;
        bool isTrusted = false;
        DOMHighResTimeStamp timeStamp;

    public:

        // Constructor
        Event(const DOMString &type, bool bubbles = false, bool cancelable = false, bool composed = false);
        Event(const Event* temp);

        void inner_event_creation_steps(const Event* event,const Realm* realm,const DOMHighResTimeStamp &time, bool bubbles = false, bool cancelable = false, bool composed = false);

        // FLAGS BRO !!
        bool stop_propagation_flag = false;
        bool stop_immediate_propagation_flag = false;
        bool canceled_flag = false;
        bool in_passive_listener_flag = false;
        bool composed_flag = false;
        bool initialized_flag = false;
        bool dispatch_flag = false;

        // See path_structs for more reference future me :) ! Also, this is 
        std::vector<path_structs> path = {};
        std::vector<EventTarget*> touch_target_list = {}; //mostly no use until TouchEvent Interface

        void initEvent(DOMString const &type, bool bubbles = false, bool cancelable = false); // legacy
        void stopPropagation();
        void stopImmediatePropagation();
        void preventDefault();
        std::vector<EventTarget*> composedPath();
        void set_canceled_flag();

        // *GETTER-SETTER METHODS

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
        CustomEvent(DOMString const &type, bool bubbles = false, bool cancelable = false, bool composed = false, std::any detail = nullptr);
        void initCustomEvent(DOMString const &type, bool bubbles = false, bool cancelable = false, std::any detail = nullptr);

        std::any getdetail() const{
            return this->detail;
        }

        CustomEvent(const CustomEvent* temp): Event(temp->type, temp->bubbles, temp->cancelable, temp->composed){
            this->detail = temp->detail;
        };
};


//Remember to remove when rewriting it
class MouseEvent: public Event{};


#endif