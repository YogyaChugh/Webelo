#include "src/base.cpp"
#include "src/exceptions.cpp"
#include <vector>
#include <variant>
#include <algorithm>
#include <optional>
#include <any>
#include <functional>
#include <memory>
#include <cassert>
#include <iostream>


// Macros

#define DOCUMENT_POSITION_DISCONNECTED 0x01
#define DOCUMENT_POSITION_PRECEDING 0x02
#define DOCUMENT_POSITION_FOLLOWING 0x04
#define DOCUMENT_POSITION_CONTAINS 0x08
#define DOCUMENT_POSITION_CONTAINED_BY 0x10
#define DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC 0x20


// Class Declarations

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
class Node;
class NodeList;
class Document;
class Element;


// Enums

// Types of Node objects possible !!
enum node_type{
    ELEMENT_NODE = 1,
    ATTRIBUTE_NODE = 2,
    TEXT_NODE = 3,
    CDATA_SECTION_NODE = 4,
    ENTITY_REFERENCE_NODE = 5,
    ENTITY_NODE = 6,
    PROCESSING_INSTRUCTION_NODE = 7,
    COMMENT_NODE = 8,
    DOCUMENT_NODE = 9,
    DOCUMENT_TYPE_NODE = 10,
    DOCUMENT_FRAGMENT_NODE = 11,
    NOTATION_NODE = 12
};


// Algos (functions) declarations

event_listener* flatten(DOMString &type, EventListener *callback, std::variant<AddEventListenerOptions,bool> options);
void remove_event_listener(EventTarget* eventTarget, event_listener *listener);
void add_abort_algo(const std::function<void()> &algo, AbortSignal* signal);
void run_abort_steps(AbortSignal* signal);
void signal_abort(AbortSignal* signal, std::any reason = nullptr);
void add_event_listener(EventTarget* eventTarget, event_listener *listener);
AbortSignal* create_dependent_abort_signal(std::vector<AbortSignal*> signals, AbortSignal* signalInterface = nullptr, Realm* realm = nullptr);
bool fire_event(DOMString e,EventTarget* target,Event* temporary_class = nullptr ,bool legacy_target_override_flag = false);
Event* create_event(Event* eventInterface, Realm* realm = nullptr);

//hehe
bool default_passive_value(const DOMString &type, EventTarget* eventTarget){return false;}
bool dispatch_event(Event* event, EventTarget* target, std::optional<bool> legacy_target_override_flag = std::nullopt, std::optional<bool> legacy_output_did_listeners_throw_flag = std::nullopt){ return true;}


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
    std::optional<bool> passive = std::nullopt;
    bool once = false;
    AbortSignal *signal;

    AddEventListenerOptions(bool capture, std::optional<bool> passive, bool once, AbortSignal* signal = nullptr){
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
        std::function<void(Event* event)> activation_behavior_algorithm = [](Event* event) {};
        std::function<void()> legacy_canceled_activation_behavior_algorithm = []() {};
        std::function<void()> legacy_pre_activation_behavior_algorithm = []() {};

        std::vector<event_listener*> event_listener_list = {};

        EventTarget(){};

        void addEventListener(DOMString &type, EventListener* callback, std::variant<AddEventListenerOptions,bool> &options);
        void removeEventListener(DOMString &type, EventListener* callback, bool capture);
        void removeAllEventListeners();
        bool dispatchEvent(Event* event);

        bool operator==(const EventTarget &a){
            if (this->event_listener_list.size()!=a.event_listener_list.size()){
                return false;
            }

            for (size_t i=0; i<this->event_listener_list.size(); i++){
                if (*(this->event_listener_list[i])!=*(a.event_listener_list[i])){
                    return false;
                }
            }
            return true;
        }

        bool operator!=(const EventTarget &a){
            return !(*this==a);
        }

        virtual EventTarget* get_the_parent(const Event* event){
            return nullptr;
        }
};

class AbortSignal: public EventTarget{
    public:
        bool aborted;
        bool dependent = false;
        std::any reason = nullptr;
        EventHandler onabort; //TODO: event handler IDL attribute whose event handler event type is abort.

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
            return this->isaborted();
        }
        bool isaborted(){
            if (this->reason.has_value()){
                try{
                    auto k = std::any_cast<std::nullptr_t>(this->reason);
                    return false;
                }
                catch(std::bad_any_cast){
                    return true;
                }
            }
            return false;
        }
        bool getdependent(){
            return this->dependent;
        }
        void setdependent(bool dependent){
            this->dependent = dependent;
        }
        std::any getreason(){
            return this->reason;
        }
};

class AbortController{
    public:
        AbortSignal* signal;
        AbortController();
        void abort(std::any reason = nullptr) const;
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

    path_structs(EventTarget *it = nullptr, bool itst = false, EventTarget *sat = nullptr, EventTarget *rt = nullptr, std::vector<EventTarget*> ttl = {}, bool rct = false, bool sct = false){
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
    public:
        DOMString type = "";
        EventTarget *target = nullptr;
        EventTarget *relatedTarget = nullptr;
        EventTarget *currentTarget = nullptr;
        enum event_phase eventPhase = NONE;
        bool bubbles;
        bool cancelable;
        bool composed;
        DOMHighResTimeStamp timeStamp;
    
        bool isTrusted = false;

        // Constructor
        Event(const DOMString &type, bool bubbles = false, bool cancelable = false, bool composed = false);
        Event(const Event* temp);

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
        std::vector<path_structs> path = {};
        std::vector<EventTarget*> touch_target_list = {}; //mostly no use until TouchEvent Interface

        void initEvent(DOMString type, bool bubbles = false, bool cancelable = false); // legacy
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
        void seteventPhase(enum event_phase temp){
            this->eventPhase = temp;
        }
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


        virtual bool operator==(Event* ev){
            if (this->type == ev->gettype() && this->target == ev->gettarget() && this->timeStamp == ev->gettimeStamp()){
                return true;
            }
            return false;
        }

        virtual Event* newObject(){
            return new Event(this->type);
        }
};


class CustomEvent: public Event{
    public:
        std::any detail = nullptr;
        CustomEvent(DOMString const type, std::any &detail, bool bubbles = false, bool cancelable = false, bool composed = false);
        void initCustomEvent(DOMString const type, bool bubbles = false, bool cancelable = false, std::any detail = nullptr);

        std::any getdetail() const{
            return this->detail;
        }

        CustomEvent(const CustomEvent* temp): Event(temp->type, temp->bubbles, temp->cancelable, temp->composed){
            this->detail = temp->detail;
        };
};


//Remember to remove when rewriting it
class MouseEvent: public Event{};


/*
Collection of Node objects

Attributes:
    None

Methods:
    item(unsigned long index) - Returns ptr to node object at index if present else nullptr
    length() - Number of elements in the nodelist

Operators:
    [unsigned long index] - Operator using item() method internally

 */
class NodeList{
    public:
        std::vector<Node*> node_list = {};

        // Returns the Node ptr on the index provided !
        Node* item(const unsigned long index) const;

        // Returns the Node ptr on the index provided !
        Node* operator[](unsigned long index) const {
            return this->item(index);
        }

        bool operator==(const NodeList* otherNodeList) const;

        // Returns the length of the list stored ! Must be stored in a variable.
        [[nodiscard]] unsigned long length() const;

        void append(Node* node){
            this->node_list.push_back(node);
        }

        void insert(Node* node, const unsigned long &index){
            if (index<0){return;}
            this->node_list.insert(this->node_list.begin()+index, node);
        }

        void remove(Node* node);

        ~NodeList();
};



// The Mega Boss & almost everything in a DOM tree - Node object !! Abstract class
class Node: public EventTarget{
    //Basic INFO.
    public:
        node_type nodeType;
        DOMString nodeName;
        USVString baseURI;
        Document* ownerDocument; // it is referenced as nodeDocument in the DOM at lots of places
        // Not necessary that parent is element ! could be some other type of node baby !
        Node* parentNode;
        Element* parentElement = nullptr;
        bool isConnected();

        //Babies !!! ( Children )
        NodeList childNodes;
        virtual Node* firstChild();
        virtual Node* lastChild();
        virtual Node* previousSibling();
        virtual Node* nextSibling();

        bool hasChildNodes() const;

        Node* getRootNode(bool composed = false);

        DOMString nodeValue;
        DOMString textContent;      
        void normalize();
        Node* cloneNode(bool subtree);


        Node(node_type nodeType, DOMString nodeName, Document* ownerDocument = nullptr, Node* parentNode = nullptr);

        unsigned long length(){
            //if (dynamic_cast<DocumentType*>(this) || dynamic_cast<Attr*>(this)){
            //    return 0;
            //}
            //CharacterData* temp = dynamic_cast<CharacterData*>(this);
            //if (temp){
            //    return temp->getdata().length();
            //}
            //return this->childNodes.length();
            return 0;
        }

        bool isEqualNode(Node* otherNode);
        bool isSameNode(Node* otherNode);

        unsigned short compareDocumentPosition(Node* other);
        bool contains(Node* other);

        virtual std::optional<DOMString> lookupPrefix(std::optional<DOMString> &namesp);
        std::optional<DOMString> lookupNamespaceURI(std::optional<DOMString> &prefix);

        bool isDefaultNamespace(std::optional<DOMString> &namesp);

        Node* insertBefore(Node* node, Node* child);
        Node* appendChild(Node* node);
        Node* replaceChild(Node* node, Node* child);
        Node* removeChild(Node* child);

        virtual Node* get_the_parent(Event* event);

        virtual std::optional<DOMString> getnodeValue(){
            return std::nullopt;
        }
        virtual void setnodeValue(DOMString &val){};
        virtual std::optional<DOMString> gettextContent(){
            return std::nullopt;
        }
        virtual void settextContent(DOMString  &val){};


        bool operator==(Node& other){ return this->isEqualNode(&other); }

        // Based on the follows algorithm !!
        bool operator^(Node* other){
            Node* currentNode = other->childNodes[0];
            std::vector<Node*> temp = {currentNode};
            while (currentNode!=nullptr){
                if (currentNode == this){
                    return true;
                }
                if (currentNode->childNodes.length()!=0){
                    temp.push_back(currentNode);
                    currentNode = currentNode->firstChild();
                    continue;
                }
                currentNode = currentNode->nextSibling();
                while (currentNode==nullptr && !temp.empty()){
                    currentNode = (*(temp.end() -1))->nextSibling();
                    temp.erase(temp.end()-1);
                }
            }
            return false;
        }

        unsigned long index(){
            auto a = std::find(this->childNodes.node_list.begin(), this->childNodes.node_list.end(), this);
            return a - this->childNodes.node_list.begin();
        }
};












// Algos

event_listener* flatten(DOMString &type, EventListener *callback, std::variant<AddEventListenerOptions,bool> options){
    event_listener* temp = new event_listener(type);
    temp->type = type;
    temp->callback = callback;
    temp->once = false;
    temp->passive = std::nullopt;
    temp->signal = nullptr;
    if (std::holds_alternative<bool>(options)){
        temp->capture = std::get<bool>(options);
    }
    else if (std::holds_alternative<AddEventListenerOptions>(options)){
        auto opts = std::get<AddEventListenerOptions>(options);
        temp->capture = opts.capture;
        temp->once = opts.once;
        if (opts.passive.has_value()){
            temp->passive = opts.passive;
        }
        if (opts.signal){
            temp->signal = opts.signal;
        }
    }
    return temp;
}

void remove_event_listener(EventTarget* eventTarget, event_listener *listener){
    listener->removed = true;
    auto it = std::find(eventTarget->event_listener_list.begin(),eventTarget->event_listener_list.end(), listener);
    if (it!=eventTarget->event_listener_list.end()){
        eventTarget->event_listener_list.erase(it);
    }
}

void add_abort_algo(const std::function<void()> &algo, AbortSignal* signal){
    if (signal->isaborted()){
        return;
    }
    signal->abort_algos.push_back(algo);
}

void run_abort_steps(AbortSignal* signal){
    for (auto algo: signal->abort_algos){
        algo();
    }
    signal->abort_algos.clear();
    fire_event("abort", signal);
}

void signal_abort(AbortSignal* signal, std::any reason) {
    if (signal->isaborted()) {
        return;
    }
    if (reason.has_value()){
        signal->reason = reason;
    }
    else{
        signal->reason = new AbortError("Abort errors !!");
    }

    std::vector<AbortSignal*> dependentSignalsToAbort = {};
    for (auto &dependentSignal: signal->dependent_signals) {
        if (!(dependentSignal->isaborted())) {
            dependentSignal->reason = signal->reason;
            dependentSignalsToAbort.push_back(dependentSignal);
        }
    }
    run_abort_steps(signal);
    for (const auto &dependentSignal: dependentSignalsToAbort) {
        run_abort_steps(dependentSignal);
    }
}

void add_event_listener(EventTarget* eventTarget, event_listener *listener){
    if (listener->signal != nullptr && listener->signal->isaborted()){ return; }
    if (listener->callback == nullptr){ return; }
    if (listener->passive == std::nullopt){
        listener->passive = default_passive_value(listener->type, eventTarget);
    }
    bool found = false;
    for (event_listener* ev: eventTarget->event_listener_list){
        if (ev->type == listener->type && ev->callback == listener->callback && ev->capture == listener->capture){
            found = true;
            break;
        }
    }
    if (!found){
        eventTarget->event_listener_list.push_back(listener);
    }
    if (listener->signal != nullptr ){
        add_abort_algo(std::bind(remove_event_listener, eventTarget, listener), listener->signal);
    }
}

AbortSignal* create_dependent_abort_signal(std::vector<AbortSignal*> signals, AbortSignal* signalInterface, Realm* realm) {
    AbortSignal* resultSignal = signalInterface->create_object();
    for (AbortSignal* signal: signals) {
        if (signal->isaborted()) {
            resultSignal->reason = signal->reason;
            return resultSignal;
        }
    }
    resultSignal->dependent = true;
    for (AbortSignal* signal: signals) {
        if (!(signal-> dependent)) {
            resultSignal->source_signals.push_back(signal);
            signal->dependent_signals.push_back(resultSignal);
        }
        else {
            for (AbortSignal* sourceSignal: signal->source_signals) {
                assert(!(sourceSignal->isaborted()) && !(sourceSignal->dependent));
                resultSignal->source_signals.push_back(sourceSignal);
                sourceSignal->dependent_signals.push_back(resultSignal);
            }
        }
    }
    return resultSignal;
}


bool fire_event(DOMString e,EventTarget* target,Event* temporary_class,bool legacy_target_override_flag) {
    Event* event;
    if (!temporary_class){
        event = new Event(e);
    }
    else{
        event = temporary_class->newObject();
    }
    event->type = e;
    bool returning_val = dispatch_event(event, target, legacy_target_override_flag);
    delete event;
    return returning_val;
};















void Event::inner_event_creation_steps(Event* event, Realm* realm, DOMHighResTimeStamp &time, bool bubbles, bool cancelable, bool composed){
    event->initialized_flag = true;
    event->timeStamp = time;
    event->bubbles = bubbles;
    event->cancelable = cancelable;
    event->composed = composed;
}

Event::Event(const DOMString &type, bool bubbles, bool cancelable, bool composed){
    DOMHighResTimeStamp now = time(NULL);
    inner_event_creation_steps(this, nullptr, now, bubbles, cancelable, composed);
    this->type = type;
};

Event::Event(const Event* temp){
    DOMHighResTimeStamp now = time(NULL);
    inner_event_creation_steps(this, nullptr, now, temp->bubbles, temp->cancelable, temp->composed);
    this->type = temp->type;
}

inline void Event::stopPropagation(){
    this->stop_propagation_flag = true;
};

inline void Event::stopImmediatePropagation(){
    this->stop_propagation_flag = true;
    this->stop_immediate_propagation_flag = true;
};

inline void Event::set_canceled_flag(){
    if (this->cancelable && !this->in_passive_listener_flag){
        this->canceled_flag = true;
    }
};

void Event::preventDefault(){
    // *Cancels the event (if it is cancelable).
    this->set_canceled_flag();
};

void Event::initEvent(DOMString type, bool bubbles, bool cancelable){
    if (this->dispatch_flag){
        return;
    }
    this->isTrusted = false;
    this->initialized_flag = true;
    this->stop_propagation_flag = false;
    this->stop_immediate_propagation_flag = false;
    this->canceled_flag = false;
    this->target = nullptr;
    this->type = type;
    this->bubbles = bubbles;
    this->cancelable = cancelable;
}

std::vector<EventTarget*> Event::composedPath(){
    std::vector<EventTarget*> composed_path = {};
    if (this->path.empty()){
        return composed_path;
    }
    assert(dynamic_cast<EventTarget*>(this->currentTarget));
    composed_path.push_back(this->currentTarget);
    int currentTargetIndex = 0;
    int currentTargetHiddenSubtreeLevel = 0;
    for (int index = this->path.size() - 1; index>=0; index--){
        if (this->path[index].root_of_closed_tree){
            currentTargetHiddenSubtreeLevel++;
        }
        if (this->path[index].invocation_target==this->currentTarget){
            currentTargetIndex = index;
            break;
        }
        if (this->path[index].slot_in_closed_tree){
            currentTargetHiddenSubtreeLevel--;
        }
    }
    int currentHiddenLevel = currentTargetHiddenSubtreeLevel;
    int maxHiddenLevel = currentTargetHiddenSubtreeLevel;
    for (int index = currentTargetIndex - 1; index>=0; index--){
        if (this->path[index].root_of_closed_tree){
            currentHiddenLevel++;
        }
        if (currentHiddenLevel<=maxHiddenLevel){
            composed_path.insert(composed_path.begin(),this->path[index].invocation_target);
        }
        if (this->path[index].slot_in_closed_tree){
            currentHiddenLevel--;
            if (currentHiddenLevel<maxHiddenLevel){
                maxHiddenLevel = currentHiddenLevel;
            }
        }
    }
    currentHiddenLevel = currentTargetHiddenSubtreeLevel;
    maxHiddenLevel = currentTargetHiddenSubtreeLevel;
    for (int index = currentTargetIndex + 1; index<this->path.size(); index++){
        if (this->path[index].slot_in_closed_tree){
            currentHiddenLevel++;
        }
        if (currentHiddenLevel<=maxHiddenLevel){
            composed_path.push_back(this->path[index].invocation_target);
        }
        if (this->path[index].root_of_closed_tree){
            currentHiddenLevel--;
            if (currentHiddenLevel<maxHiddenLevel){
                maxHiddenLevel = currentHiddenLevel;
            };
        }
    }
    return composed_path;
};








CustomEvent::CustomEvent(DOMString const type, std::any &detail, bool bubbles, bool cancelable, bool composed): Event(type, bubbles, cancelable, composed){
    this->detail = detail;
}

void CustomEvent::initCustomEvent(DOMString const type, bool bubbles, bool cancelable, std::any detail){
    if (this->dispatch_flag){
        return;
    }
    this->initEvent(type, bubbles, cancelable);
    this->detail = detail;
}


Event* create_event(Event* eventInterface, Realm* realm){
    DOMHighResTimeStamp now = time(NULL);
    eventInterface->inner_event_creation_steps(eventInterface, realm, now);
    eventInterface->isTrusted = true;
    return eventInterface;
};


void EventTarget::addEventListener(DOMString &type, EventListener* callback, std::variant<AddEventListenerOptions,bool> &options){
    event_listener* temp = flatten(type, callback, options);
    add_event_listener(this, temp);
}

void EventTarget::removeEventListener(DOMString &type, EventListener* callback, bool capture){
    int i = 0;
    event_listener* el = new event_listener(type, callback, capture);
    for (event_listener* ev: this->event_listener_list){
        if (*ev == *el){
            remove_event_listener(this, el);
        }
        i++;
    }
}

void EventTarget::removeAllEventListeners(){
    for (event_listener* a: event_listener_list){
        a->removed = true;
        delete a;
    }
    event_listener_list.clear();
}

bool EventTarget::dispatchEvent(Event* event) {
    if (event->dispatch_flag || !event->initialized_flag){
        throw InvalidStateError("Invalid State");
    }
    event->isTrusted = false;
    return dispatch_event(event, this, false);
}










AbortController::AbortController(){
    this->signal = new AbortSignal();
}

void AbortController::abort(std::any reason) const{
    signal_abort(this->signal, reason);
}

AbortSignal* AbortSignal::abort(std::any reason) {
    AbortSignal* signal = new AbortSignal();
    if (reason.has_value()) {
        signal->reason = reason;
    }
    else {
        signal->reason = AbortError("Damn ! Abort error paji! ");
    }
    return signal;
}

AbortSignal* AbortSignal::timeout(unsigned long long milliseconds) {
    AbortSignal* signal = new AbortSignal();
    //! MF GLOBAL OBJECT AGAIN HERE
    // HTML stuff here againnnnnnnnnnnnnnn
    return signal;
}

AbortSignal *AbortSignal::_any(std::vector<AbortSignal *> signals) {
    return create_dependent_abort_signal(signals);
}

void AbortSignal::throwIfAborted() {
    if (this->isaborted()) {
        reason = nullptr;
    }
}



Node* NodeList::item(const unsigned long index) const{
    try {
        return node_list.at(index);
    }
    catch (const std::out_of_range&) {
        return nullptr;
    }
}

unsigned long NodeList::length() const{
    return node_list.size();
}

bool NodeList::operator==(const NodeList* otherNodeList) const{
    if (this->length() != otherNodeList->length()){
        return false;
    }
    for (size_t i=0; i<this->length(); i++){
        if (this->item(i)->isEqualNode(otherNodeList->item(i))){
            continue;
        }
        return false;
    }
    return true;
}

void NodeList::remove(Node* node){
    unsigned int i = 0;
    for (auto a: this->node_list){
        if (a->isEqualNode(node)){
            this->node_list.erase(this->node_list.begin()+i);
            return;
        }
        i++;
    }
}


NodeList::~NodeList(){
    for (auto a: node_list) {
        delete a;
    }
    node_list = {};
}








int main(){
    std::cout<<"La lala lalalalalalala";
}