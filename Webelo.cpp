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
#include <map>
#include <set>
#include <initializer_list>


// Macros

#define DOCUMENT_POSITION_DISCONNECTED 0x01
#define DOCUMENT_POSITION_PRECEDING 0x02
#define DOCUMENT_POSITION_FOLLOWING 0x04
#define DOCUMENT_POSITION_CONTAINS 0x08
#define DOCUMENT_POSITION_CONTAINED_BY 0x10
#define DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC 0x20

#define START_TO_START 0
#define START_TO_END 1
#define END_TO_END 2
#define END_TO_START 3

#define FILTER_ACCEPT 1
#define FILTER_REJECT 2
#define FILTER_SKIP 3

#define SHOW_ALL 0xFFFFFFFF
#define SHOW_ELEMENT 0x1
#define SHOW_ATTRIBUTE 0x2
#define SHOW_TEXT 0x4
#define SHOW_CDATA_SECTION 0x8
#define SHOW_ENTITY_REFERENCE 0x10
#define SHOW_ENTITY 0x20
#define SHOW_PROCESSING_INSTRUCTION 0x40
#define SHOW_COMMENT 0x80
#define SHOW_DOCUMENT 0x100
#define SHOW_DOCUMENT_TYPE 0x200
#define SHOW_DOCUMENT_FRAGMENT 0x400
#define SHOW_NOTATION 0x800


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
class CustomElementRegistry;
struct ImportNodeOptions;
class NodeFilter;
class NodeIterator;
class TreeWalker;
class AbstractRange;
struct StaticRangeInit;
class StaticRange;
class Range;
class DocumentFragment;
class HTMLCollection;
class ParentNode;
class Attr;
class Text;
class CharacterData;
class CDATASection;
class Comment;
class ProcessingInstruction;
class DocumentType;
class DocumentFragment;
class ShadowRoot;
struct ElementCreationOptions;
struct ShadowRootInit;
class NamedNodeMap;
class XMLDocument;
class DOMImplementation;
class DOMTokenList;
class Window;
class HTMLSlotElement;



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

// *Phase/State of the Event
enum event_phase: unsigned int{
    NONE,
    CAPTURING_PHASE, //top to bottom
    AT_TARGET, //reached
    BUBBLING_PHASE //bottom to top again !
};

enum ShadowRootMode{ open, closed};
enum SlotAssignmentMode{ manual, named};

enum DocType{
    XML,
    HTML,
    XML_XHTML
};

enum DocMode{
    NO_QUIRKS,
    QUIRKS,
    LIMITED_QUIRKS
};

enum ElementState{
    UNDEFINED, FAILED, UNCUSTOMIZED, PRECUSTOMIZED, CUSTOM
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
DOMString replace_data(Node* node, unsigned long offset, unsigned long count, DOMString data);
Element* create_element(Document* document, DOMString localName, std::optional<DOMString> namesp, std::optional<DOMString> prefix = std::nullopt, std::optional<DOMString> is = std::nullopt, bool synchronousCustomElements = false, std::variant<DOMString,std::nullptr_t,CustomElementRegistry> registry = std::string("default"));
void flatten_element_creation_options(std::variant<DOMString,ElementCreationOptions> options, Document* document, CustomElementRegistry* registry, std::optional<DOMString> &is);
void adopt(Node* node, Document* document);
Element* internal_create_element_ns(Document* document, std::optional<DOMString> namesp, DOMString qualifiedName, std::variant<DOMString,ElementCreationOptions> options);
void change_attribute_value(Attr* attribute, DOMString value);
void append_attribute(Attr* attribute, Element* element);
void remove_attribute(Attr* attribute);
void replace_attribute(Attr* oldAttribute, Attr* newAttribute);
Attr* fetch_attribute(DOMString qualifiedName, Element* element);
Attr* fetch_attribute(std::optional<DOMString> namesp, DOMString localName, Element* element);
DOMString fetch_attribute(Element* element, DOMString localName, std::optional<DOMString> namesp = std::nullopt);
Attr* set_attribute(Attr* attr, Element* element);
void set_attribute_value(Element* element, DOMString localName, DOMString value, std::optional<DOMString> prefix = std::nullopt, std::optional<DOMString> namesp = std::nullopt);
Attr* remove_attribute_by_name(DOMString qualifiedName, Element* element);
Attr* remove_attribute_by_namespace(std::optional<DOMString> namesp, DOMString localName, Element* element);
void attach_shadow_root(Element* element, ShadowRootMode mode, bool clonable, bool serializable, bool delegatesFocus, SlotAssignmentMode slotAssignment, std::optional<CustomElementRegistry> registry);
Node* insert_adjacent(Element* element, DOMString where, Node* node);
DOMString replace_all(Node* node, Node* newParent);
DOMString substring_data(Node* node, unsigned long offset, unsigned long count);
bool check_exclusive_text_node(Text* node);
std::vector<Text*> contiguous_text_nodes(Text* node);
std::vector<Text*> contiguous_exclusive_text_nodes(Text* node);
DOMString child_text_content(Node* node);
DOMString descendant_text_content(Node* node);
Text* split_text_node(Text* node, unsigned long offset);
int position(Node* nodeA, unsigned long offsetA, Node* nodeB, unsigned long offsetB);
bool static_range_valid(StaticRange* range);
bool contained_in_range(Node* node, Range* range);
bool partially_contained_in_range(Node* node, Range* range);
void pre_remove_range(Node* node);
void set_start_end(Range* range, Node* node, int offset, bool start = true);
void select_node_within_rangee(Node* node, Range* range);
DocumentFragment* extract_range(Range* range);
DocumentFragment* clone_contents(Range* range);
void insert_node_in_range(Node* node, Range* range);
void pre_remove_steps(NodeIterator* node_iterator, Node* toBeRemovedNode);
Node* traverse(NodeIterator* iterator, unsigned long direction);
Node* traverse_children(TreeWalker* walker, unsigned long type);
Node* traverse_sibling(TreeWalker* walker, unsigned long type);
bool inner_invoke(Event* event, std::vector<event_listener*> &listeners,enum event_phase phase, bool invocationTargetInShadowTree, std::optional<bool> legacyOutputDidListenersThrowFlag = std::nullopt);
void append_to_event_path(Event* event, EventTarget* invocationTarget, EventTarget*  shadowAdjustedTarget, EventTarget* relatedTarget, std::vector<EventTarget*> &touchTargets, bool slot_in_closed_tree);
void invoke_event(path_structs &struc, Event* event, enum event_phase phase, std::optional<bool> legacyOutputDidListenersThrowFlag = std::nullopt);
Node* clone_node(Node* node, Document* document = nullptr, bool subtree = false, Node* parent = nullptr, CustomElementRegistry* fallbackRegistry = nullptr);
Node* clone_a_single_node(Node* node, Document* document, CustomElementRegistry* fallbackRegistry);
bool nodequals(Node* first, Node* second);
void string_replace_all(std::string &str, Node* parent);
std::optional<DOMString> locate_a_namespace(Node* node, std::optional<DOMString> prefix);
std::optional<DOMString> locate_a_namespace_prefix(Element* element, std::optional<DOMString> namesp);
EventTarget* retard(EventTarget* a, EventTarget* b);
int determine_node_length(Node* node);
Node* convert_nodes_to_node(std::vector<std::variant<Node*, DOMString>> nodes, Document* document);
bool check_ancestor(Node* node, Node* target, bool inclusive = false);
bool check_descendant(Node* node, Node* target, bool inclusive = false);
bool check_node_precedes(Document* doc, Node* node, Node* target);
bool check_shadow_including_descendant(Node* node, Node* target, bool inclusive = false);
bool is_closed_shadow_hidden(Node* A, Node* B);
Node* retarget(Node* A, Node* B);
bool host_including_inclusive_ancestor(Node* A, Node* B);
void ensure_pre_insert_validity(Node* node, Node* parent, Node* child);
void move_node(Node* node,Node* node2,Node* Child){};
void replace(Node* obj, Node* node, Node* parent){};
// void replace_data(Node* node, unsigned long offset, unsigned long count, DOMString data){}
void insert_node(Node* node, Node* parent, Node* child, bool suppress_observers = false);
void queue_tree_mutation_record(Node* node, NodeList* gg,NodeList* nodes,Node* boi,Node* girl){};
Node* pre_insert_node(Node* node, Node* parent, Node* child);
void remove_node(Node* node);
void before(std::vector<std::variant<Node*, DOMString>> &nodes, Node* obj);
void after(std::vector<std::variant<Node*, DOMString>>& nodes, Node* obj);
void replaceWith(std::vector<std::variant<Node*, DOMString>> &nodes, Node* obj);
void remove(Node* obj);
Node* pre_remove_node(Node* child, Node* parent);
Node* replace_node(Node* node, Node* child, Node* parent);


//hehe
bool default_passive_value(const DOMString &type, EventTarget* eventTarget);
bool dispatch_event(Event* event, EventTarget* target, std::optional<bool> legacy_target_override_flag = std::nullopt, std::optional<bool> legacy_output_did_listeners_throw_flag = std::nullopt);




// Classes & Structs

class Window{
    //TODO: LATER DO IT FULL !
    protected:
        Event* event = nullptr; //Replaceable
    public:
        Event* getEvent(){
            return this->event;
        }
};

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

struct ImportNodeOptions{
    CustomElementRegistry* customElementRegistry;
    bool selfOnly = false;
};

class NodeFilter{
    public:
        void acceptNode(Node* node){};
};

class NodeIterator{
    public:
        Node* root;
        Node* referenceNode;
        bool pointerBeforeReferenceNode;
        unsigned long whatToShow;
        NodeFilter* filter;

        bool active = false;

        Node* nextNode();
        Node* previousNode();

        void detach(){};

        unsigned short filter_node(Node* node);

        NodeIterator(){};
};

class TreeWalker{
    public:
        Node* root;
        unsigned long whatToShow;
        NodeFilter* filter;
        Node* currentNode;

        bool active = false;

        TreeWalker(){};

        unsigned short filter_node(Node* node);

        Node* parentNode();
        Node* firstChild();
        Node* lastChild();
        Node* previousSibling();
        Node* nextSibling();
        Node* previousNode();
        Node* nextNode();
};



class AbstractRange{
    public:
        Node* startContainer;
        unsigned long startOffset;
        Node* endContainer;
        unsigned long endOffset;
        bool collapsed();
};

struct StaticRangeInit{
    Node* startContainer;
    unsigned long startOffset;
    Node* endContainer;
    unsigned long endOffset;
    StaticRangeInit(Node* sc, unsigned long sos, Node* ec, unsigned long eos){
        startContainer = sc;
        startOffset = sos;
        endContainer = ec;
        endOffset = eos;
    }
};

//Exposed to window only
class StaticRange: public AbstractRange{
    public:
        StaticRange(StaticRangeInit init);
};


class Range: public AbstractRange{
    public:
        Node* commonAncestorContainer();
        Range();

        void setStart(Node* node, unsigned long offset);
        void setEnd(Node* node, unsigned long offset);
        void setStartBefore(Node* node);
        void setStartAfter(Node* node);
        void setEndBefore(Node* node);
        void setEndAfter(Node* node);
        void collapse(bool toStart = false);
        void selectNode(Node* node);
        void selectNodeContents(Node* node);

        short compareBoundaryPoints(unsigned short how, Range* sourceRange);

        //CEReactions
        void deleteContents();
        DocumentFragment* extraContents(); //NewObject
        DocumentFragment* cloneContents(); //NewObject
        void insertNode(Node* node);
        void surroundContents(Node* newParent);

        Range* cloneRange(); //NewObject
        void detach(){};
        bool isPointInRange(Node* node, unsigned long offset);
        short comparePoint(Node* node, unsigned long offset);
        bool intersectsNode(Node* node);

        //TODO: stringifier;
        DOMString stringification_behavior();
};


/*
Collection of Element objects

Attributes:
    None

Methods:
    item(unsigned long index) - Returns ptr to node object at index if present else nullptr
    namedItem(DOMString name)
    length() - Number of elements in the nodelist

Operators:
    [unsigned long index] - Operator using item() method internally
    [DOMString name] - Operator using namedItem() method internally
 */
class HTMLCollection{
    public:
        std::vector<Element*> element_list = {};

        // Returns the Node ptr on the index provided !
        Element* item(const unsigned long &index) const;

        // Returns the Node ptr on the index provided !
        Element* operator[](const unsigned long &index) const {
            return this->item(index);
        }

        Element* namedItem(const DOMString &name) const;

        Element* operator[](const DOMString &name) const{
            return this->namedItem(name);
        }

        // Returns the length of the list stored ! Must be stored in a variable.
        [[nodiscard]] unsigned long length() const;

        void append(Element* node){
            this->element_list.push_back(node);
        }

        void insert(Element* node, const unsigned long &index){
            if (index<0){return;}
            this->element_list.insert(this->element_list.begin()+index, node);
        }

        void remove(Element* node){
            unsigned int i = 0;
            for (auto a: this->element_list){
                // if (dynamic_cast<Node*>(a)->isEqualNode(dynamic_cast<Node*>(node))){
                //     this->element_list.erase(this->element_list.begin()+i);
                //     return;
                // }
                i++;
            }
        }

        ~HTMLCollection();
};


class ParentNode: public Node {
    public:
        HTMLCollection children;
        Element* firstElementChild() const{
            return children.item(0);
        };
        Element* lastElementChild() const{
            return children.element_list.back();
        };

        unsigned long childElementCount() const{
            return children.length();
        };

        void evaluate_children(){
            for (auto a: this->childNodes.node_list){
                // if (dynamic_cast<Element*>(a)){
                     // this->children.append(dynamic_cast<Element*>(a));
                // }
            }
        }

        void prepend(std::vector<std::variant<Node*, DOMString>> &nodes);
        void append(std::vector<std::variant<Node*, DOMString>> &nodes);
        void replaceChildren(std::vector<std::variant<Node*, DOMString>> &nodes);
        void moveBefore(Node* node,Node* child);

        Element* querySelector(DOMString selectors);
        NodeList querySelectorAll(DOMString selectors);

        virtual void making_it_abstract(){};

        ParentNode(node_type nodeType, DOMString nodeName, Document* ownerDocument, Node* parentNode): Node(nodeType, nodeName, ownerDocument, parentNode){};
};

//Exposed to window only
class Attr: public Node{
    public:
        std::optional<DOMString> namespaceURI = std::nullopt;
        std::optional<DOMString> prefix = std::nullopt;
        DOMString localName;
        DOMString name;
        Element* ownerElement = nullptr;
        bool specified = true;
        //CEReactions
        DOMString value = "";
        DOMString qualifiedName();

        Attr(DOMString localName);


        void setvalue(DOMString value){
            if (this->ownerElement==nullptr){ this->value = value; }
            // else{ change_attribute_value(this, value); }
        }
};


class CharacterData: public Node{
    protected:
        DOMString data;
    public:
        unsigned long length();
        DOMString substringData(unsigned long offset, unsigned long count);
        void appendData(DOMString data);
        void insertData(unsigned long offset, DOMString data);
        void deleteData(unsigned long offset, unsigned long count);
        void replaceData(unsigned long offset, unsigned long count, DOMString data);
        Element* previousElementSibling();
        Element* nextElementSibling();

        // friend void before(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj);
        // friend void after(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj);
        // friend void replaceWith(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj);
        // friend void remove(Node* obj);

        CharacterData(Document* ownerdoc = nullptr, Node* parentnode = nullptr): Node(CDATA_SECTION_NODE, "#cdata-section", ownerdoc, parentnode){};

        DOMString getdata(){ return this->data; }
        virtual void setdata(DOMString data){
            replace_data(this, 0, this->length(),data);
        }
};

class Text: public CharacterData{
    public:
        DOMString wholeText();
        DOMString slot=""; //! IMPORTANT SOMEWHERE in dispatch_event (slottable check)
        HTMLSlotElement* assignedSlot;

        virtual void setdata(DOMString data) override{
            replace_data(this, 0, this->length(),data);
        }
        
        Text(DOMString data = ""):CharacterData(){
            this->setdata(data);
        };
        Text* splitText(unsigned long offset); //NewObject

};

//Exposed to window only
class ProcessingInstruction: public CharacterData{
    public:
        DOMString target;

        virtual void setdata(DOMString data) override{
            replace_data(this, 0, this->length(),data);
        }

        ProcessingInstruction(Document* ownerdoc = nullptr, Node* parentnode = nullptr): CharacterData(ownerdoc, parentnode){};

};

//Exposed to window only
class Comment: public CharacterData{
    public:

        virtual void setdata(DOMString data) override{
            replace_data(this, 0, this->length(),data);
        }

        Comment(DOMString data = ""){
            this->setdata(data);
        };

};

//Exposed to window only
class CDATASection: public Text{
    public:

        virtual void setdata(DOMString data) override{
            replace_data(dynamic_cast<Node*>(this),0, this->length(),data);
        }

};


class Document: public ParentNode{
    public:
        CustomElementRegistry* custom_element_registry = nullptr;
        DOMImplementation* implementation;
        USVString URL = "about:blank"; //!serialize
        USVString documentURI = URL; //!serialize
        DOMString characterSet = "utf-8";
        DOMString contentType = "application/xml";

        DocumentType* doctype();
        Element* documentElement();

        DOMString encoding = "utf-8";
        DocType type = XML;
        DOMString* origin = nullptr; //lateeeeeer
        DocMode mode = NO_QUIRKS;
        bool allow_declarative_shodow_roots = false;

        Document(Document* ownerdoc = nullptr, Node* parentnode = nullptr): ParentNode(DOCUMENT_NODE, "#document", ownerdoc, parentnode){
            // this->implementation->associated_doc = this;
        };

        DOMString compatMode();

        DOMString* lookupPrefix(std::optional<DOMString> namesp); //Redefining for Node class

        HTMLCollection* getElementsByTagName(DOMString qualifiedName);
        HTMLCollection* getElementsByTagNameNS(std::optional<DOMString> namesp, DOMString localname);
        HTMLCollection* getElementsByClassName(std::vector<DOMString> &classNames);
        // friend Element* getElementById(Node* node, const DOMString &elementId);


        Element* createElement(DOMString localName, std::variant<DOMString,ElementCreationOptions> options); //NOTE: Keep last argument as optional
        Element* createElementNS(std::optional<DOMString> namesp, DOMString qualifiedName, std::variant<DOMString,ElementCreationOptions> options); //NOTE: Keep last argument as optional
        Node* importNode(Node* node, std::variant<bool,ImportNodeOptions> options = false);
        Node* adoptNode(Node* node); //no NewObject

        //NewObject
        DocumentFragment* createDocumentFragment();
        Text* createTextNode(DOMString data);
        CDATASection* createCDATASection(DOMString data);
        Comment* createComment(DOMString data);
        ProcessingInstruction* createProcessingInstruction(DOMString target, DOMString data);
        Attr* createAttribute(DOMString localName);
        Attr* createAttributeNS(std::optional<DOMString> namesp, DOMString qualifiedName);
        Event* createEvent(DOMString interface); //LEGACY
        Range* createRange();
        NodeIterator* createNodeIterator(Node* root, unsigned long whatToShow = 0xFFFFFFFF, NodeFilter* filter = nullptr);
        TreeWalker* createTreeWalker(Node* root, unsigned long whatToShow = 0xFFFFFFFF, NodeFilter* filter = nullptr);

        CustomElementRegistry* get_custom_element_registry() const{
            return this->custom_element_registry;
        }

        virtual Node* get_the_parent(Event* event){
            if (event->gettype()=="load"){
                return nullptr;
            }
            return nullptr;
        }

        virtual void making_it_abstract(){};
};

//Exposed to window only
class DocumentType: public Node{
    public:
        DOMString name;
        DOMString publicId;
        DOMString systemId;
    
        // friend void before(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj);
        // friend void after(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj);
        // friend void replaceWith(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj);
        // friend void remove(Node* obj);

        DocumentType(DOMString name,DOMString publicId="",DOMString systemId="",Document* ownerdoc = nullptr, Node* parentnode = nullptr): Node(DOCUMENT_TYPE_NODE, name, ownerdoc, parentnode){
            this->name = name;
            this->publicId = publicId;
            this->systemId = systemId;
        }
        DOMString getname(){
            return name;
        }
        DOMString getpublicId(){
            return publicId;
        }
        DOMString getsystemId(){
            return systemId;
        }

};

class DocumentFragment: public ParentNode{
    public:
        Element* associatedHost = nullptr;
        // friend Element* getElementById(Node* node ,const DOMString &elementId);
        DocumentFragment(Document* ownerdoc = nullptr, Node* parentnode = nullptr): ParentNode(DOCUMENT_FRAGMENT_NODE, "#document-fragment", ownerdoc, parentnode){};

};

//Exposed to window only
class ShadowRoot: public DocumentFragment{
    public:
        CustomElementRegistry* custom_element_registry = nullptr;
        ShadowRootMode mode;
        bool delegatesFocus = false;
        bool availableToElementInternals = false;
        bool declarative = false;
        SlotAssignmentMode slotAssignment;
        bool clonable = false;
        bool serializable = false;
        Element* host(){ return this->associatedHost; }
        EventHandler onslotchange;

        bool keepCustomElementRegistryNull = false;

        // virtual Element* get_the_parent(Event* event);
        // virtual Element* get_the_parent(Event* event) override{
        //     if (!event->composed_flag && !event->path.empty() && dynamic_cast<EventTarget*>(this) == event->path.at(0).invocation_target){
        //         return nullptr;
        //     }
        //     return this->associatedHost;
        // }

};


struct ElementCreationOptions{
    CustomElementRegistry* CustomElementRegistry = nullptr;
    std::optional<DOMString> is = std::nullopt;

    ElementCreationOptions(){};
};

struct ShadowRootInit{
    ShadowRootMode mode;
    bool delegatesFocus = false;
    SlotAssignmentMode slotAssignment = named;
    bool clonable = false;
    bool serializable = false;
    CustomElementRegistry* customElementRegistry = nullptr;

    ShadowRootInit(ShadowRootMode mod){
        mode = mod;
    }
};

//Exposed to window only + LegacyUnenumerableNamedProperties
class NamedNodeMap{
    public:
        std::vector<Attr*> attribute_list = {};
        Element* associatedElement;
        unsigned long length();
        Attr* item(unsigned long index);
        Attr* getNamedItem(DOMString qualifiedName);

        Attr* getNamedItemNS(std::optional<DOMString> namesp, DOMString localName);

        //CEReactions
        Attr* setNamedItem(Attr* attr);
        Attr* setNamedItemNS(Attr* attr);
        Attr* removeNamedItem(DOMString qualifiedName);
        Attr* removeNamedItemNS(std::optional<DOMString> namesp, DOMString localName);
};


class Element: public ParentNode{
    public:
        std::optional<DOMString> namespaceURI;
        std::optional<DOMString> prefix;
        DOMString localName;
        // DOMTokenList classList;
        NamedNodeMap attributes;
        ShadowRoot* shadow_root = nullptr;
        CustomElementRegistry* customElementRegistry;
        ElementState customElementState;
        //CEReactions
        DOMString id;
        DOMString className;
        DOMString slot="";
        HTMLSlotElement* assignedSlot;
        std::optional<DOMString> is;

        DOMString html_uppercased_qualified_name(){
            DOMString qualified_name;
            if (this->prefix==std::nullopt){ qualified_name = this->localName; }
            else{ qualified_name = this->prefix.value() + ":" + this->localName; }
            // if (this->ownerDocument->type != XML){
            //     std::transform(qualified_name.begin(), qualified_name.end(), qualified_name.begin(), [](unsigned char c){ return std::toupper(c); });
            // }
            return qualified_name;
        }

        Element(std::optional<DOMString> namesp, std::optional<DOMString> prefix, DOMString localName, CustomElementRegistry* customElementRegistry = nullptr, ElementState customElementState = UNDEFINED, Document* ownerdoc = nullptr, Node* parentnode = nullptr): ParentNode(ELEMENT_NODE, this->html_uppercased_qualified_name(), ownerdoc, parentnode){
            this->namespaceURI = namesp;
            this->prefix = prefix;
            this->localName = localName;
            this->customElementRegistry = customElementRegistry;
            this->customElementState = customElementState;
        }

        Element* previousElementSibling();
        Element* nextElementSibling();

        DOMString tagName(){
            return this->html_uppercased_qualified_name();
        };


        void setAttribute(DOMString qualifiedName, DOMString value);
        void setAttributeNS(std::optional<DOMString> namesp, DOMString qualifiedName, DOMString value);
        void removeAttribute(DOMString qualifiedName);
        void removeAttributeNS(std::optional<DOMString> namesp, DOMString localName);
        bool toggleAttribute(DOMString qualifiedName, std::optional<bool> force); //force is optional
        Attr* setAttributeNode(Attr* attr);
        Attr* setAttributeNodeNS(Attr* attr);
        Attr* removeAttributeNode(Attr* attr);
        
        bool hasAttributes();
        std::vector<DOMString> getAttributeNames();
        std::optional<DOMString> getAttribute(DOMString qualifiedName);
        std::optional<DOMString> getAttributeNS(std::optional<DOMString> namesp, DOMString localName);
        bool hasAttribute(DOMString qualifiedName);
        bool hasAttributeNS(std::optional<DOMString> namesp, DOMString localname);

        Attr* getAttributeNode(DOMString qualifiedName);
        Attr* getAttributeNodeNS(std::optional<DOMString> namesp, DOMString localName);

        ShadowRoot* attachShadow(ShadowRootInit init);
        std::optional<Element> closest(DOMString selectors);
        bool matches(DOMString selectors);

        HTMLCollection* getElementsByTagName(DOMString qualifiedName);
        HTMLCollection* getElementsByTagNameNS(std::optional<DOMString> namesp, DOMString localName);
        HTMLCollection* getElementsByClassName(DOMString classNames);

        Element* insertAdjacentElement(DOMString where, Element element); //legacy
        void insertAdjacentText(DOMString where, DOMString data); //legacy

        // friend void before(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj);
        // friend void after(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj);
        // friend void replaceWith(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj);
        // friend void remove(Node* obj);

        bool operator==(Element* other){ return dynamic_cast<Node*>(this)->isEqualNode(dynamic_cast<Node*>(other)); }

        virtual void making_it_abstract(){};



        //Getter Setters
        DOMString getid(){
            // return fetch_attribute(this, "id");
            return "";
        }
        void setid(DOMString value){
            // set_attribute_value(this, "id", value);
        }

        DOMString getclassName(){
            // return fetch_attribute(this, "class");
            return "";
        }
        void setclassName(DOMString value){
            // set_attribute_value(this, "class", value);
        }

        DOMString getslot(){
            // return fetch_attribute(this, "slot");
            return "";
        }
        void setslot(DOMString value){
            // set_attribute_value(this, "slot", value);
        }

        ShadowRoot* getshadow_root(){
            if (this->shadow_root==nullptr || this->shadow_root->mode==closed){ return nullptr; }
            return this->shadow_root;
        }

        void update_slot_name(DOMString name, std::optional<DOMString> oldvalue, std::optional<DOMString> value){
            if (value == oldvalue){ return; }
            if (!value.has_value() && oldvalue.has_value() && oldvalue.value()==""){ return; }
            if (value.has_value() && value.value()=="" && !oldvalue.has_value()){ return; }
            if (!value.has_value() || value.value()==""){
                this->localName = "";
            }
            else{
                this->localName = value.value();
            }
            // assign_slottables_for_tree(this->getRootNode())
        }

};

class HTMLSlotElement: public Element{};

class XMLDocument: public Document{};


class DOMImplementation{
    public:
        Document* associated_doc = nullptr;
        //NewObject
        DocumentType* createDocumentType(DOMString name, DOMString publicId, DOMString systemId);
        XMLDocument* createDocument(std::optional<DOMString> namesp, DOMString qualifiedName, std::optional<DocumentType> doctype = std::nullopt);
        //qualifiedName is LegacyNullToEmptyString
        Document* createHTMLDocument(std::optional<DOMString> title);
        bool hasFeature();
};


class DOMTokenList{
    public:
        std::optional<DOMString> item(unsigned long index){
            if (index>=this->length()){
                return std::nullopt;
            }
            return "";
        };
        bool contains(DOMString token){
            auto a = this->list.find(token);
            if (a == this->list.end()){
                return false;
            }
            return true;
        };

        //CEReactions
        void add(std::vector<DOMString> tokens);
        void remove(std::vector<DOMString> tokens);
        bool toggle(DOMString token, std::optional<bool> force);
        bool replace(DOMString token, DOMString newToken);
        DOMString getvalue(){
            return this->serialize();
        }
        void setvalue(DOMString value){
            // set_attribute_value(this->associatedElement, this->associatedAttribute->localName, value);
        }


        bool supports(DOMString token);
        std::set<DOMString> list = {};

        Element* associatedElement = nullptr;
        Attr* associatedAttribute = nullptr;

        unsigned long length(){
            return this->list.size();
        }

        bool validate(DOMString token){
            auto ltoken = std::copy(token.begin(),token.begin(), token.end());
            std::transform(token.begin(), token.end(), token.begin(), [](unsigned char c){ return std::tolower(c); });
            return false;
        }

        void update(){
            if (!this->associatedAttribute){
                return;
            }
            // set_attribute_value(associatedElement, associatedAttribute->localName, SerializeOrderedSet(this->list));
        }

        DOMString serialize(){
            // return fetch_attribute(this->associatedElement, this->associatedAttribute->localName);
            return "";
        }


        DOMTokenList(Element* element, Attr* attribute){
            this->associatedElement = element;
            this->associatedAttribute = attribute;
            // this->setvalue(fetch_attribute(element, attribute->localName));
            if (this->getvalue()==""){
                list.clear();
            }
            // else{
            //     this->list = ParseOrderedSet(this->getvalue());
            // }
        }
};






// Algos


// Returns a set of strings. It separates all the substrings based on ASCII whitespace in the input !!
std::set<DOMString> parse_ordered_set(DOMString input){
    std::vector<int> asciiWhitespace = {9,10,12,13,32};
    std::vector<DOMString> inputTokens = split_text_multiple(input, asciiWhitespace);
    std::set<DOMString> tokens;
    for (DOMString a: inputTokens){
        tokens.insert(a);
    }
    return tokens;
}

// Concatenates all the strings in the set provided with U+0020 (SPACE)
DOMString serialize_ordered_set(std::set<DOMString> input){
    DOMString str = "";
    int i=0;
    for (auto a: input){
        (void)str.append(a);
        if (i!=(input.size()-1)){
            str.append(" ");
        }
        i++;
    }
    return str;
}

/*
Validates Namespace Prefix !
These characters aren't allowed:
- ASCII WHITESPACE (U+0009 TAB, U+000A LF, U+000C FF, U+000D CR, or U+0020 SPACE)
- U+0000 NULL
- U+002F (/)
- U+003E (>)
*/
bool valid_namespace_prefix(DOMString input){
    if (input.size()==0){ return false; }
    unsigned int temp;
    for (auto it=input.begin(); it!=input.end();){
        try{
            temp = utf8::next(it, input.end());
        }
        catch (utf8::not_enough_room){
            break;
        }
        if (temp==9 || temp==10 || temp==12 || temp==13 || temp==32 || temp==0 || temp==47 || temp==62){
            return false;
        }
    }
    return true;
}


/*
Validates Attribute Names !
These characters aren't allowed:
- ASCII WHITESPACE (U+0009 TAB, U+000A LF, U+000C FF, U+000D CR, or U+0020 SPACE)
- U+0000 NULL
- U+002F (/)
- U+003D (=)
- U+003E (>)
*/
bool valid_attribute_local_name(DOMString input){
    if (input.size()==0){ return false; }
    int temp;
    for (auto it=input.begin(); it!=input.end();){
        if (temp==9 || temp==10 || temp==12 || temp==13 || temp==32 || temp==0 || temp==47 || temp==61 || temp==62){
            return false;
        }
    }
    return true;
}



//Validates Element Names !
bool valid_element_local_name(DOMString input){
    if (input.size()==0){ return false; }
    auto it = input.begin();
    unsigned int first = utf8::next(it, input.end());
    unsigned int temp;
    if ((first>=65 && first<=90) || (first>=97 && first<=122)){
        for (;it<input.end();){
            try{
                temp = utf8::next(it, input.end());
            }
            catch (utf8::not_enough_room){
                break;
            }
            if (temp==9 || temp==10 || temp==12 || temp==13 || temp==32 || temp==0 || temp==47 || temp==62){
                return false;
            }
        }
        return true;
    }
    if (first!=58 && first!=95 && (first<128 || first>1114111)){
        return false;
    }
    for (it=input.begin();it<input.end();){
        try{
            temp = utf8::next(it, input.end());
        }
        catch (utf8::not_enough_room){
            break;
        }
        if ((temp<65 || temp>90) && (temp<97 || temp>122) && (temp<48 || temp>57) && temp!=45 && temp!=46 && temp!=58 && temp!=95 && (temp<128 || temp>1114111)){
            return false;
        }
    }
    return true;
}


/*
Validates DocType Names !
These characters aren't allowed:
- ASCII WHITESPACE (U+0009 TAB, U+000A LF, U+000C FF, U+000D CR, or U+0020 SPACE)
- U+0000 NULL
- U+003E (>)
*/
bool valid_doctype_name(DOMString input){
    unsigned int temp;
    for (auto it=input.begin(); it<input.end();){
        temp = utf8::next(it, input.end());
        if (temp==9 || temp==10 || temp==12 || temp==13 || temp==32 || temp==0 || temp==62){
            return false;
        }
    }
    return true;
}



// From the HTML Specification
bool valid_custom_element_name(DOMString name){
    if (!valid_element_local_name(name)){ return false; }
    int a = name.at(0);
    if (a<97 && a>122){ return false; }
    bool containsHyphen = false;
    for (auto ch: name){
        if (ch=='-'){ containsHyphen = true; }
        int c = ch;
        if (c>=65 && c<=90){ return false; }
    }
    if (!containsHyphen){ return false; }
    if (name=="annotation-xml" || name=="color-profile" || name=="font-face" || name=="font-face-src" || name=="font-face-uri" || name=="font-face-format" || name=="font-face-name" || name=="missing-glyph"){
        return false;
    }
    return true;
}

bool valid_shadow_host_name(DOMString name){
    if (!valid_custom_element_name(name)){ return false; }
    if (name!="article" && name!="aside" && name!="blockquote" && name!="body" && name!="div" && name!="footer" && name!="h1" && name!="h2" && name!="h3" && name!="h4" && name!="h5" && name!="h6" && name!="header" && name!="main" && name!="nav" && name!="p" && name!="section" && name!="span"){
        return false;
    }
    return true;
}



/*
It validates and extracts namespace `prefix` and `localName` based on other args.
If the `qualifiedName` contains a (:) it cuts it in half to feed `prefix` and `localName`. Else, `localName` gets `qualifiedName` and `prefix` is null
`prefix` is validated and matched with it's corresponding namespace (1st arg) whereas
the `localName` is being validated to be an `attribute` or an `element` based on the value of `context`
*/
void validate_and_extract(std::optional<DOMString> &namesp,DOMString qualifiedName, DOMString context,std::optional<DOMString> &prefix,DOMString &localName){
    if (namesp.has_value() && namesp.value()==""){ namesp = std::nullopt; }
    prefix = std::nullopt;
    localName = qualifiedName;
    if (qualifiedName.find(":")!=std::string::npos){
        std::vector<DOMString> splitResult = split_text(qualifiedName, ":");
        prefix = splitResult[0];
        localName = splitResult[1];
        if (!valid_namespace_prefix(prefix.value())){ throw InvalidCharacterError("The prefix aka 'text before colon (:)' in the qualifiedName (2nd arg) should be a valid namespace prefix !"); }
    }
    assert(!prefix.has_value() || valid_namespace_prefix(prefix.value()));
    if (context=="attribute" && !valid_attribute_local_name(localName)){ throw InvalidCharacterError("qualified name (sometimes, text after colon (:)) isn't a valid attribute name !"); }
    if (context=="element" && !valid_element_local_name(localName)){ throw InvalidCharacterError("qualified name (sometimes, text after colon (:)) isn't a valid element name !"); }
    if (!prefix.has_value() && !namesp.has_value()){ throw NamespaceError("Namespace error !! Namespace &  Namespace Prefix are both null !"); }
    if (prefix.has_value() && prefix.value()=="xml" && namesp.has_value() && namesp.value()!="http://www.w3.org/XML/1998/namespace"){ throw NamespaceError("Namespace error !! Namespace & namespace prefix don't match !"); }
    if ((qualifiedName=="xmlns" ||(prefix.has_value() && prefix.value()=="xmlns")) && (!namesp.has_value() || namesp.value()!="http://www.w3.org/2000/xmlns/")){ throw NamespaceError("Namespace error !! Namespace & namespace prefix don't match !"); }
    if (namesp.has_value() && namesp.value()=="http://www.w3.org/2000/xmlns/" && (qualifiedName!="xmlns" && (!prefix.has_value() ||(prefix.has_value() && prefix.value()!="xmlns")))){ throw NamespaceError("Namespace error !! Namespace & namespace prefix don't match !"); }
}








// More algos

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


DOMString replace_data(Node* node, unsigned long offset, unsigned long count, DOMString data){
    unsigned length = node->length();
    if (offset>length){ throw IndexSizeError("greater than error !!"); }
    if ((offset+count)>length){ count = length-offset; }
    // queue mutation record
	return "";
}

Element* create_element(Document* document, DOMString localName, std::optional<DOMString> namesp, std::optional<DOMString> prefix, std::optional<DOMString> is, bool synchronousCustomElements, std::variant<DOMString,std::nullptr_t,CustomElementRegistry> registry){
    return nullptr;
}

void flatten_element_creation_options(std::variant<DOMString,ElementCreationOptions> options, Document* document, CustomElementRegistry* registry, std::optional<DOMString> &is){
    if (std::holds_alternative<ElementCreationOptions>(options)){
        ElementCreationOptions temp = std::get<ElementCreationOptions>(options);
        if (temp.CustomElementRegistry){
            registry = temp.CustomElementRegistry;
        }
        if (registry!=document->custom_element_registry){
            throw NotSupportedError("not supported boi !!");
        }
        if (temp.is.has_value()){
            is = temp.is;
        }
        if (registry!=nullptr && is!=std::nullopt){
            throw NotSupportedError("not supported boi !!");
        }
    }
    if (registry==nullptr){}
}

void adopt(Node* node, Document* document){
    // Document* oldDocument = node->ownerDocument;
    if (node->parentNode!=nullptr){ remove_node(node); }
    // if (document!=oldDocument){
    //     for (auto inclusiveDescendant: node->shad)
    // }
}

Element* internal_create_element_ns(Document* document, std::optional<DOMString> namesp, DOMString qualifiedName, std::variant<DOMString,ElementCreationOptions> options){
    std::optional<DOMString> prefix;
    DOMString localName;
    validate_and_extract(namesp, qualifiedName, "element", prefix, localName);
    CustomElementRegistry* registry;
    std::optional<DOMString> is;
    flatten_element_creation_options(options, document, registry, is);
    // return create_element(document, localName, namesp, prefix, is, true, registry);
    return new Element("","","");
}


void change_attribute_value(Attr* attribute, DOMString value){
    DOMString oldValue = attribute->value;
    attribute->value = value;
    // handle_attribute_changes(attribute, attribute->ownerElement, oldValue, value);
}

void append_attribute(Attr* attribute, Element* element){
    element->attributes.attribute_list.push_back(attribute);
    attribute->ownerElement = element;
    // attribute->ownerDocument = element->ownerDocument;
    // handle_attribute_changes(attribute, element, std::nullopt, attribute->value);
}

void remove_attribute(Attr* attribute){
    Element* element = attribute->ownerElement;
    element->attributes.attribute_list.erase(std::find(element->attributes.attribute_list.begin(), element->attributes.attribute_list.end(), attribute));
    attribute->ownerElement = nullptr;
    // handle_attribute_changes(attribute, element, attribute->value, std::nullopt);
}

void replace_attribute(Attr* oldAttribute, Attr* newAttribute){
    Element* element = oldAttribute->ownerElement;
    std::replace(element->attributes.attribute_list.begin(), element->attributes.attribute_list.end(), oldAttribute, newAttribute);
    newAttribute->ownerElement = element;
    // newAttribute->ownerDocument = element->ownerDocument;
    oldAttribute->ownerElement = nullptr;
    // handle_attribute_changes(oldAttribute, element, oldAttribute->value, newAttribute->value);
}

Attr* fetch_attribute(DOMString qualifiedName, Element* element){
    // if (element->ownerDocument->type!=XML){
    //     std::transform(qualifiedName.begin(), qualifiedName.end(), qualifiedName.begin(), [](unsigned char c){ return std::tolower(c); });
    // }
    for (auto attr: element->attributes.attribute_list){
        if (attr->qualifiedName()==qualifiedName){
            return attr;
        }
    }
    return nullptr;
}

Attr* fetch_attribute(std::optional<DOMString> namesp, DOMString localName, Element* element){
    if (namesp.has_value() && namesp.value()==""){ namesp = std::nullopt; }
    for (auto attr: element->attributes.attribute_list){
        if (attr->namespaceURI==namesp && attr->localName==localName){
            return attr;
        }
    }
    return nullptr;
}


DOMString fetch_attribute(Element* element, DOMString localName, std::optional<DOMString> namesp){
    Attr* attr = fetch_attribute(namesp, localName, element);
    if (attr==nullptr){ return ""; }
    return attr->value;
}


Attr* set_attribute(Attr* attr, Element* element){
    if (attr->ownerElement!=nullptr && !dynamic_cast<Element*>(attr->ownerElement)){ throw InUseAttributeError("In use !!"); }
    Attr* oldAttr = fetch_attribute(attr->namespaceURI, attr->localName, element);
    if (oldAttr==attr){ return attr; }
    if (oldAttr!=nullptr){
        replace_attribute(oldAttr, attr);
    }
    else{
        append_attribute(attr, element);
    }
    return oldAttr;
}


void set_attribute_value(Element* element, DOMString localName, DOMString value, std::optional<DOMString> prefix, std::optional<DOMString> namesp){
    Attr* attribute = fetch_attribute(namesp, localName, element);
    if (attribute==nullptr){
        Attr* attr = new Attr(localName);
        attr->namespaceURI = namesp;
        attr->prefix = prefix;
        attr->value = value;
        // attr->ownerDocument = element->ownerDocument;
        append_attribute(attr, element);
        return;
    }
    change_attribute_value(attribute, value);
}

Attr* remove_attribute_by_name(DOMString qualifiedName, Element* element){
    Attr* attr = fetch_attribute(qualifiedName, element);
    if (attr!=nullptr){
        remove_attribute(attr);
    }
    return attr;
}

Attr* remove_attribute_by_namespace(std::optional<DOMString> namesp, DOMString localName, Element* element){
    Attr* attr = fetch_attribute(namesp, localName, element);
    if (attr!=nullptr){
        remove_attribute(attr);
    }
    return attr;
}

void attach_shadow_root(Element* element, ShadowRootMode mode, bool clonable, bool serializable, bool delegatesFocus, SlotAssignmentMode slotAssignment, std::optional<CustomElementRegistry> registry){
    if (element->namespaceURI!="http://www.w3.org/1999/xhtml"){ throw NotSupportedError("nope not supported"); }
    // if (!ValidShadowHostName(element->localName)){ throw NotSupportedError("nope not supported boi !!"); }
    // if (ValidCustomElementName(element->localName) || element->is!=std::nullopt){}
    if (element->getshadow_root()!=nullptr){
        ShadowRoot* currentShadowRoot = element->getshadow_root();
        if (!currentShadowRoot->declarative || currentShadowRoot->mode!=mode){ throw NotSupportedError("nope not supporting :) !"); }
        else{
            for (auto child: currentShadowRoot->childNodes.node_list){
                remove_node(child);
            }
            currentShadowRoot->declarative = false;
            return;
        }
    }
    ShadowRoot* shadow = new ShadowRoot();
    // shadow->ownerDocument = element->ownerDocument;
    shadow->associatedHost = element;
    shadow->mode = mode;
    shadow->delegatesFocus = delegatesFocus;
    if (element->customElementState==PRECUSTOMIZED && element->customElementState==CUSTOM){
        shadow->availableToElementInternals = true;
    }
    shadow->slotAssignment = slotAssignment;
    shadow->declarative = false;
    shadow->clonable = clonable;
    shadow->serializable = serializable;
    shadow->custom_element_registry = &registry.value();
    element->shadow_root = shadow;
}

Node* insert_adjacent(Element* element, DOMString where, Node* node){
    std::transform(where.begin(), where.end(), where.begin(), [](unsigned char c){ return std::tolower(c); } );
    if (where=="beforebegin"){
        if (element->parentNode==nullptr){ return nullptr; }
        return pre_insert_node(node, dynamic_cast<Node*>(element)->parentNode, dynamic_cast<Node*>(element));
    }
    else if (where=="afterbegin"){
        return pre_insert_node(node, dynamic_cast<Node*>(element), dynamic_cast<Node*>(element)->firstChild());
    }
    else if (where=="beforeend"){
        return pre_insert_node(node, dynamic_cast<Node*>(element), nullptr);
    }
    else if (where=="afterend"){
        if (element->parentNode==nullptr){ return nullptr; }
        return pre_insert_node(node, element->parentNode, dynamic_cast<Node*>(element)->nextSibling());
    }
    else{
        throw SyntaxError("syntax errrrrror boi !!");
    }
}

DOMString replace_all(Node* node, Node* newParent){
	return "";
}


DOMString substring_data(Node* node, unsigned long offset, unsigned long count){
    unsigned length = node->length();
    if (offset>length){ throw IndexSizeError("greater than error !!"); }
    CharacterData* temp = dynamic_cast<CharacterData*>(node);
    if ((offset+count)>length){ return temp->getdata().substr(offset); }
    return temp->getdata().substr(offset, count);
}


bool check_exclusive_text_node(Text* node){
    if (dynamic_cast<CDATASection*>(node)){ return false; }
    return true;
}

std::vector<Text*> contiguous_text_nodes(Text* node){
    std::vector<Text*> temp = {node};
    Text* currentNode = dynamic_cast<Text*>(node->previousSibling());
    while (currentNode){
        temp.insert(temp.begin(), currentNode);
        currentNode = dynamic_cast<Text*>(currentNode->previousSibling());
    }
    currentNode = dynamic_cast<Text*>(node->nextSibling());
    while (currentNode){
        temp.push_back(currentNode);
        currentNode = dynamic_cast<Text*>(currentNode->nextSibling());
    }
    return temp;
}

std::vector<Text*> contiguous_exclusive_text_nodes(Text* node){
    std::vector<Text*> temp = {node};
    Text* currentNode = dynamic_cast<Text*>(dynamic_cast<Node*>(node)->previousSibling());
    auto smth = dynamic_cast<Node*>(currentNode);
    while (currentNode && !dynamic_cast<CDATASection*>(currentNode)){
        temp.insert(temp.begin(), currentNode);
        currentNode = dynamic_cast<Text*>(smth->previousSibling());
        smth = dynamic_cast<Node*>(currentNode);
    }
    currentNode = dynamic_cast<Text*>(node->nextSibling());
    while (currentNode && !dynamic_cast<CDATASection*>(currentNode)){
        temp.push_back(currentNode);
        currentNode = dynamic_cast<Text*>(smth->nextSibling());
        smth = dynamic_cast<Node*>(currentNode);
    }
    return temp;
}




DOMString child_text_content(Node* node){
    DOMString temp = "";
    for (auto a: node->childNodes.node_list){
        Text* temp2 = dynamic_cast<Text*>(a);
        if (temp2){ temp+= temp2->getdata(); }
    }
    return temp;
}

DOMString descendant_text_content(Node* node){
    Node* currentNode = node->childNodes[0];
    std::vector<Node*> temp = {currentNode};
    Text* temp2;
    DOMString data = "";
    while (currentNode!=nullptr){
        temp2 = dynamic_cast<Text*>(currentNode);
        auto temp3 = dynamic_cast<CharacterData*>(currentNode);
        if (temp2){
            data += temp3->getdata();
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
    return data;
}


Text* split_text_node(Text* node, unsigned long offset){
    auto smth = dynamic_cast<Node*>(node);
    unsigned long length = smth->length();
    if (offset>length){ throw IndexSizeError("size issues ! You are fat :) "); }
    unsigned long count = length - offset;

    DOMString data = substring_data(smth, offset, count);
    Text* new_node = new Text(data);
    // new_node->ownerDocument = smth->ownerDocument;

    Node* parent = smth->parentNode;
    if (parent!=nullptr){
        insert_node(dynamic_cast<Node*>(new_node), parent, smth->nextSibling());
    }
    replace_data(dynamic_cast<Node*>(node), offset, count, "");
    return new_node;
}

int position(Node* nodeA, unsigned long offsetA, Node* nodeB, unsigned long offsetB){
    assert(nodeA->getRootNode()==nodeB->getRootNode());
    if (nodeA==nodeB){
        if (offsetA==offsetB){ return 0; }
        if (offsetA<offsetB){ return -1; }
        return 1;
    }
    if (*nodeA^nodeB){
        int a = position(nodeB, offsetB, nodeA, offsetA);
        if (a==-1){ return 1; }
        if (a==1){ return -1; }
    }
    if (check_ancestor(nodeB, nodeA)){
        Node* child = nodeB;
        bool ischild = false;
        int index;
        while (!ischild){
            index = 0;
            for (auto a: nodeA->childNodes.node_list){
                if (a==child){ ischild = true; break; }
                index++;
            }
            if (!ischild){
                child = child->parentNode;
            }
        }
        if (index<offsetA){
            return 1;
        }
    }
    return -1;
}


bool static_range_valid(StaticRange* range){
    if (range->startContainer->getRootNode(true)!=range->endContainer->getRootNode(true)){
        return false;
    }
    if (range->startOffset<0 || range->startOffset>range->startContainer->length()){
        return false;
    }
    if (range->endOffset<0 || range->endOffset>range->endContainer->length()){
        return false;
    }
    int temp = position(range->startContainer, range->startOffset, range->endContainer, range->endOffset);
    if (temp==1){
        return false;
    }
    return true;
}

bool contained_in_range(Node* node, Range* range){
    if (node->getRootNode()!=range->startContainer->getRootNode()){
        return false;
    }
    int temp = position(node, 0, range->startContainer, range->startOffset);
    if (temp==0 || temp==-1){
        return false;
    }
    temp = position(node, node->length(), range->endContainer, range->endOffset);
    if (temp==0 || temp==1){
        return false;
    }
    return true;
}

bool partially_contained_in_range(Node* node, Range* range){
    bool one = check_ancestor(range->startContainer, node, true);
    bool two = check_ancestor(range->endContainer, node, true);
    if ((one && !two) || (!one && two)){
        return true;
    }
    return false;
}

void pre_remove_range(Node* node){
    Node* parent = node->parentNode;
    assert(parent!=nullptr);
    unsigned long index = node->index();
}

void set_start_end(Range* range, Node* node, int offset, bool start){
    if (dynamic_cast<DocumentType*>(node)){ throw InvalidNodeTypeError("invalid node type !!!!!"); }
    if (offset>node->length()){ throw IndexSizeError("size issues, fatty !!"); }
    if (start){
        if ((range->startContainer->getRootNode()!=node->getRootNode()) || position(node, offset, range->endContainer, range->endOffset)==1){
            range->endContainer = node;
            range->endOffset = offset;
        }
        range->startContainer = node;
        range->startOffset = offset;
    }
    else{
        if ((range->startContainer->getRootNode()!=node->getRootNode()) || position(node, offset, range->startContainer, range->startOffset)==-1){
            range->startContainer = node;
            range->startOffset = offset;
        }
        range->endContainer = node;
        range->endOffset = offset;
    }

}

void select_node_within_rangee(Node* node, Range* range){
    Node* parent = node->parentNode;
    if (parent==nullptr){ throw InvalidNodeTypeError("invalid node type dummy !"); }
    unsigned long index = node->index();
    range->startContainer = parent;
    range->startOffset = index;
    range->endContainer = parent;
    range->endOffset = index + 1;
}


DocumentFragment* extract_range(Range* range){
    DocumentFragment* fragment = new DocumentFragment();
    // fragment->ownerDocument = range->startContainer->ownerDocument;
    if (range->collapsed()){
        return fragment;
    }
    Node* original_startnode = range->startContainer;
    unsigned long original_startoffset = range->startOffset;
    Node* original_endnode = range->endContainer;
    unsigned long original_endoffset = range->endOffset;
    
    if (original_startnode==original_endnode && dynamic_cast<CharacterData*>(original_startnode)){
        Node* temp = clone_node(original_startnode);
        CharacterData* clone = dynamic_cast<CharacterData*>(temp);
        clone->setdata(substring_data(original_startnode, original_startoffset, original_endoffset - original_startoffset));
        pre_insert_node(dynamic_cast<Node*>(clone), dynamic_cast<Node*>(fragment), nullptr);
        replace_data(original_startnode, original_startoffset, original_endoffset - original_startoffset, "");
        return fragment;
    }
    Node* common_ancestor = original_startnode;
    while (!check_ancestor(original_endnode, common_ancestor, true)){
        common_ancestor = common_ancestor->parentNode;
    }
    Node* first_partially_contained_child = nullptr;
    if (!check_ancestor(original_endnode, original_startnode, true)){
        for (auto a: common_ancestor->childNodes.node_list){
            if (partially_contained_in_range(a, range)){
                first_partially_contained_child = a;
                break;
            }
        }
    }
    Node* last_partially_contained_child = nullptr;
    if (!check_ancestor(original_startnode, original_endnode, true)){
        for (auto a: common_ancestor->childNodes.node_list){
            if (partially_contained_in_range(a, range)){
                last_partially_contained_child = a;
            }
        }
    }
    std::vector<Node*> contained_children = {};
    for (auto a: common_ancestor->childNodes.node_list){
        if (contained_in_range(a, range)){
            contained_children.push_back(a);
            if (dynamic_cast<DocumentType*>(a)){
                throw HeirarchyRequestError("hierarchy issue dude !!");
            }
        }
    }
    Node* new_node;
    unsigned long new_offset;
    if (check_ancestor(original_endnode, original_startnode, true)){
        new_node = original_startnode;
        new_offset = original_startoffset;
    }
    else{
        Node* referenceNode = original_startnode;
        Node* parent = referenceNode->parentNode;
        while (parent!=nullptr && !check_ancestor(original_endnode, parent, true)){
            referenceNode = parent;
            parent = referenceNode->parentNode;
        }
        new_node = referenceNode->parentNode;
        new_offset = referenceNode->index() + 1;
    }
    if (dynamic_cast<CharacterData*>(first_partially_contained_child)){
        Node* temp = clone_node(original_startnode);
        CharacterData* clone = dynamic_cast<CharacterData*>(temp);
        clone->setdata(substring_data(original_startnode, original_startoffset, original_startnode->length() - original_startoffset));
        // pre_insert_node(dynamic_cast<Node*>(clone), fragment, nullptr);
        replace_data(original_startnode, original_startoffset, original_startnode->length() - original_startoffset, "");
    }
    else if (first_partially_contained_child!=nullptr){
        Node* temp = clone_node(first_partially_contained_child);
        CharacterData* clone = dynamic_cast<CharacterData*>(temp);
        // pre_insert_node(dynamic_cast<Node*>(clone), fragment, nullptr);
        Range* subrange = new Range();
        subrange->startContainer = original_startnode;
        subrange->startOffset = original_startoffset;
        subrange->endContainer = first_partially_contained_child;
        subrange->endOffset = first_partially_contained_child->length();
        DocumentFragment* subfragment = extract_range(subrange);
        // pre_insert_node(subfragment, clone, nullptr);   
    }
    for (auto child: contained_children){
        // pre_insert_node(child, fragment, nullptr);
    }
    if (dynamic_cast<CharacterData*>(last_partially_contained_child)){
        Node* temp = clone_node(original_endnode);
        CharacterData* clone = dynamic_cast<CharacterData*>(temp);
        clone->setdata(substring_data(original_endnode, 0, original_endoffset));
        pre_insert_node(dynamic_cast<Node*>(clone), dynamic_cast<Node*>(fragment), nullptr);
        replace_data(original_endnode, 0, original_endoffset, "");
    }
    else if (first_partially_contained_child!=nullptr){
        Node* temp = clone_node(last_partially_contained_child);
        CharacterData* clone = dynamic_cast<CharacterData*>(temp);
        pre_insert_node(dynamic_cast<Node*>(clone), dynamic_cast<Node*>(fragment), nullptr);
        Range* subrange = new Range();
        subrange->startContainer = last_partially_contained_child;
        subrange->startOffset = 0;
        subrange->endContainer = original_endnode;
        subrange->endOffset = original_endoffset;
        DocumentFragment* subfragment = extract_range(subrange);
        pre_insert_node(dynamic_cast<Node*>(subfragment), dynamic_cast<Node*>(clone), nullptr);   
    }
    range->startContainer = new_node;
    range->endContainer = new_node;
    range->startOffset = new_offset;
    range->endOffset = new_offset;
    return fragment;
}



DocumentFragment* clone_contents(Range* range){
    DocumentFragment* fragment = new DocumentFragment();
    // fragment->ownerDocument = range->startContainer->ownerDocument;
    if (range->collapsed()){
        return fragment;
    }
    Node* original_startnode = range->startContainer;
    unsigned long original_startoffset = range->startOffset;
    Node* original_endnode = range->endContainer;
    unsigned long original_endoffset = range->endOffset;
    
    if (original_startnode==original_endnode && dynamic_cast<CharacterData*>(original_startnode)){
        Node* temp = clone_node(original_startnode);
        CharacterData* clone = dynamic_cast<CharacterData*>(temp);
        clone->setdata(substring_data(original_startnode, original_startoffset, original_endoffset - original_startoffset));
        pre_insert_node(dynamic_cast<Node*>(clone), dynamic_cast<Node*>(fragment), nullptr);
        return fragment;
    }
    Node* common_ancestor = original_startnode;
    while (!check_ancestor(original_endnode, common_ancestor, true)){
        common_ancestor = common_ancestor->parentNode;
    }
    Node* first_partially_contained_child = nullptr;
    if (!check_ancestor(original_endnode, original_startnode, true)){
        for (auto a: common_ancestor->childNodes.node_list){
            if (partially_contained_in_range(a, range)){
                first_partially_contained_child = a;
                break;
            }
        }
    }
    Node* last_partially_contained_child = nullptr;
    if (!check_ancestor(original_startnode, original_endnode, true)){
        for (auto a: common_ancestor->childNodes.node_list){
            if (partially_contained_in_range(a, range)){
                last_partially_contained_child = a;
            }
        }
    }

    std::vector<Node*> contained_children = {};
    for (auto a: common_ancestor->childNodes.node_list){
        if (contained_in_range(a, range)){
            contained_children.push_back(a);
            if (dynamic_cast<DocumentType*>(a)){
                throw HeirarchyRequestError("hierarchy issue dude !!");
            }
        }
    }

    if (dynamic_cast<CharacterData*>(first_partially_contained_child)){
        Node* temp = clone_node(original_startnode);
        CharacterData* clone = dynamic_cast<CharacterData*>(temp);
        clone->setdata(substring_data(original_startnode, original_startoffset, original_startnode->length() - original_startoffset));
        pre_insert_node(dynamic_cast<Node*>(clone), dynamic_cast<Node*>(fragment), nullptr);
    }
    else if (first_partially_contained_child!=nullptr){
        Node* temp = clone_node(first_partially_contained_child);
        CharacterData* clone = dynamic_cast<CharacterData*>(temp);
        pre_insert_node(dynamic_cast<Node*>(clone), dynamic_cast<Node*>(fragment), nullptr);
        Range* subrange = new Range();
        subrange->startContainer = original_startnode;
        subrange->startOffset = original_startoffset;
        subrange->endContainer = first_partially_contained_child;
        subrange->endOffset = first_partially_contained_child->length();
        DocumentFragment* subfragment = clone_contents(subrange);
        pre_insert_node(dynamic_cast<Node*>(subfragment), dynamic_cast<Node*>(clone), nullptr);
    }
    for (auto child: contained_children){
        Node* clone = clone_node(dynamic_cast<Node*>(child));
        pre_insert_node(dynamic_cast<Node*>(clone), dynamic_cast<Node*>(fragment), nullptr);
    }

    if (dynamic_cast<CharacterData*>(last_partially_contained_child)){
        Node* temp = clone_node(original_endnode);
        CharacterData* clone = dynamic_cast<CharacterData*>(temp);
        clone->setdata(substring_data(original_endnode, 0, original_endoffset));
        pre_insert_node(dynamic_cast<Node*>(clone), dynamic_cast<Node*>(fragment), nullptr);
    }
    else if (first_partially_contained_child!=nullptr){
        Node* temp = clone_node(last_partially_contained_child);
        CharacterData* clone = dynamic_cast<CharacterData*>(temp);
        pre_insert_node(dynamic_cast<Node*>(clone), dynamic_cast<Node*>(fragment), nullptr);
        Range* subrange = new Range();
        subrange->startContainer = last_partially_contained_child;
        subrange->startOffset = 0;
        subrange->endContainer = original_endnode;
        subrange->endOffset = original_endoffset;
        DocumentFragment* subfragment = clone_contents(subrange);
        pre_insert_node(dynamic_cast<Node*>(subfragment), dynamic_cast<Node*>(clone), nullptr);
    }
    return fragment;
}


void insert_node_in_range(Node* node, Range* range){
    if (dynamic_cast<ProcessingInstruction*>(range->startContainer) || dynamic_cast<Comment*>(range->startContainer) ||(dynamic_cast<Text*>(range->startContainer) && range->startContainer->parentNode==nullptr) || range->startContainer==node){
        throw HeirarchyRequestError("hierarchy ! spelling issues :) ");
    }
    Node* referenceNode = nullptr;
    if (dynamic_cast<Text*>(range->startContainer)){
        referenceNode = range->startContainer;
    }
    else{
        for (auto a: range->startContainer->childNodes.node_list){
            if (a->index()==range->startOffset){
                referenceNode = a;
                break;
            }
        }
    }
    Node* parent;
    if (!referenceNode){
        parent = range->startContainer;
    }
    else{
        parent = referenceNode->parentNode;
    }
    ensure_pre_insert_validity(node, parent, referenceNode);
    Text* tempji = dynamic_cast<Text*>(range->startContainer);
    if (tempji){
        referenceNode = dynamic_cast<Node*>(split_text_node(tempji, range->startOffset));
    }
    if (node==referenceNode){
        referenceNode = referenceNode->nextSibling();
    }
    if (node->parentNode!=nullptr){
        remove_node(node);
    }

    unsigned long newOffset;
    if (referenceNode==nullptr){
        newOffset = parent->length();
    }
    else{
        newOffset = referenceNode->index();
    }

    if (dynamic_cast<DocumentFragment*>(node)){
        newOffset += node->length();
    }
    else{
        newOffset++;
    }

    pre_insert_node(node, parent, referenceNode);
    if (range->collapsed()){
        range->endContainer = parent;
        range->endOffset = newOffset;
    }
}


void pre_remove_steps(NodeIterator* node_iterator, Node* toBeRemovedNode){
    if (!check_ancestor(node_iterator->referenceNode, toBeRemovedNode,true) || toBeRemovedNode==node_iterator->root){
        return;
    }
    if (node_iterator->pointerBeforeReferenceNode){
        // if (next!=nullptr){
        //     node_iterator->referenceNode = next;
        //     return;
        // }
        node_iterator->pointerBeforeReferenceNode = false;
    }
    if (toBeRemovedNode->previousSibling()==nullptr){
        // node_iterator->referenceNode = toBeRemovedNode->parentNode();
    }
    else{
        Node* prev = toBeRemovedNode->previousSibling();
        for (auto a: prev->childNodes.node_list){}
    }
}

Node* traverse(NodeIterator* iterator, unsigned long direction){
    Node* reference = iterator->referenceNode;
    bool beforeNode = iterator->pointerBeforeReferenceNode;
    Node* node;
    while (true){
        if (direction==1){
            if (!beforeNode){

            }
            if (beforeNode){ beforeNode = false; }
        }
        else if (direction==-1){
            if (beforeNode){

            }
            if (!beforeNode){ beforeNode = true; }
        }
        unsigned short result = iterator->filter_node(node);
        if (result==FILTER_ACCEPT){
            break;
        }
    }
    iterator->referenceNode = node;
    iterator->pointerBeforeReferenceNode = beforeNode;
    return node;
}


Node* traverse_children(TreeWalker* walker, unsigned long type){
    Node* node = walker->currentNode;
    Node* child;
    if (type==1){
        node = node->firstChild();
    }
    else if (type==-1){
        node = node->lastChild();
    }
    while (node!=nullptr){
        unsigned short result = walker->filter_node(node);
        if (result==FILTER_ACCEPT){
            walker->currentNode = node;
            return node;
        }
        else if (result == FILTER_SKIP){
            if (type==1){ child = node->firstChild(); }
            else if (type==-1){ child = node->lastChild(); }
        }
        
        while (node!=nullptr){
            Node* sibling;
            if (type==1){
                sibling = node->nextSibling();
            }
            else if (type==-1){
                sibling = node->previousSibling();
            }
            if (sibling!=nullptr){
                node = sibling;
                break;
            }
            Node* parent = node->parentNode;
            if (parent==nullptr || parent==walker->root || parent==walker->currentNode){
                return nullptr;
            }
            node = parent;
        }
    }
    return nullptr;
}


Node* traverse_sibling(TreeWalker* walker, unsigned long type){
    Node* node = walker->currentNode;
    if (node==walker->root){
        return nullptr;
    }
    while (true){
        Node* sibling;
        if (type==1){
            sibling = node->nextSibling();
        }
        else if (type==-1){
            sibling = node->previousSibling();
        }
        while (sibling!=nullptr){
            node = sibling;
            unsigned short result = walker->filter_node(node);

            if (result==FILTER_ACCEPT){
                walker->currentNode = node;
                return node;
            }

            if (type==1){
                sibling = node->firstChild();
            }
            else if (type==-1){
                sibling = node->lastChild();
            }

            if (result==FILTER_REJECT || sibling==nullptr){
                if (type==1){
                    sibling = node->nextSibling();
                }
                else if (type==-1){
                    sibling = node->previousSibling();
                }
            }
        }
        node = node->parentNode;
        if (node==nullptr || node==walker->root){
            return nullptr;
        }
        if (walker->filter_node(node)==FILTER_ACCEPT){
            return nullptr;
        }
    }
}

bool default_passive_value(const DOMString &type, EventTarget* eventTarget){
    if (type=="touchstart" || type=="touchmove" || type=="wheel" || type=="mousewheel"){
        if (dynamic_cast<Window*>(eventTarget)){
            return true;
        }
        else{
            auto temp = dynamic_cast<Node*>(eventTarget);
            if (temp && temp->ownerDocument==(dynamic_cast<Document*>(eventTarget))){
                return true;
            }
            else if (temp && dynamic_cast<Document*>(temp->parentNode)==temp->ownerDocument){
                return true;
            }
        }
    }
    return false;
}


bool dispatch_event(Event* event, EventTarget* target, std::optional<bool> legacy_target_override_flag, std::optional<bool> legacy_output_did_listeners_throw_flag){
    event->dispatch_flag = true;

    EventTarget* targetOverride;
    if (!legacy_target_override_flag.has_value()) {
        targetOverride = target;
    }
    else{
        // set targetOverride to target's associatedDocument
    }

    EventTarget* activationTarget = nullptr;
    EventTarget* relatedTarget = retard(event->getrelatedTarget(), target);
    bool clearTargets = false;

    Node* targetNode = dynamic_cast<Node*>(target);

    if (target!=relatedTarget || target==event->getrelatedTarget()) {
        std::vector<EventTarget*> touchTargets = {};
        for (auto touchTarget: event->touch_target_list){
            touchTargets.push_back(retard(touchTarget,target));
        }

        append_to_event_path(event,target,targetOverride,relatedTarget,touchTargets,false);

        bool isActivationEvent = false;
        if ((dynamic_cast<MouseEvent*>(event)) && event->gettype()=="click"){
            isActivationEvent = true;
        }
     
        if (isActivationEvent && target->has_activation_behavior){
            activationTarget = target;
        }
        EventTarget* slottable = nullptr;
        auto te = dynamic_cast<Element*>(target);
        if (te && te->assignedSlot){
            slottable = target;
        }
        else{
            auto f = dynamic_cast<Text*>(target);
            if (f && f->assignedSlot){
                slottable = target;
            }
        }

        bool slot_in_closed_tree = false;
        EventTarget* parent = target->get_the_parent(event);
        while (parent){
            auto parentNode = dynamic_cast<Node*>(parent);
            auto parentRoot = dynamic_cast<ShadowRoot*>(parentNode->getRootNode());
            if (slottable){
                assert(dynamic_cast<Element*>(parent) && parentRoot && parentRoot->host());
                slottable = nullptr;
                if (parentRoot && parentRoot->mode==closed){
                    slot_in_closed_tree = true;
                }
            }
            auto te = dynamic_cast<Element*>(parent);
            if (te && te->assignedSlot){
                slottable = parent;
            }
            else{
                auto f = dynamic_cast<Text*>(parent);
                if (f && f->assignedSlot){
                    slottable = parent;
                }
            }
            relatedTarget = retard(event->getrelatedTarget(),parent);
            std::vector<EventTarget*> touchTargets = {};
            for (EventTarget* touchboi: event->touch_target_list){
                touchTargets.push_back(retard(touchboi,parent));
            }
            if (dynamic_cast<Window*>(parent) || (parentNode && check_shadow_including_descendant(targetNode->getRootNode(),parentNode,true))){
                if (isActivationEvent && event->getbubbles() && !activationTarget && parent->has_activation_behavior){
                    activationTarget = parent;
                }
                append_to_event_path(event, parent, nullptr, relatedTarget, touchTargets, slot_in_closed_tree);
            }
            else if (parent==relatedTarget){
                parent = nullptr;
            }
            else{
                target = parent;
                if (isActivationEvent && !activationTarget && target->has_activation_behavior){
                    activationTarget = target;
                }
                append_to_event_path(event, parent, target, relatedTarget, touchTargets, slot_in_closed_tree);
            }
            if (parent){
                parent = parent->get_the_parent(event);
            }
            slot_in_closed_tree = false;
        }

        path_structs clearTargetsStruct;
        for (path_structs &a: event->path){
            if (a.shadow_adjusted_target){
                clearTargetsStruct = a;
            }
        }

        auto tempShadowAdjustedTarget = dynamic_cast<Node*>(clearTargetsStruct.shadow_adjusted_target);
        if (tempShadowAdjustedTarget && dynamic_cast<ShadowRoot*>(tempShadowAdjustedTarget->getRootNode())){
            clearTargets = true;
        }
        else{
            auto tempRelatedTarget = dynamic_cast<Node*>(clearTargetsStruct.related_target);
            if (tempRelatedTarget && dynamic_cast<ShadowRoot*>(tempRelatedTarget->getRootNode())){
                clearTargets = true;
            }
            else{
                Node* tempNode2;
                for (EventTarget* a: clearTargetsStruct.touch_target_list){
                    tempNode2 = dynamic_cast<Node*>(a);
                    if (tempNode2 && dynamic_cast<ShadowRoot*>(tempNode2->getRootNode())){
                        clearTargets = true;
                        break;
                    }
                }
            }
        }


        if (activationTarget && activationTarget->has_legacy_pre_activation_behavior){
            activationTarget->legacy_pre_activation_behavior_algorithm();
        }
        std::vector<path_structs> rev_path = std::vector<path_structs>(event->path.rbegin(),event->path.rend());
        for (path_structs &struc: rev_path){
            if (struc.shadow_adjusted_target){
                event->seteventPhase(AT_TARGET);
            }
            else{
                event->seteventPhase(CAPTURING_PHASE);
            }
            invoke_event(struc, event, CAPTURING_PHASE, legacy_output_did_listeners_throw_flag);
        }
        for (path_structs& a: event->path){
            if (a.shadow_adjusted_target){
                event->seteventPhase(AT_TARGET);
            }
            else{
                if (!(event->getbubbles())){
                    continue;
                }
                event->seteventPhase(BUBBLING_PHASE);
            }
            invoke_event(a, event, BUBBLING_PHASE, legacy_output_did_listeners_throw_flag);
        }
    }
    event->seteventPhase(NONE);
    event->currentTarget = nullptr;
    event->path.clear();
    event->dispatch_flag = false;
    event->stop_propagation_flag = false;
    event->stop_immediate_propagation_flag = false;
    if (clearTargets){
        event->target = nullptr;
        event->relatedTarget = nullptr;
        event->touch_target_list.clear();
    }
    if (activationTarget){
        if (!event->canceled_flag){
            activationTarget->activation_behavior_algorithm(event);
        }
        else if(activationTarget->has_legacy_canceled_activation_behavior){
            activationTarget->legacy_canceled_activation_behavior_algorithm;
        }
    }
    if (event->canceled_flag){
        return false;
    }
    return true;
}

void append_to_event_path(Event* event, EventTarget* invocationTarget, EventTarget*  shadowAdjustedTarget, EventTarget* relatedTarget, std::vector<EventTarget*> &touchTargets, bool slot_in_closed_tree){
    bool invocationTargetInShadowTree = false;
    auto tempNode = dynamic_cast<Node*>(invocationTarget);
    if (tempNode &&  dynamic_cast<ShadowRoot*>(tempNode->getRootNode())){
        invocationTargetInShadowTree = true;
    }
    bool root_of_closed_tree = false;
    auto temp = dynamic_cast<ShadowRoot*>(invocationTarget);
    if (temp && temp->mode==closed){
        root_of_closed_tree = true;
    }
    event->path.push_back(path_structs(invocationTarget, invocationTargetInShadowTree, shadowAdjustedTarget, relatedTarget, touchTargets, root_of_closed_tree, slot_in_closed_tree));
}

bool inner_invoke(Event* event, std::vector<event_listener*> &listeners,enum event_phase phase, bool invocationTargetInShadowTree, std::optional<bool> legacyOutputDidListenersThrowFlag){
    bool found = false;
    for (event_listener* listener: listeners) {
        if (!(listener->removed)) {
            continue;
        }
        if (event->type!=listener->type) {
            continue;
        }
        found = true;
        if ((phase==CAPTURING_PHASE && !(listener->capture)) || (phase==BUBBLING_PHASE && listener->capture)) {
            continue;
        }
        if (listener->once) {
            remove_event_listener(event->currentTarget, listener);
        }
        //! IMPORTANT BEFORE PUBLISH
        //! IMPLEMENT global OBJECT WORK HERE
        //! TEMPORARILY!
        Event* currentEvent = nullptr;
        if (listener->passive) {
            event->in_passive_listener_flag = true;
        }
        //! again global here
        event->in_passive_listener_flag = false;
        if (event->stop_immediate_propagation_flag) {
            break;
        }
    }
    return found;
}


void invoke_event(path_structs &struc, Event* event, enum event_phase phase, std::optional<bool> legacyOutputDidListenersThrowFlag) {
    event->target = nullptr;
    for (const path_structs a: event->path){
        if (a.shadow_adjusted_target){
            event->target = a.shadow_adjusted_target;
        }
    }
    event->relatedTarget = struc.related_target;
    event->touch_target_list = struc.touch_target_list;
    if (event->stop_propagation_flag){ return; }
    event->currentTarget = struc.invocation_target;
    std::vector<event_listener*> listeners (event->currentTarget->event_listener_list);

    bool invocationTargetInShadowTree = struc.invocation_target_in_shadow_tree;
    bool found = inner_invoke(event, listeners, phase, invocationTargetInShadowTree,legacyOutputDidListenersThrowFlag);

    if (!found && event->isTrusted) {
        DOMString originalEventType = event->type;
        if (event->type=="animationend") {
            event->type = "webkitAnimationEnd";
        }
        else if (event->type=="animationiteration") {
            event->type = "webkitAnimationIteration";
        }
        else if (event->type=="animationstart") {
            event->type = "webkitAnimationStart";
        }
        else if (event->type=="transitionend") {
            event->type = "webkitTransitionEnd";
        }
        else{return;}
        inner_invoke(event, listeners, phase, invocationTargetInShadowTree, legacyOutputDidListenersThrowFlag);
        event->type = originalEventType;
    }
}

// Node* create_element(Document* document, DOMString name, std::optional<DOMString> namespaceURI, std::optional<DOMString> prefix, bool gtem, CustomElementRegistry*istry){
//     return dynamic_cast<Node*>(new Element(namespaceURI, prefix, name));
// };

Node* clone_node(Node* node, Document* document, bool subtree, Node* parent, CustomElementRegistry* fallbackRegistry){
    if (document==nullptr){
        document = node->ownerDocument;
    }
    // assert(!dynamic_cast<Document*>(node) || (dynamic_cast<Document*>(node)==document));
    Node* copy = clone_a_single_node(node, document, fallbackRegistry);
    if (parent != nullptr){
        pre_insert_node(copy, parent, nullptr);
    }
    if (subtree){
        for (auto child: node->childNodes.node_list){
            clone_node(child, document, subtree, copy, fallbackRegistry);
        }
    }
    // Element* temp = dynamic_cast<Element*>(node);
    // if (temp && temp->shadow_root!=nullptr && temp->shadow_root->clonable){
    //     Element* temp2 = dynamic_cast<Element*>(copy);
    //     assert(temp2->shadow_root==nullptr);
    //     CustomElementRegistry* shadowRootRegistry = temp->shadow_root->custom_element_registry;
    //     attach_shadow_root(temp2, temp->shadow_root->mode, true, temp->shadow_root->serializable, temp->shadow_root->delegatesFocus, temp->shadow_root->slotAssignment, shadowRootRegistry);
    //     temp2->shadow_root->declarative = temp->shadow_root->declarative;
    //     for (auto child: temp->shadow_root->childNodes){
    //         clone_node(child, document, subtree, temp2->shadow_root);
    //     }
    // }
    return copy;
}


Node* clone_a_single_node(Node* node, Document* document, CustomElementRegistry* fallbackRegistry){
    Node* copy = nullptr;
    // Element* temp = dynamic_cast<Element*>(node);
    Element* temp = nullptr;
    if (temp){
        // CustomElementRegistry* registry = temp->customElementRegistry;
        // if (!registry){ registry = fallbackRegistry; }
        // copy = create_element(document, temp->localName, temp->namespaceURI, temp->prefix, false, registry);
        // for (auto attr: temp->attributes.attribute_list){
        //     Node* copyAttribute = clone_a_single_node(attr, document, nullptr);
        //     append_attribute_to_element(copyAttribute, dynamic_cast<Element*>(copy));
        // }
    }
    else{
        // Document* temp = dynamic_cast<Document*>(node);
        // if (temp){
        //     Document* temp2 = new Document();
        //     temp2->encoding = temp->encoding;
        //     temp2->contentType = temp->contentType;
        //     temp2->URL = temp->URL;
        //     temp2->origin = temp->origin;
        //     temp2->type = temp->type;
        //     temp2->mode = temp->mode;
        //     temp2->allow_declarative_shodow_roots = temp->allow_declarative_shodow_roots;
        //     // step for custom element registry is scoped
        //     temp2->custom_element_registry = temp->custom_element_registry;
        //     copy = dynamic_cast<Node*>(temp2);
        // }
        // else{
        //     DocumentType* temp = dynamic_cast<DocumentType*>(node);
        //     if (temp){
        //         DocumentType* temp2 = new DocumentType();
        //         temp2->name = temp->name;
        //         temp2->publicId = temp->publicId;
        //         temp2->systemId = temp->systemId;
        //         copy = dynamic_cast<Node*>(temp2);
        //     }
        //     else{
        //         Attr* temp = dynamic_cast<Attr*>(node);
        //         if (temp){
        //             Attr* temp2 = new Attr("something");
        //             temp2->namespaceURI = temp->namespaceURI;
        //             temp2->prefix = temp->prefix;
        //             temp2->localName = temp->localName;
        //             temp2->value = temp->value;
        //             copy = dynamic_cast<Node*>(temp2);
        //         }
        //         else{
        //             Text* temp = dynamic_cast<Text*>(node);
        //             if (temp){}
        //             else{
        //                 Comment* temp = dynamic_cast<Comment*>(node);
        //                 if (temp){
        //                     Comment* temp2 = new Comment();
        //                     temp2->data = temp->data;
        //                     copy = dynamic_cast<Node*>(temp2);
        //                 }
        //                 else{
        //                     ProcessingInstruction* temp = dynamic_cast<ProcessingInstruction*>(node);
        //                     if (temp){
        //                         ProcessingInstruction* temp2 = new ProcessingInstruction();
        //                         temp2->target = temp->target;
        //                         temp2->data = temp->data;
        //                     }
        //                 }
        //             }
        //         }
        //     }
        // }
    }
    assert(dynamic_cast<Node*>(copy));
    // if (dynamic_cast<Document*>(node)){ document = dynamic_cast<Document*>(copy); }
    copy->ownerDocument = document;
    return copy;
}

bool nodequals(Node* first, Node* second){
    if (typeid(first) != typeid(second)){
        return false;
    }
    Document* temp = nullptr;
    if (temp){
        // DocumentType* temp2 = dynamic_cast<DocumentType*>(second);
        // if (temp->getname()!=temp2->getname() || temp->getpublicId()!=temp2->getpublicId() || temp->getsystemId()!=temp2->getsystemId()){
        //     return false;
        // }
    }
    else{
        // Element* temp = dynamic_cast<Element*>(first);
        // if (temp){
        //     Element* temp2 = dynamic_cast<Element*>(second);
        //     if (temp->namespaceURI!=temp2->namespaceURI || temp->prefix!=temp2->prefix || temp->localName!=temp2->localName){
        //         return false;
        //     }
        // }
        // else{
        //     Attr* temp = dynamic_cast<Attr*>(first);
        //     if (temp){
        //         Attr* temp2 = dynamic_cast<Attr*>(second);
        //         if (temp->namespaceURI!=temp2->namespaceURI || temp->localName!=temp2->localName || temp->value!=temp2->value){
        //             return false;
        //         }
        //     }
        //     else{
        //         ProcessingInstruction* temp = dynamic_cast<ProcessingInstruction*>(first);
        //         if (temp){
        //             ProcessingInstruction* temp2 = dynamic_cast<ProcessingInstruction*>(second);
        //             if (temp->target!=temp2->target || temp->data!=temp2->data){
        //                 return false;
        //             }
        //         }
        //         else{
        //             Comment* temp = dynamic_cast<Comment*>(first);
        //             if (temp){
        //                 Comment* temp2 = dynamic_cast<Comment*>(second);
        //                 if (temp->data!=temp2->data){
        //                     return false;
        //                 }
        //             }
        //         }
        //     }
        // }
    }
    // Element* temp = dynamic_cast<Element*>(first);
    // if (temp){
    //     Element* temp2 = dynamic_cast<Element*>(second);
    //     int i = 0;
    //     for (auto attribute: temp->attributes.attribute_list){
    //         if (attribute != temp2->attributes.attribute_list.at(i)){
    //             return false;
    //         }
    //         i++;
    //     }
    // }
    if (first->childNodes.length() != second->childNodes.length()){
        return false;
    }
    int i = 0;
    for (auto a: first->childNodes.node_list){
        if (!nodequals(a, second->childNodes[i])){
            return false;
        }
        i++;
    }
    return true;
}

void string_replace_all(std::string &str, Node* parent){
    // Node* node = nullptr;
    // if (str!=""){
    //     node = new Text(str);
    //     node->ownerDocument = parent->ownerDocument;
    // }
    // replace_all(node, parent);
}


std::optional<DOMString> locate_a_namespace(Node* node, std::optional<DOMString> prefix){
    Element* temp = nullptr;
    if (temp){
        // if (prefix=="xml"){
        //     return"http://www.w3.org/XML/1998/namespace";
        // }
        // if (prefix=="xmlns"){
        //     return "http://www.w3.org/2000/xmlns/";
        // }
        // if (temp->namespaceURI.has_value() && temp->prefix==prefix){
        //     return temp->namespaceURI;
        // }
        // for (auto attr: temp->attributes.attribute_list){
        //     if ((attr->namespaceURI=="http://www.w3.org/2000/xmlns/" && attr->prefix=="xmlns" && attr->localName==prefix) || (!prefix.has_value() && attr->namespaceURI=="http://www.w3.org/2000/xmlns/" && !attr->prefix.has_value() && attr->localName=="xmlns")){
        //         if (atr->value==""){ return std::nullopt; }
        //         return attr->value;
        //     }
        // }
        // if (temp->parentElement==nullptr){ return std::nullopt; }
        // return locate_a_namespace(temp->parentElement, prefix);
    }
    else{
        Document* temp = nullptr;
        if (temp){
            // if (temp->documentElement()){ return locate_a_namespace(temp->documentElement(), prefix); }
            // return std::nullopt;
        }
        // else{
        //     DocumentType* temp = dynamic_cast<DocumentType*>(node);
        //     if (temp){}
        //     else{
        //         DocumentFragment* temp = dynamic_cast<DocumentFragment*>(node);
        //         if (temp){
        //             return std::nullopt;
        //         }
        //         else{
        //             Attr* temp = dynamic_cast<Attr*>(node);
        //             if (temp){
        //                 if (temp->ownerElement==nullptr){ return nullptr; }
        //                 return locate_a_namespace(temp->ownerElement, prefix);
        //             }
        //             else{
        //                 if (node->parentElement==nullptr){ return std::nullopt; }
        //                 return locate_a_namespace(node->parentElement, prefix);
        //             }
        //         }
        //     }
        // }
    }
    return std::nullopt;
}

std::optional<DOMString> locate_a_namespace_prefix(Element* element, std::optional<DOMString> namesp){
    // if (element->namespaceURI==namespace && element->prefix.has_value()){
    //     return element->prefix;
    // }
    // for (auto attr: element->attributes.attribute_list){
    //     // if (attr->prefix=="xmlns" && attr->value==namesp){
    //     //     return attr->localName;
    //     // }
    // }
    // if (element->parentElement!=nullptr){
    //     return locate_a_namespace_prefix(element, namesp);
    // }
    return std::nullopt;
}

// HTMLCollection* list_of_elements(DOMString qualifiedName, Node* root){
//     // if (qualifiedName=="*"){}
//     // if (root->ownerDocument->type!="xml"){}
//     return new HTMLCollection();
// }

// HTMLCollection* list_of_elements(std::optional<DOMString> namesp, DOMString localName, Node* root){
//     // if (namesp==""){ namesp = std::nullopt; }
//     // if (namesp=="*" && localName=="*"){}
//     // if (namesp=="*"){}
//     // if (localName=="*"){}
//     return new HTMLCollection();
// }

// HTMLCollection* list_of_elements(std::vector<DOMString> &classNames, Node* root){
//     // std::vector<DOMString> classes;
//     // for (auto class: classes){
//     //     auto something = ParseOrderedSet(class);
//     // }
//     return new HTMLCollection();
// }

EventTarget* retard(EventTarget* a, EventTarget* b){
    auto temp = dynamic_cast<Node*>(a);
    if (!temp){
        return a;
    }
    if (!dynamic_cast<ShadowRoot*>(temp->getRootNode())){
        return a;
    }
    auto temp2 = dynamic_cast<Node*>(b);
    if (temp2 && (check_shadow_including_descendant(temp->getRootNode(), temp2, true))){
        return a;
    }
    auto temp3 = dynamic_cast<ShadowRoot*>(temp->getRootNode());
    if (temp3){
        a = temp3->host();
    }
    return retard(a,b);
}


int determine_node_length(Node* node){
    // if ((dynamic_cast<DocumentType*>(node)) || (dynamic_cast<Attr*>(node))){
    //     return 0;
    // }
    // if (dynamic_cast<CharacterData*>(node)){
    //     return node->data.length();
    // }
    return node->childNodes.node_list.size();
}

// void update_slot_name(Element* element, DOMString &name,  namespace = nullptr){

// }

Node* convert_nodes_to_node(std::vector<std::variant<Node*, DOMString>> nodes, Document* document) {
    Node* node = nullptr;
    int count = 0;
    for (auto a: nodes){
        if (std::holds_alternative<DOMString>(a)){
            // Text* temp = new Text(std::get<DOMString>(a));
            // temp->nodeDocument = document;
            // std::replace (nodes.begin(), nodes.end(), a, temp);
        }
        count++;
    }
    if (count==1){
        node = std::get<Node*>(nodes.at(0));
    }
    // else{
    //     node = new DocumentFragment();
    //     node->nodeDocument = document;
    //     node->childNodes = nodes;
    // }
    return node;
}


bool check_ancestor(Node* node, Node* target, bool inclusive){
    if (inclusive && node->isSameNode(target)){
        return true;
    }
    if (node==nullptr || target==nullptr){
        return false;
    }
    Node* parent = node->parentNode;
    // while (!dynamic_cast<Document*>(parent) && parent!=nullptr){
    //     if (parent == target){
    //         return true;
    //     }
    //     parent = parent->parentNode;
    // }
    return false;
}

bool check_descendant(Node* node, Node* target, bool inclusive){
    if (node==nullptr || target==nullptr){
        return false;
    }
    if (node->childNodes.length()==0){ return false; }
    if (inclusive && node->isSameNode(target)){
        return true;
    }
    Node* currentNode = node->childNodes[0];
    std::vector<Node*> temp = {currentNode};
    while (currentNode!=nullptr){
        if (currentNode == target){
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

bool check_node_precedes(Document* doc, Node* node, Node* target){
    if (doc==nullptr || node==nullptr || target==nullptr){
        return false;
    }
    // if (doc->childNodes.length()==0){ return false; }
    // Node* currentNode = doc->childNodes[0];
    // std::vector<Node*> temp = {currentNode};
    // while (currentNode!=nullptr){
    //     if (currentNode == target){
    //         return true;
    //     }
    //     if (currentNode == node){
    //         break;
    //     }
    //     if (currentNode->childNodes.length()!=0){
    //         temp.push_back(currentNode);
    //         currentNode = currentNode->firstChild();
    //         continue;
    //     }
    //     currentNode = currentNode->nextSibling();
    //     while (currentNode==nullptr && !temp.empty()){
    //         currentNode = (*(temp.end() -1))->nextSibling();
    //         temp.erase(temp.end()-1);
    //     }
    // }
    return false;
}


bool check_shadow_including_descendant(Node* node, Node* target, bool inclusive){
    if (node==nullptr || target==nullptr){
        return false;
    }
    if (check_descendant(node, target, inclusive)){ return true; }
    // ShadowRoot* temp = dynamic_cast<ShadowRoot*>(target->getRootNode());
    // if (temp){
    //     return check_shadow_including_descendant(node, dynamic_cast<Node*>(temp->host()));
    // }
    return false;
}


bool is_closed_shadow_hidden(Node* A, Node* B){
    // ShadowRoot* temp = dynamic_cast<ShadowRoot*>(A->getRootNode());
    // if (temp){
    //     if (!check_shadow_including_descendant(dynamic_cast<Node*>(temp), B, true)){
    //         if (temp->mode==closed || is_closed_shadow_hidden(dynamic_cast<Node*>(temp->host()), B)){
    //             return true;
    //         }
    //     }
    // }
    return false;
}

Node* retarget(Node* A, Node* B){
    Node* temp;
    while (true){
        temp = A->getRootNode();
        // if (!dynamic_cast<Node*>(A) || !dynamic_cast<ShadowRoot*>(temp) || (dynamic_cast<Node*>(B) && check_shadow_including_descendant(B, temp))){
        //     return A;
        // }
        // A = dynamic_cast<Node*>(dynamic_cast<ShadowRoot*>(temp)->host());
        return temp;
    }
}


bool host_including_inclusive_ancestor(Node* A, Node* B){
    if (check_ancestor(B, A, true)){
        return true;
    }
    // auto temp = dynamic_cast<ShadowRoot*>(B);
    // if (temp && temp->getRootNode()->host() && host_including_inclusive_ancestor(A, B->getRootNode()->host())){}
    return false;
}


void ensure_pre_insert_validity(Node* node, Node* parent, Node* child){
    // if (!(dynamic_cast<Document*>(parent)) && !(dynamic_cast<DocumentFragment*>(parent)) && !(dynamic_cast<Element*>(parent))){
    //     throw HeirarchyRequestError("Shit boi !");
    // }

    if (host_including_inclusive_ancestor(node, parent)){
        throw HeirarchyRequestError("Shit boi !");
    }

    if (child && child->parentNode != parent){
        throw NotFoundError("Not found fudge !");
    }
    // if (!(dynamic_cast<DocumentFragment*>(node)) && !(dynamic_cast<DocumentType*>(node)) && !(dynamic_cast<Element*>(node)) && !(dynamic_cast<CharacterData*>(node))){
    //     throw HeirarchyRequestError("Shit boi !");
    // }
    // if ((dynamic_cast<Text*>(node) && dynamic_cast<Document*>(parent)) || (dynamic_cast<DocumentType*>(node) && !(dynamic_cast<Document*>(parent)))){
    //     throw HeirarchyRequestError("Shit boi !");
    // }
    // if (true){
    //     bool element_count = 0;
    //     bool doctype_count = 0;
    //     for (auto a: parent->childNodes.node_list){
    //         if (dynamic_cast<Element*>(a)){ element_count++; }
    //         else if (dynamic_cast<DocumentType*>(a)){ doctype_count++; }
    //     }
    //     if (dynamic_cast<DocumentFragment*>(node)){
    //         int count = 0;
    //         bool has = false;
    //         for (auto a: node->childNodes.node_list){
    //             if (dynamic_cast<Element*>(a)){ count++; }
    //             if (dynamic_cast<Text*>(a)){ has = true; }
    //         }
    //         if (count>1 || has){
    //             throw HeirarchyRequestError("Shit boi !");
    //         }
    //         if (count==1){
    //             if (element_count>0 && dynamic_cast<DocumentType*>(child)){
    //                 throw HeirarchyRequestError("Shit boi !");
    //             }
    //         }
    //     }
    //     else if (dynamic_cast<Element*>(node)){
    //         if (element_count>0 && dynamic_cast<DocumentType*>(child)){
    //             throw HeirarchyRequestError("Shit boi !");
    //         }
    //     }
    //     else if (dynamic_cast<DocumentType*>(node)){
    //         if (doctype_count>0 && child){
    //             throw HeirarchyRequestError("Shit boi !");
    //         }
    //         if (!child && element_count){
    //             throw HeirarchyRequestError("Shit boi !");
    //         }
    //     }
    // }
}




Node* pre_insert_node(Node* node, Node* parent, Node* child){
    ensure_pre_insert_validity(node, parent, child);
    Node* referenceChild = child;
    if (referenceChild == node){
        referenceChild = node->nextSibling();
    }
    insert_node(node, parent, referenceChild);
    return node;
}

void insert_node(Node* node, Node* parent, Node* child, bool suppress_observers){
    NodeList* nodes;
    // if (dynamic_cast<DocumentFragment*>(node)){
    //     nodes = &node->childNodes;
    // }
    // else{
    //     nodes = new NodeList();
    //     nodes->node_list.push_back(node);
    // }
    int count = nodes->length();
    if (count==0){ return; }
    // if (dynamic_cast<DocumentFragment*>(node)){
    //     // remove_node(node);
    //     queue_tree_mutation_record(node, new NodeList(), nodes, nullptr, nullptr);
    // }
    if (child){
        //TODO
    }
    Node* previousSibling;
    if (child){
        previousSibling = child->previousSibling();
    }
    else{
        previousSibling = parent->lastChild();
    }
    for (auto tempnode: nodes->node_list){
        // adopt(tempnode, parent->ownerDocument);
        if (!child){
            parent->childNodes.append(tempnode);
        }
        else{
            auto gg = std::find(parent->childNodes.node_list.begin(), parent->childNodes.node_list.end(), child);
            if (gg!=parent->childNodes.node_list.end()){
                // parent->childNodes.node_list.insert(parent->childNodes.node_list.begin()+index, node);
            }
        }
        // auto bro = dynamic_cast<Element*>(parent);
        // if (bro->shadow_root && bro->shadow_root->slotAssignment==named && (dynamic_cast<Element*>(node) || dynamic_cast<Node*>(node))){
        //     assign_slot(node);
        // }
        // assign_slottables_for_tree(node->getRootNode());
    }
}


void remove_node(Node* node){}


void before(std::vector<std::variant<Node*, DOMString>> &nodes, Node* obj){
    Node* parent = obj->parentNode;
    if (parent==nullptr){return;}
    Node* viablePreviousSibling = nullptr;
    Node* prev = obj->previousSibling();
    bool found = false;
    while (prev){
        for (auto a: nodes){
            if (std::holds_alternative<Node*>(a)){
                if (std::get<Node*>(a)->isEqualNode(prev)){
                    found = true;
                    break;
                }
            }
        }
        if (!found){
            viablePreviousSibling = prev;
            break;
        }
        prev = prev->previousSibling();
        found = false;
    }
    DOMString kk = "";
    Node* node = new Node(ELEMENT_NODE, kk);
    if (viablePreviousSibling==nullptr){
        viablePreviousSibling = parent->firstChild();
    }
    else{
        viablePreviousSibling = viablePreviousSibling->nextSibling();
    }
    pre_insert_node(node, parent, viablePreviousSibling);
}


void after(std::vector<std::variant<Node*, DOMString>>& nodes, Node* obj){
    Node* parent = obj->parentNode;
    if (parent==nullptr){return;}
    Node* viableNextSibling = nullptr;
    Node* next = obj->nextSibling();
    bool found = false;
    while (next){
        for (auto a: nodes){
            if (std::holds_alternative<Node*>(a)){
                if (std::get<Node*>(a)->isEqualNode(next)){
                    found = true;
                    break;
                }
            }
        }
        if (!found){
            viableNextSibling = next;
            break;
        }
        next = next->nextSibling();
        found = false;
    }
    DOMString kk = "";
    Node* node = new Node(ELEMENT_NODE, kk);
    pre_insert_node(node, parent, viableNextSibling);
}

void replaceWith(std::vector<std::variant<Node*, DOMString>> &nodes, Node* obj){
    Node* parent = obj->parentNode;
    if (parent==nullptr){return;}
    Node* viableNextSibling = nullptr;
    Node* next = obj->nextSibling();
    bool found = false;
    while (next){
        for (auto a: nodes){
            if (std::holds_alternative<Node*>(a)){
                if (std::get<Node*>(a)->isEqualNode(next)){
                    found = true;
                    break;
                }
            }
        }
        if (!found){
            viableNextSibling = next;
            break;
        }
        next = next->nextSibling();
        found = false;
    }
    // Node* node = convert_nodes_to_node(nodes, obj->ownerDocument);
    DOMString ff = "";
    Node* node = new Node(ELEMENT_NODE,ff);
    if (*obj->parentNode==*parent){
        replace(obj, node, parent);
    }
    else{
        pre_insert_node(node, parent, viableNextSibling);
    }
}

void remove(Node* obj){
    if (obj->parentNode==nullptr){return;}
    remove_node(obj);
}

Node* pre_remove_node(Node* child, Node* parent){
    return new Node(ELEMENT_NODE, "");
}
Node* replace_node(Node* node, Node* child, Node* parent){
    return new Node(ELEMENT_NODE, "");
}










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


// Node
Node::Node(node_type nodeType, DOMString nodeName, Document* ownerDocument, Node* parentNode){
    this->nodeType = nodeType;
    this->nodeName = nodeName;
    this->ownerDocument = ownerDocument;
    this->parentNode = parentNode;
    if (dynamic_cast<Element*>(parentNode)){
        this->parentElement = dynamic_cast<Element*>(parentNode);
    }
}

bool inline Node::isConnected(){
    if (dynamic_cast<Document*>(this->getRootNode(true))){
        return true;
    }
    return false;
}

Node* Node::getRootNode(bool composed){
    if (composed){
        auto temp = dynamic_cast<ShadowRoot*>(this);
        if (temp){
            return temp->host()->getRootNode(composed);
        }
    }
    if (this->parentNode){
        return this->parentNode->getRootNode(composed);
    }
    return this;
}

inline bool Node::hasChildNodes() const{
    if (this->childNodes.length()==0){ return false; }
    return true;
}

inline Node* Node::firstChild(){
    return this->childNodes[0];
}
inline Node* Node::lastChild(){
    return this->childNodes.node_list.back();
}
Node* Node::previousSibling() {
    if (this->parentNode) {
        auto& vect = this->parentNode->childNodes.node_list;
        for (size_t i = 0; i < vect.size(); i++) {
            if (vect[i] == this) {
                if (i == 0) return nullptr; // no previous
                return vect[i - 1];
            }
        }
    }
    return nullptr;
}

Node* Node::nextSibling() {
    if (this->parentNode) {
        auto& vect = this->parentNode->childNodes.node_list;
        for (size_t i = 0; i < vect.size(); i++) {
            if (vect[i] == this) {
                if (i + 1 >= vect.size()) return nullptr; // no next
                return vect[i + 1];
            }
        }
    }
    return nullptr;
}

Node* Node::get_the_parent(Event* event){
    Element* temp = dynamic_cast<Element*>(this);
    if (temp){
        if (temp->assignedSlot!=nullptr){
            return temp->assignedSlot;
        }
    }
    Text* temp2 = dynamic_cast<Text*>(this);
    if (temp2){
        if (temp2->assignedSlot!=nullptr){
            return temp2->assignedSlot;
        }
    }
    return this->parentNode;
}

Node* Node::cloneNode(bool subtree){
    // node is self, document is nodeDocument, subtree is arg, parent is null, fallbackRegistry is null
    return clone_node(this,nullptr, subtree);
    //TODO
}

bool Node::isEqualNode(Node* otherNode){
    if (otherNode==nullptr){ return false; }
    if (nodequals(this, otherNode)){
        return true;
    }
    return false;
}

bool Node::isSameNode(Node* otherNode){
    if (otherNode==this){
        return true;
    }
    return false;
}

unsigned short Node::compareDocumentPosition(Node* other){
    if (this->isSameNode(other)){
        return 0;
    }
    Node* node1 = other;
    Node* node2 = this;
    Attr* attr1 = nullptr;
    Attr* attr2 = nullptr;
    Attr* temp = dynamic_cast<Attr*>(node1);
    Element* temp2;
    if (temp){
        attr1 = temp;
        node1 = dynamic_cast<Node*>(attr1->ownerElement);
        temp2 = dynamic_cast<Element*>(attr1->ownerElement);
    }
    temp = dynamic_cast<Attr*>(node2);
    if (temp){
        attr2 = temp;
        node2 = dynamic_cast<Node*>(attr2->ownerElement);
        temp2 = dynamic_cast<Element*>(attr2->ownerElement);
        if (attr2!=nullptr && node1!=nullptr && node2==node1){
            for (Attr* attr: temp2->attributes.attribute_list){
                if (nodequals(attr, attr1)){
                    return DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC + DOCUMENT_POSITION_PRECEDING;
                }
                if (nodequals(attr, attr2)){
                    return DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC + DOCUMENT_POSITION_FOLLOWING;
                }
            }
        }
    }
    if (node1==nullptr || node2==nullptr || node1->getRootNode()!=node2->getRootNode()){
        return DOCUMENT_POSITION_DISCONNECTED + DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC + DOCUMENT_POSITION_PRECEDING;
    }
    if ((check_ancestor(dynamic_cast<Node*>(node2->ownerDocument), node2, node1) && attr1==nullptr) || (node1==node2 && attr2!=nullptr)){
        return DOCUMENT_POSITION_CONTAINS + DOCUMENT_POSITION_PRECEDING;
    }
    if ((check_descendant(node2, node1) && attr2==nullptr) || (node1==node2 && attr1!=nullptr)){
        return DOCUMENT_POSITION_CONTAINED_BY + DOCUMENT_POSITION_FOLLOWING;
    }
    if (check_node_precedes(node2->ownerDocument, node2, node1)){
        return DOCUMENT_POSITION_PRECEDING;
    }
    return DOCUMENT_POSITION_FOLLOWING;
}

bool Node::contains(Node* other){
    if (other==nullptr){return false;}
    return check_descendant(this, other, true);
}

std::optional<DOMString> Node::lookupPrefix(std::optional<DOMString> &namesp){
    if (namesp==std::nullopt || namesp==""){ return std::nullopt; }
    if (this->parentElement==nullptr){ return std::nullopt; }
    return locate_a_namespace_prefix(this->parentElement, namesp);
}

std::optional<DOMString> Node::lookupNamespaceURI(std::optional<DOMString> &prefix){
    if (prefix==""){ prefix=std::nullopt; }
    return locate_a_namespace(this, prefix);
}

bool Node::isDefaultNamespace(std::optional<DOMString> &namesp){
    if (namesp==""){ namesp=std::nullopt; }
    std::optional<DOMString> defaultNamespace = locate_a_namespace(this, std::nullopt);
    if (defaultNamespace==namesp){ return true; }
    return false;
}

Node* Node::insertBefore(Node* node, Node* child){
    return pre_insert_node(node, this, child);
}

Node* Node::appendChild(Node* node){
    return pre_insert_node(node, this, nullptr);
}

Node* Node::replaceChild(Node* node, Node* child){
    return replace_node(node, this, child);
}

Node* Node::removeChild(Node* child){
    return pre_remove_node(child, this);
}


void Node::normalize(){
    if (this->childNodes.length()==0){ return; }
    Node* currentNode = this->childNodes[0];
    std::vector<Node*> temp = {currentNode};
    while (currentNode!=nullptr){
        if (dynamic_cast<Text*>(currentNode) && !dynamic_cast<CDATASection*>(currentNode)){
            unsigned long length = this->length();
            if (length==0){
                remove_node(currentNode);
            }
            else{
                
            }
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
}

Element* HTMLCollection::item(const unsigned long &index) const{
    try {
        return element_list.at(index);
    }
    catch (const std::out_of_range&) {
        return nullptr;
    }
}

Element* HTMLCollection::namedItem(const DOMString &name) const{
    if (name=="") {
        return nullptr;
    }
    for (auto element: element_list) {
        //! CHECK IF `element` IS IN THE HTML NAMESPACE
        //! CHECK IF `element` HAS A NAME ATTRIBUTE WHOSE VALUE IS name
        if (element->id==name) {
            return element;
        }
    }
    return nullptr;
}

unsigned long HTMLCollection::length() const{
    return element_list.size();
}

HTMLCollection::~HTMLCollection(){
    for (auto a: element_list) {
        delete a;
    }
    element_list.clear();
}



void ParentNode::prepend(std::vector<std::variant<Node*, DOMString>> &nodes) {
    DOMString kk = "";
    Node* temp = new Node(ELEMENT_NODE, kk);
    // Node* temp = convert_nodes_to_node(nodes, this->ownerDocument);
    auto smth = dynamic_cast<Node*>(this);
    pre_insert_node(temp, dynamic_cast<Node*>(this), smth->firstChild());
}

void ParentNode::append(std::vector<std::variant<Node*, DOMString>> &nodes){
    DOMString kk = "";
    Node* temp = new Node(ELEMENT_NODE, kk);
    // Node* temp = convert_nodes_to_node(nodes, this->ownerDocument);
    pre_insert_node(temp, dynamic_cast<Node*>(this), nullptr);
}

void ParentNode::replaceChildren(std::vector<std::variant<Node*, DOMString>> &nodes){
    DOMString kk = "";
    Node* temp = new Node(ELEMENT_NODE, kk);
    // Node* temp = convert_nodes_to_node(nodes, this->ownerDocument);
    ensure_pre_insert_validity(temp, dynamic_cast<Node*>(this), nullptr);
    replace_all(temp, dynamic_cast<Node*>(this));
}

void ParentNode::moveBefore(Node* node, Node* child){
    Node* referenceChild = child;
    if (*referenceChild == *node){
        referenceChild = node->nextSibling();
    }
    move_node(node, dynamic_cast<Node*>(this), referenceChild);
}






Element* Element::previousElementSibling(){
    auto smth = dynamic_cast<Node*>(this);
    Node* prev = smth->previousSibling();
    while (prev){
        auto bro = dynamic_cast<Element*>(prev);
        if (bro){
            return bro;
        }
        prev = prev->previousSibling();
    }
    return nullptr;
}

Element* Element::nextElementSibling(){
    auto smth = dynamic_cast<Node*>(this);
    Node* next = smth->nextSibling();
    while (next){
        auto bro = dynamic_cast<Element*>(next);
        if (bro){
            return bro;
        }
        next = next->nextSibling();
    }
    return nullptr;
}

Element* CharacterData::previousElementSibling(){
    auto smth = dynamic_cast<Node*>(this);
    Node* prev = smth->previousSibling();
    while (prev){
        if (dynamic_cast<Element*>(prev)){
            return dynamic_cast<Element*>(prev);
        }
        prev = prev->previousSibling();
    }
    return nullptr;
}

Element* CharacterData::nextElementSibling(){
    auto smth = dynamic_cast<Node*>(this);
    Node* next = smth->nextSibling();
    while (next){
        if (dynamic_cast<Element*>(next)){
            return dynamic_cast<Element*>(next);
        }
        next = next->nextSibling();
    }
    return nullptr;
}





DOMString* Document::lookupPrefix(std::optional<DOMString> namesp){
    if (namesp==std::nullopt || namesp.value()==""){ return nullptr; }
    if (this->documentElement()==nullptr){ return nullptr; }
    // return locate_a_namespace_prefix(this->documentElement() , namesp);
    DOMString k = "";
    return nullptr;
}


DOMString Document::compatMode(){
    if (this->mode==QUIRKS){
        return "BackCompat";
    }
    return "CSS1Compat";
}

DocumentType* Document::doctype(){
    for (size_t i=0;  i<this->childNodes.length(); i++){
        DocumentType* temp = dynamic_cast<DocumentType*>(this->childNodes[i]);
        if (temp){
            return temp;
        }
    }
    return nullptr;
}

Element* Document::documentElement(){
    for (size_t i=0;  i<this->childNodes.length(); i++){
        Element* temp = dynamic_cast<Element*>(this->childNodes[i]);
        if (temp){
            return temp;
        }
    }
    return nullptr;
}



HTMLCollection* Document::getElementsByTagName(DOMString qualifiedName){
    // return list_of_elements(qualifiedName, dynamic_cast<Node*>(this));
    return new HTMLCollection();
}

HTMLCollection* Document::getElementsByTagNameNS(std::optional<DOMString> namesp, DOMString localname){
    // return list_of_elements(namesp, localname, dynamic_cast<Node*>(this));
    return new HTMLCollection();
}

HTMLCollection* Document::getElementsByClassName(std::vector<DOMString> &classNames){
    // return list_of_elements(classNames, dynamic_cast<Node*>(this));
    return new HTMLCollection();
}

Element* Document::createElement(DOMString localName, std::variant<DOMString,ElementCreationOptions> options){
    if (!valid_element_local_name(localName)){ throw InvalidCharacterError("Character Name invalid !!"); }
    if (this->type!=XML){
        std::transform(localName.begin(), localName.end(), localName.begin(), [](unsigned char c){ return std::tolower(c); });
    }
    CustomElementRegistry* registry;
    std::optional<DOMString> is;
    std::optional<DOMString> namesp;
    flatten_element_creation_options(options, this, registry, is);
    if (this->type!=XML || this->contentType=="application/xhtml+xml"){
        namesp = "http://www.w3.org/1999/xhtml";
    }
    else{
        namesp = std::nullopt;
    }
    // return create_element(this, localName, namesp, std::nullopt, is, true, registry);
    return new Element("","","");
}

Element* Document::createElementNS(std::optional<DOMString> namesp, DOMString qualifiedName, std::variant<DOMString,ElementCreationOptions> options){
    return internal_create_element_ns(this, namesp, qualifiedName, options);
}

DocumentFragment* Document::createDocumentFragment(){
    DocumentFragment* temp = new DocumentFragment();
    // temp->ownerDocument = this;
    return temp;
}

Text* Document::createTextNode(DOMString data){
    Text* temp = new Text(data);
    // temp->ownerDocument = this;
    return temp;
}

CDATASection* Document::createCDATASection(DOMString data){
    if (this->type!=XML){ throw NotSupportedError("Html Doc ain't supported !"); }
    if (data.find("]]>") != std::string::npos) { throw InvalidCharacterError("Invalid Characters !"); }
    CDATASection* temp = new CDATASection();
    temp->setdata(data);
    // temp->ownerDocument = this;
    return temp;
}

Comment* Document::createComment(DOMString data){
    Comment* temp = new Comment(data);
    // temp->ownerDocument = this;
    return temp;
}

ProcessingInstruction* Document::createProcessingInstruction(DOMString target, DOMString data){
    // If target doesn't match some Name production, throw InvalidCharacterError exception
    if (data.find("?>") != std::string::npos){ throw InvalidCharacterError("Invalid Characters !"); }
    ProcessingInstruction* temp = new ProcessingInstruction();
    temp->target = target;
    temp->setdata(data);
    // temp->ownerDocument = this;
    return temp;
}

Node* Document::importNode(Node* node, std::variant<bool,ImportNodeOptions> options){
    if (dynamic_cast<Document*>(node) || dynamic_cast<ShadowRoot*>(node)){ throw NotSupportedError("Document and Shadow Root not supported !!"); }
    bool subtree = false;
    CustomElementRegistry* registry = nullptr;
    if (std::holds_alternative<bool>(options)){ subtree = std::get<bool>(options); }
    else{
        ImportNodeOptions temp = std::get<ImportNodeOptions>(options);
        subtree = !temp.selfOnly;
        if (temp.customElementRegistry!=nullptr){ registry = temp.customElementRegistry; }
        if (registry && registry!=this->custom_element_registry){ throw NotSupportedError("NOT SUPPORTED :) !"); }
    }
    return clone_node(node, this, subtree, nullptr, registry);
}

Node* Document::adoptNode(Node* node){
    if (dynamic_cast<Document*>(node)){ throw NotSupportedError("Document ain't supported !"); }
    if (dynamic_cast<ShadowRoot*>(node)){ throw HeirarchyRequestError("IDK WHY THIS !!"); }
    DocumentFragment* temp = dynamic_cast<DocumentFragment*>(node);
    if (temp && temp->associatedHost!=nullptr){
        return nullptr;
    }
    adopt(node, this);
    return node;
}

Attr* Document::createAttribute(DOMString localName){
    if (!valid_attribute_local_name(localName)){ throw InvalidCharacterError("Invalid Attribute Name"); }
    if (this->type!=XML){
        std::transform(localName.begin(), localName.end(), localName.begin(), [](unsigned char c){ return std::tolower(c); });
    }
    Attr* temp = new Attr(localName);
    // temp->ownerDocument = this;
    return temp;
}

Attr* Document::createAttributeNS(std::optional<DOMString> namesp, DOMString qualifiedName){
    std::optional<DOMString> prefix;
    DOMString localName;
    validate_and_extract(namesp, qualifiedName, "attribute",prefix, localName);
    Attr* temp = new Attr(localName);
    temp->namespaceURI = namesp;
    temp->prefix = prefix;
    // temp->ownerDocument = this;
    return temp;
}

Event* Document::createEvent(DOMString interface){
    Event* constructor = nullptr;
    if (constructor==nullptr){
        throw NotSupportedError("Not supported :)) !!");
    }
	return constructor;
}

Range* createRange(){
    Range* temp = new Range();
    return temp;
}

NodeIterator* createNodeIterator(Node* root, unsigned long whatToShow, NodeFilter* filter){
    NodeIterator* iterator = new NodeIterator();
    return iterator;
}

TreeWalker* createTreeWalker(Node* root, unsigned long whatToShow, NodeFilter* filter){
    TreeWalker* walker = new TreeWalker();
    return walker;
}



DocumentType* DOMImplementation::createDocumentType(DOMString name, DOMString publicId, DOMString systemId){
    if (!valid_doctype_name(name)){ throw InvalidCharacterError("Invalid Chars !!"); }
    DocumentType* temp = new DocumentType(name, publicId, systemId);
    // temp->ownerDocument = this->associated_doc;
    return temp;
}

XMLDocument* DOMImplementation::createDocument(std::optional<DOMString> namesp, DOMString qualifiedName, std::optional<DocumentType> doctype){
    XMLDocument* document = new XMLDocument();
    Element* element = nullptr;
    if (qualifiedName!=""){
        element = internal_create_element_ns(dynamic_cast<Document*>(document), namesp, qualifiedName, ElementCreationOptions());
    }
    if (doctype.has_value()){ pre_insert_node(dynamic_cast<Node*>(document), dynamic_cast<Node*>(&doctype.value()), nullptr); }
    if (element!=nullptr){ pre_insert_node(dynamic_cast<Node*>(document), dynamic_cast<Node*>(element), nullptr); }
    document->origin=this->associated_doc->origin;
    if (namesp.value()=="http://www.w3.org/1999/xhtml"){
        document->contentType = "application/xhtml+xml";
    }
    else if (namesp.value()=="http://www.w3.org/2000/svg"){
        document->contentType = "image/svg+xml";
    }
    else{
        document->contentType = "application/xml";
    }
    return document;
}

Document* DOMImplementation::createHTMLDocument(std::optional<DOMString> title){
    Document* document = new Document();
    document->type = HTML;
    document->contentType = "text/html";
    DocumentType* doct = new DocumentType("html");
    // doct->ownerDocument = document;
    pre_insert_node(dynamic_cast<Node*>(document), dynamic_cast<Node*>(doct), nullptr);
    Element* htmlElement = create_element(document, "html", "http://www.w3.org/1999/xhtml", std::nullopt);
    pre_insert_node(dynamic_cast<Node*>(document), dynamic_cast<Node*>(htmlElement), nullptr);
    Element* headElement = create_element(document, "head", "http://www.w3.org/1999/xhtml", std::nullopt);
    pre_insert_node(dynamic_cast<Node*>(htmlElement), dynamic_cast<Node*>(headElement), nullptr);
    if (title!=std::nullopt){
        Element* titleElement = create_element(document, "title", "http://www.w3.org/1999/xhtml", std::nullopt);
        pre_insert_node(dynamic_cast<Node*>(headElement), dynamic_cast<Node*>(titleElement), nullptr);
        Text* text = new Text(title.value());
        // text->ownerDocument = document;
        pre_insert_node(dynamic_cast<Node*>(titleElement), dynamic_cast<Node*>(text), nullptr);
    }
    pre_insert_node(dynamic_cast<Node*>(htmlElement), dynamic_cast<Node*>(create_element(document, "body", "http://www.w3.org/1999/xhtml")), nullptr);
    document->origin = this->associated_doc->origin;
    return document;
}



bool DOMImplementation::hasFeature(){ return true; }




bool Element::hasAttributes(){
    if (this->attributes.attribute_list.size()==0){
        return false;
    }
    return true;
}

std::vector<DOMString> Element::getAttributeNames(){
    std::vector<DOMString> attribute_qualified_names = {};
    for (auto a: this->attributes.attribute_list){
        if (a->prefix==std::nullopt){
            attribute_qualified_names.push_back(a->localName);
        }
        else{
            attribute_qualified_names.push_back(a->prefix.value() + ":" + a->localName);
        }
    }
    return attribute_qualified_names;
}


std::optional<DOMString> Element::getAttribute(DOMString qualifiedName){
    Attr* attr = fetch_attribute(qualifiedName, this);
    if (attr==nullptr){ return std::nullopt; }
    return attr->value;
}

std::optional<DOMString> Element::getAttributeNS(std::optional<DOMString> namesp, DOMString localName){
    Attr* attr = fetch_attribute(namesp, localName, this);
    if (attr==nullptr){ return std::nullopt; }
    return attr->value;
}


void Element::setAttribute(DOMString qualifiedName, DOMString value){
    if (!valid_attribute_local_name(qualifiedName)){ throw InvalidCharacterError("Invalid name for attribute !!"); }
    //later !
    // if (this->ownerDocument->type!=XML){
    //     std::transform(qualifiedName.begin(), qualifiedName.end(), qualifiedName.begin(), [](unsigned char c){ return std::tolower(c); });
    // }
    Attr* attribute = nullptr;
    for (auto attr: this->attributes.attribute_list){
        DOMString qualif;
        if (attr->prefix == std::nullopt){
            qualif = attr->localName;
        }
        else{
            qualif = attr->prefix.value() + ":" + attr->localName;
        }
        if (qualif==qualifiedName){
            attribute = attr;
            break;
        }
    }
    if (attribute==nullptr){
        Attr* temp = new Attr(qualifiedName);
        temp->value = value;
        // temp->ownerDocument = this->ownerDocument;
        append_attribute(temp, this);
        return;
    }
    change_attribute_value(attribute, value);
}

void Element::setAttributeNS(std::optional<DOMString> namesp, DOMString qualifiedName, DOMString value){
    std::optional<DOMString> prefix;
    DOMString localName;
    validate_and_extract(namesp, qualifiedName, "element", prefix, localName);
    set_attribute_value(this, localName, value, prefix, namesp);
}

void Element::removeAttribute(DOMString qualifiedName){
    remove_attribute_by_name(qualifiedName, this);
}

void Element::removeAttributeNS(std::optional<DOMString> namesp, DOMString localName){
    remove_attribute_by_namespace(namesp, localName, this);
}


bool Element::hasAttribute(DOMString qualifiedName){
    // if (this->ownerDocument->type!=XML){
    //     std::transform(qualifiedName.begin(), qualifiedName.end(), qualifiedName.begin(), [](unsigned char c){ return std::tolower(c); });
    // }
    for (auto attr: this->attributes.attribute_list){
        DOMString qualif;
        if (attr->prefix == std::nullopt){
            qualif = attr->localName;
        }
        else{
            qualif = attr->prefix.value() + ":" + attr->localName;
        }
        if (qualif==qualifiedName){
            return true;
        }
    }
    return false;
}

bool Element::toggleAttribute(DOMString qualifiedName, std::optional<bool> force){
    if (!valid_attribute_local_name(qualifiedName)){ throw InvalidCharacterError("Invalid Attribute Name boi !"); }
    // if (this->ownerDocument->type!=XML){
    //     std::transform(qualifiedName.begin(), qualifiedName.end(), qualifiedName.begin(), [](unsigned char c){ return std::tolower(c); });
    // }
    Attr* attribute = nullptr;
    for (auto attr: this->attributes.attribute_list){
        DOMString qualif;
        if (attr->prefix == std::nullopt){
            qualif = attr->localName;
        }
        else{
            qualif = attr->prefix.value() + ":" + attr->localName;
        }
        if (qualif==qualifiedName){
            attribute = attr;
            break;
        }
    }
    if (attribute==nullptr){
        if (!force.has_value() || (force.has_value() && force.value()==true)){
            Attr* temp = new Attr(qualifiedName);
            temp->value = "";
            // temp->ownerDocument = this->ownerDocument;
            append_attribute(temp, this);
            return true;
        }
        return false;
    }
    if (!force.has_value() || (force.has_value() && force.value()==false)){
        remove_attribute_by_name(qualifiedName, this);
        return false;
    }
    return true;
}

bool Element::hasAttributeNS(std::optional<DOMString> namesp, DOMString localname){
    if (namesp.has_value() && namesp.value()==""){ namesp = std::nullopt; }
    for (auto a: this->attributes.attribute_list){
        if (a->namespaceURI==namesp && a->localName==localName){
            return true;
        }
    }
    return false;
}


Attr* Element::getAttributeNode(DOMString qualifiedName){
    return fetch_attribute(qualifiedName, this);
}

Attr* Element::getAttributeNodeNS(std::optional<DOMString> namesp, DOMString localName){
    return fetch_attribute(namesp, localName, this);
}

Attr* Element::setAttributeNode(Attr* attr){
    return set_attribute(attr, this);
}

Attr* Element::setAttributeNodeNS(Attr* attr){
    return set_attribute(attr, this);
}

Attr* Element::removeAttributeNode(Attr* attr){
    bool found = false;
    for (auto a: this->attributes.attribute_list){
        if (a==attr){ found = true; }
    }
    if (!found){ throw NotFoundError("Attribute Not Found !"); }
    remove_attribute(attr);
    return attr;
}


ShadowRoot* Element::attachShadow(ShadowRootInit init){
    CustomElementRegistry* registry = this->customElementRegistry;
    if (init.customElementRegistry!=nullptr){
        registry = init.customElementRegistry;
        // if (registry!=this->ownerDocument->custom_element_registry){ throw NotSupportedError("This ain't supported !"); }
    }
    attach_shadow_root(this, init.mode, init.clonable, init.serializable, init.delegatesFocus, init.slotAssignment, *registry);
    return this->getshadow_root();
}

Element* Element::insertAdjacentElement(DOMString where, Element element){
    // return dynamic_cast<Element*>(insert_adjacent(this, where, dynamic_cast<Node*>(element)));
    return new Element("","","");
}

void Element::insertAdjacentText(DOMString where, DOMString data){
    // Text* text = new Text(data);
    // text->ownerDocument = this->ownerDocument;
    // insert_adjacent(this, where, dynamic_cast<Node*>(text));
}

HTMLCollection* Element::getElementsByTagName(DOMString qualifiedName){
    // return list_of_elements(qualifiedName, dynamic_cast<Node*>(this));
    return new HTMLCollection();
}

HTMLCollection* Element::getElementsByTagNameNS(std::optional<DOMString> namesp, DOMString localName){
    // return list_of_elements(namesp, localName, dynamic_cast<Node*>(this));
    return new HTMLCollection();
}

HTMLCollection* Element::getElementsByClassName(DOMString classNames){
    // return list_of_elements(classNames, dynamic_cast<Node*>(this));
    return new HTMLCollection();
}



Attr* NamedNodeMap::item(unsigned long index){
    try {
        return attribute_list.at(index);
    }
    catch (const std::out_of_range&) {
        return nullptr;
    }
}


unsigned long NamedNodeMap::length(){
    return attribute_list.size();
}

Attr* NamedNodeMap::getNamedItem(DOMString qualifiedName){
    return fetch_attribute(qualifiedName, this->associatedElement);
}

Attr* NamedNodeMap::getNamedItemNS(std::optional<DOMString> namesp, DOMString localName){
    return fetch_attribute(namesp, localName, this->associatedElement);
}

Attr* NamedNodeMap::setNamedItem(Attr* attr){
    return set_attribute(attr, this->associatedElement);
}

Attr* NamedNodeMap::setNamedItemNS(Attr* attr){
    return set_attribute(attr, this->associatedElement);
}

Attr* NamedNodeMap::removeNamedItem(DOMString qualifiedName){
    Attr* attr = remove_attribute_by_name(qualifiedName, this->associatedElement);
    if (attr==nullptr){ throw NotFoundError("Attribute not found !!"); }
    return attr;
}

Attr* NamedNodeMap::removeNamedItemNS(std::optional<DOMString> namesp, DOMString localName){
    Attr* attr = remove_attribute_by_namespace(namesp, localName, this->associatedElement);
    if (attr==nullptr){ throw NotFoundError("Attribute not found !!"); }
    return attr;
}



Attr::Attr(DOMString localName): Node(ATTRIBUTE_NODE, this->qualifiedName()){
    this->localName = localName;
}

DOMString Attr::qualifiedName(){
    if (this->prefix==std::nullopt){
        return this->localName;
    }
    return this->prefix.value() + ":" + this->localName;
}


unsigned long CharacterData::length(){
    return this->data.length();
}

DOMString CharacterData::substringData(unsigned long offset, unsigned long count){
    return substring_data(dynamic_cast<Node*>(this), offset, count);
}

void CharacterData::appendData(DOMString data){
    replace_data(dynamic_cast<Node*>(this), this->length(), 0, data);
}

void CharacterData::insertData(unsigned long offset, DOMString data){
    replace_data(dynamic_cast<Node*>(this), offset, 0, data);
}

void CharacterData::deleteData(unsigned long offset, unsigned long count){
    replace_data(dynamic_cast<Node*>(this), offset, count, "");
}

void CharacterData::replaceData(unsigned long offset, unsigned long count, DOMString data){
    replace_data(dynamic_cast<Node*>(this), offset, count, data);
}


Text* Text::splitText(unsigned long offset){
    return split_text_node(this, offset);
}

DOMString Text::wholeText(){
    DOMString data = "";
    for (auto a: contiguous_text_nodes(this)){
        data += this->data;
    }
    return data;
}




bool AbstractRange::collapsed(){
    if (this->startContainer==this->endContainer && this->startOffset==this->endOffset){
        return true;
    }
    return false;
}


StaticRange::StaticRange(StaticRangeInit init){
    if (dynamic_cast<DocumentType*>(init.startContainer) || dynamic_cast<Attr*>(init.startContainer) || dynamic_cast<DocumentType*>(init.endContainer) || dynamic_cast<Attr*>(init.endContainer) ){
        throw InvalidNodeTypeError("invalid node type baby !!");
    }
    this->startContainer = init.startContainer;
    this->startOffset = init.startOffset;
    this->endContainer = init.endContainer;
    this->endOffset = init.endOffset;
}

Range::Range(){};

Node* Range::commonAncestorContainer(){
    Node* container = this->startContainer;
    while (!check_ancestor(this->endContainer, container, true)){
        container = container->parentNode;
    }
    return container;
}


void Range::setStart(Node* node, unsigned long offset){
    set_start_end(this, node, offset);
}

void Range::setEnd(Node* node, unsigned long offset){
    set_start_end(this, node, offset, false);
}

void Range::setStartBefore(Node* node){
    Node* parent = node->parentNode;
    if (parent==nullptr){ throw InvalidNodeTypeError("invalid node type dummy !"); }
    set_start_end(this, parent, node->index());
}

void Range::setStartAfter(Node* node){
    Node* parent = node->parentNode;
    if (parent==nullptr){ throw InvalidNodeTypeError("invalid node type dummy !"); }
    set_start_end(this, parent, node->index()+1);
}

void Range::setEndBefore(Node* node){
    Node* parent = node->parentNode;
    if (parent==nullptr){ throw InvalidNodeTypeError("invalid node type dummy !"); }
    set_start_end(this, parent, node->index(), false);
}

void Range::setEndAfter(Node* node){
    Node* parent = node->parentNode;
    if (parent==nullptr){ throw InvalidNodeTypeError("invalid node type dummy !"); }
    set_start_end(this, parent, node->index()+1, false);
}

void Range::collapse(bool toStart){
    if (toStart){
        this->endContainer = this->startContainer;
        this->endOffset = this->startOffset;
    }
    else{
        this->startContainer = this->endContainer;
        this->startOffset = this->endOffset;
    }
}

void Range::selectNode(Node* node){
    select_node_within_rangee(node, this);
}

void Range::selectNodeContents(Node* node){
    if (dynamic_cast<DocumentType*>(node)){ throw InvalidNodeTypeError("invalid node type boi !!!"); }
    unsigned long length = node->length();
    this->startContainer = node;
    this->startOffset = 0;
    this->endContainer = node;
    this->endOffset = length;
}

short Range::compareBoundaryPoints(unsigned short how, Range* sourceRange){
    if (how!=START_TO_START && how!=START_TO_END && how!=END_TO_END && how!=END_TO_START){
        throw NotSupportedError("not supported this start end whatever !");
    }
    if (this->startContainer->getRootNode()!=sourceRange->startContainer->getRootNode()){
        throw WrongDocumentError("wrong document ! read it u sick boi !!");
    }
    Node* thisnode;
    unsigned long thisoffset;
    Node* othernode;
    unsigned long otheroffset;
    if (how==START_TO_START){
        thisnode = this->startContainer;
        thisoffset = this->startOffset;
        othernode = sourceRange->startContainer;
        otheroffset = sourceRange->startOffset;
    }
    else if (how==START_TO_END){
        thisnode = this->endContainer;
        thisoffset = this->endOffset;
        othernode = sourceRange->startContainer;
        otheroffset = sourceRange->startOffset;
    }
    else if (how==END_TO_END){
        thisnode = this->endContainer;
        thisoffset = this->endOffset;
        othernode = sourceRange->endContainer;
        otheroffset = sourceRange->endOffset;
    }
    else if (how==END_TO_START){
        thisnode = this->startContainer;
        thisoffset = this->startOffset;
        othernode = sourceRange->endContainer;
        otheroffset = sourceRange->endOffset;
    }
    return position(thisnode, thisoffset, othernode, otheroffset);
}


void Range::deleteContents(){
    if (this->collapsed()){
        return;
    }
    Node* original_startnode = this->startContainer;
    unsigned long original_startoffset = this->startOffset;
    Node* original_endnode = this->endContainer;
    unsigned long original_endoffset = this->endOffset;
    
    if (original_startnode==original_endnode && dynamic_cast<CharacterData*>(original_startnode)){
        replace_data(original_startnode, original_startoffset, original_endoffset - original_startoffset, "");
        return;
    }
    std::vector<Node*> nodes_to_remove = {};
    Node* new_node;
    unsigned long new_offset;
    if (check_ancestor(original_endnode, original_startnode, true)){
        new_node = original_startnode;
        new_offset = original_startoffset;
    }
    else{
        Node* reference_node = original_startnode;
        while(reference_node->parentNode!=nullptr && !check_ancestor(original_endnode, reference_node, true)){
            reference_node = reference_node->parentNode;
        }
        new_node = reference_node->parentNode;
        new_offset = reference_node->index() + 1;
    }
    if (dynamic_cast<CharacterData*>(original_startnode)){
        replace_data(original_startnode, original_startoffset, original_startnode->length() - original_startoffset, "");
    }
    for (auto node: nodes_to_remove){
        remove_node(node);
    }
    if (dynamic_cast<CharacterData*>(original_endnode)){
        replace_data(original_endnode, 0, original_endoffset, "");
    }
    this->startContainer = new_node;
    this->startOffset = new_offset;
    this->endContainer = new_node;
    this->endOffset = new_offset;
}

DocumentFragment* Range::extraContents(){
    return new DocumentFragment();
}

DocumentFragment* Range::cloneContents(){
    return new DocumentFragment();
}

void Range::insertNode(Node* node){
    insert_node_in_range(node, this);
}

void Range::surroundContents(Node* newParent){
    if (dynamic_cast<Document*>(newParent) || dynamic_cast<DocumentType*>(newParent) || dynamic_cast<DocumentFragment*>(newParent)){
        throw InvalidNodeTypeError("invalid node type baby !!");
    }
    DocumentFragment* fragment = extract_range(this);
    if (newParent->hasChildNodes()){
        replace_all(nullptr, newParent);
    }
    insert_node_in_range(newParent, this);
    pre_insert_node(dynamic_cast<Node*>(fragment), newParent, nullptr);
    select_node_within_rangee(newParent, this);
}


Range* Range::cloneRange(){
    Range* temp = new Range();
    temp->startContainer = this->startContainer;
    temp->startOffset = this->startOffset;
    temp->endContainer = this->endContainer;
    temp->endOffset = this->endOffset;
    return temp;
}

bool Range::isPointInRange(Node* node, unsigned long offset){
    if (node->getRootNode()!=this->startContainer->getRootNode()){
        return false;
    }
    if (dynamic_cast<DocumentType*>(node)){
        throw InvalidNodeTypeError("u got from the name !");
    }
    if (offset>node->length()){
        throw IndexSizeError("index is not fit !!");
    }
    if (position(node, offset, this->startContainer, this->startOffset)==-1 || position(node, offset, this->endContainer, this->endOffset)==1){
        return false;
    }
    return true;
}


short Range::comparePoint(Node* node, unsigned long offset){
    if (node->getRootNode()!=this->startContainer->getRootNode()){
        throw WrongDocumentError("Wrong document !!");
    }
    if (dynamic_cast<DocumentType*>(node)){
        throw InvalidNodeTypeError("invalid node type !!");
    }
    if (offset>node->length()){
        throw IndexSizeError("index size issue !!");
    }
    if (position(node, offset, this->startContainer, this->startOffset)==-1){
        return -1;
    }
    if (position(node, offset, this->endContainer, this->endOffset)==1){
        return 1;
    }
    return 0;
}


bool Range::intersectsNode(Node* node){
    if (node->getRootNode()!=this->startContainer->getRootNode()){
        return false;
    }
    Node* parent = node->parentNode;
    if (parent==nullptr){
        return true;
    }
    unsigned long offset = node->index();
    if (position(parent, offset, this->endContainer, this->endOffset)==-1 && position(parent, offset+1, this->startContainer, this->startOffset)==1){
        return true;
    }
    return false;
}

DOMString Range::stringification_behavior(){
    DOMString s = "";
    Text* temp = dynamic_cast<Text*>(this->startContainer);
    if (this->startContainer==this->endContainer && temp){
    //     return temp->getdata().substr(this->startOffset, this->endOffset - this->startOffset);
    }
    if (temp){
        // s += temp->getdata().substr(this->startOffset);
    }
    temp = dynamic_cast<Text*>(this->endContainer);
    if (temp){
        // s += temp->getdata().substr(0, this->endOffset);
    }
    return s;
}



unsigned short NodeIterator::filter_node(Node* node){
    //!Later

    // if (this->active){ throw InvalidStateError("INVALID STATE ! HAHA"); }
    // int n = node->nodeType - 1;
    // if (this->filter==nullptr){
    //     return FILTER_ACCEPT;
    // }
    // this->active = true;
    // //some work
    // this->active = false;
    // return result;
	return 1;
}

unsigned short TreeWalker::filter_node(Node* node){
    //!Later

    // if (this->active){ throw InvalidStateError("INVALID STATE ! HAHA"); }
    // int n = node->nodeType - 1;
    // if (this->filter==nullptr){
    //     return FILTER_ACCEPT;
    // }
    // this->active = true;
    // //some work
    // this->active = false;
    // return result;
	return 1;
}



//Node* NodeIterator::nextNode(){
//    return traverse(this, 1);
//}

//Node* NodeIterator::previousNode(){
//    return traverse(this, -1);
//}

Node* TreeWalker::parentNode(){
    Node* node = this->currentNode;
    while (node!=nullptr && node!=this->root){
        node = node->parentNode;
        if (node!=nullptr && this->filter_node(node)==FILTER_ACCEPT){
            this->currentNode = node;
            return node;
        }
    }
    return nullptr;
}

//Node* TreeWalker::firstChild(){
//    return traverse_children(this, 1);
//}

//Node* TreeWalker::lastChild(){
//    return traverse_children(this, -1);
//}


//Node* TreeWalker::nextSibling(){
//    return traverse_sibling(this, 1);
//}

//Node* TreeWalker::previousSibling(){
//    return traverse_sibling(this, -1);
//}

//Node* TreeWalker::previousNode(){
//    Node* node = this->currentNode;
//    while (node!=this->root){
//        Node* sibling = node->previousSibling();
//        while (sibling!=nullptr){
//            node = sibling;
//            int result = this->filter_node(node);
//           while (result!="FILTER_REJECT" && node->hasChildNodes()){
//                node = node->lastChild();
//                result = this->filter_node(node);
//            }
//           if (result==FILTER_ACCEPT){
//                this->currentNode = node;
//                return node;
//            }
//            sibling = node->previousSibling();
//        }
//        if (node==this->root || node->parentNode==nullptr){
//            return nullptr;
//        }
//        // node = node->parentNode();
//        // if (this->filter_node(node)==FILTER_ACCEPT){
//       //    this->currentNode = node;
//        //    return node;
//        //}
//    }
//    return nullptr;
//}


Node* TreeWalker::nextNode(){
    Node* node = this->currentNode;
    unsigned short result = FILTER_ACCEPT;
    while (true){
        while (result!=FILTER_REJECT && node->hasChildNodes()){
            node = node->firstChild();
            result = this->filter_node(node);
            if (result == FILTER_ACCEPT){
                this->currentNode = node;
                return node;
            }
        }
        Node* sibling = nullptr;
        Node* temporary = node;
        while (temporary!=nullptr){
            if (temporary==this->root){
                return nullptr;
            }
            sibling = temporary->nextSibling();
            if (sibling!=nullptr){
                node = sibling;
                break;
            }
            temporary = temporary->parentNode;
        }
        result = this->filter_node(node);
        if (result==FILTER_ACCEPT){
            this->currentNode = node;
            return node;
        }
    }
}



void DOMTokenList::add(std::vector<DOMString> tokens){
    for (auto token: tokens){
        if (token==""){ throw SyntaxError("sytaxxxxxx"); }
        if (token.find(" ")!=std::string::npos){ throw InvalidCharacterError("uk !"); }
    }
    for (auto token: tokens){
        this->list.insert(token);
    }
    this->update();
}


void DOMTokenList::remove(std::vector<DOMString> tokens){
    for (auto token: tokens){
        if (token==""){ throw SyntaxError("sytaxxxxxx"); }
        if (token.find(" ")!=std::string::npos){ throw InvalidCharacterError("uk !"); }
    }
    for (auto token: tokens){
        this->list.erase(token);
    }
    this->update();
}

bool DOMTokenList::toggle(DOMString token, std::optional<bool> force){
    if (token==""){ throw SyntaxError("sytaxxxxxx"); }
    if (token.find(" ")!=std::string::npos){ throw InvalidCharacterError("uk !"); }
    if (this->list.find(token)!=this->list.end()){
        if (!force.has_value() || !force.value()){
            this->list.erase(token);
            this->update();
            return true;
        }
    }
    else{
        if (!force.has_value() || force){
            this->list.insert(token);
            this->update();
            return true;
        }
    }
    return false;
}

bool DOMTokenList::replace(DOMString token, DOMString newToken){
    if (token=="" || newToken==""){ throw SyntaxError("sytaxxxxxx"); }
    if (token.find(" ")!=std::string::npos || newToken.find(" ")!=std::string::npos){ throw InvalidCharacterError("uk !"); }
    if (this->list.find(token)==this->list.end()){ return false; }
    this->list.erase(token);
    this->list.insert(newToken);
    this->update();
    return true;
}


bool DOMTokenList::supports(DOMString token){
    return this->validate(token);
}






int main(){
    std::cout<<"La lala lalalalalalala";
}