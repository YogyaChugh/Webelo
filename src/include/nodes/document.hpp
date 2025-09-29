#ifndef DOCUMENT
#define DOCUMENT

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


#include <variant>
#include <vector>
#include <optional>
#include <initializer_list>
#include <stdexcept>
#include <map>
#include <set>
#include <algorithm>

#include "../events/events.hpp"
#include "../../algos/algos_docs.cpp"
#include "../../base.cpp"
#include "node.hpp"
#include "../../algos/algos_base.cpp"
#include "../../algos/mutation_algos.cpp"
#include "../../algos/basic.cpp"
#include <algorithm>
#include "../../exceptions.cpp"
#include "../../algos/algos_node.cpp"
#include "assert.h"

class Attr;
class CharacterData;
class Text;
class Element;
class ProcessingInstruction;
class Comment;
class CDATASection;
class DocumentType;
class DocumentFragment;
class ShadowRoot;
struct ElementCreationOptions;
struct ImportNodeOptions;
struct ShadowRootInit;
class NamedNodeMap;
class XMLDocument;
class DOMImplementation;
class NodeList;
class HTMLCollection;
class Document;
class NodeFilter; //! IMPLEMENT THIS !
class NodeIterator; //! THIS TOO !
class TreeWalker; //! THIS TOO !
class AbstractRange;
struct StaticRangeInit;
class StaticRange;
class Range;

// Element* getElementById(Node* node,const DOMString &elementId){
//     if (node->childNodes.length()==0){ return nullptr; }
//     Element* currentElement = dynamic_cast<Element*>(node->childNodes[0]);
//     std::map<Element*, int> temp = {{currentElement, currentElement->childNodes.length()-1}};
//     while (!temp.empty()){
//         if (dynamic_cast<Element*>(currentElement)){
//             if (currentElement->id==elementId){
//                 return currentElement;
//             }
//             if (currentElement->childNodes.length()!=0){
//                 temp[currentElement] = currentElement->childNodes.length()-1;
//                 currentElement = currentElement->firstChild();
//                 continue;
//             }
//         }
//         else{
//             continue;
//         }
//         currentElement = dynamic_cast<Element*>(currentElement->nextSibling());
//         while (currentElement==nullptr && !temp.empty()){
//             currentElement = (*(temp.end() -1))->nextSibling();
//             temp.erase(temp.end()-1);
//         }
//     }
    
//     return nullptr;
// }

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


class NodeFilter{
    public:
        unsigned short acceptNode(Node* node){};
};





//Exposed to window only
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


enum ShadowRootMode{ open, closed};
enum SlotAssignmentMode{ manual, named};





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

        virtual void making_it_abstract() override = 0;

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

        virtual void making_it_abstract() override {};

        void setvalue(DOMString value){
            if (this->ownerElement==nullptr){ this->value = value; }
            // else{ change_attribute_value(this, value); }
        }
};

//Exposed to window only
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
        virtual DOMString setdata(DOMString data){
            replace_data(this, 0, this->length(),data);
        }

        virtual void making_it_abstract() override {};
};


//Exposed to window only
class Text: public CharacterData{
    public:
        DOMString wholeText();
        DOMString slot=""; //! IMPORTANT SOMEWHERE in dispatch_event (slottable check)
        DOMString* assignedSlot;

        virtual DOMString setdata(DOMString data) override{
            replace_data(this, 0, this->length(),data);
        }
        
        Text(DOMString data = ""){
            this->setdata(data);
        };
        Text* splitText(unsigned long offset); //NewObject

        virtual void making_it_abstract() override {};
};

//Exposed to window only
class ProcessingInstruction: public CharacterData{
    public:
        DOMString target;

        virtual DOMString setdata(DOMString data) override{
            replace_data(this, 0, this->length(),data);
        }

        ProcessingInstruction(Document* ownerdoc = nullptr, Node* parentnode = nullptr): CharacterData(ownerdoc, parentnode){};

        virtual void making_it_abstract() override {};
};


//Exposed to window only
class Comment: public CharacterData{
    public:

        virtual DOMString setdata(DOMString data) override{
            replace_data(this, 0, this->length(),data);
        }

        Comment(DOMString data = ""){
            this->setdata(data);
        };

        virtual void making_it_abstract() override {};
};

//Exposed to window only
class CDATASection: public Text{
    public:

        virtual DOMString setdata(DOMString data) override{
            replace_data(this, 0, this->length(),data);
        }

        virtual void making_it_abstract() override {};
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

        virtual void making_it_abstract() override {};
};

class DocumentFragment: public ParentNode{
    public:
        Element* associatedHost = nullptr;
        // friend Element* getElementById(Node* node ,const DOMString &elementId);
        DocumentFragment(Document* ownerdoc = nullptr, Node* parentnode = nullptr): ParentNode(DOCUMENT_FRAGMENT_NODE, "#document-fragment", ownerdoc, parentnode){};

        virtual void making_it_abstract() override{};
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
        virtual Element* get_the_parent(Event* event){
            if (!event->composed_flag && !event->path.empty() && dynamic_cast<EventTarget*>(this) == event->path.at(0).invocation_target){
                return nullptr;
            }
            return this->associatedHost;
        }

        virtual void making_it_abstract() override {};
};


struct ElementCreationOptions{
    CustomElementRegistry* CustomElementRegistry = nullptr;
    std::optional<DOMString> is = std::nullopt;

    ElementCreationOptions(){};
};

struct ImportNodeOptions{
    CustomElementRegistry* customElementRegistry;
    bool selfOnly = false;
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

enum ElementState{
    UNDEFINED, FAILED, UNCUSTOMIZED, PRECUSTOMIZED, CUSTOM
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
        std::optional<DOMString> is;

        DOMString html_uppercased_qualified_name(){
            DOMString qualified_name;
            if (this->prefix==std::nullopt){ qualified_name = this->localName; }
            else{ qualified_name = this->prefix.value() + ":" + this->localName; }
            if (this->ownerDocument->type != XML){
                std::transform(qualified_name.begin(), qualified_name.end(), qualified_name.begin(), [](unsigned char c){ return std::toupper(c); });
            }
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
            return html_uppercased_qualified_name();
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

        HTMLCollection getElementsByTagName(DOMString qualifiedName);
        HTMLCollection getElementsByTagNameNS(std::optional<DOMString> namesp, DOMString localName);
        HTMLCollection getElementsByClassName(DOMString classNames);

        Element* insertAdjacentElement(DOMString where, Element element); //legacy
        void insertAdjacentText(DOMString where, DOMString data); //legacy

        // friend void before(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj);
        // friend void after(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj);
        // friend void replaceWith(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj);
        // friend void remove(Node* obj);

        bool operator==(Element* other){ return dynamic_cast<Node*>(this)->isEqualNode(dynamic_cast<Node*>(other)); }

        virtual void making_it_abstract(){};

        Element(node_type nodeType, DOMString nodeName, Document* ownerDocument, Node* parentNode): ParentNode(ELEMENT_NODE, nodeName, ownerDocument, parentNode){
            this->attributes.associatedElement = this;
        }


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
            this->implementation->associated_doc = this;
        };

        DOMString compatMode();

        std::optional<DOMString> lookupPrefix(std::optional<DOMString> namesp); //Redefining for Node class

        HTMLCollection getElementsByTagName(DOMString qualifiedName);
        HTMLCollection getElementsByTagNameNS(std::optional<DOMString> namesp, DOMString localname);
        HTMLCollection getElementsByClassName(std::vector<DOMString> &classNames);
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
    Document* oldDocument = node->ownerDocument;
    if (node->parentNode!=nullptr){ remove_node(node); }
    if (document!=oldDocument){
        for (auto inclusiveDescendant: node->shad)
    }
}

Element* internal_create_element_ns(Document* document, std::optional<DOMString> namesp, DOMString qualifiedName, std::variant<DOMString,ElementCreationOptions> options){
    std::optional<DOMString> prefix;
    DOMString localName;
    ValidateAndExtract(namesp, qualifiedName, "element", prefix, localName);
    CustomElementRegistry* registry;
    std::optional<DOMString> is;
    flatten_element_creation_options(options, document, registry, is);
    return create_element(document, localName, namesp, prefix, is, true, registry);
}


void change_attribute_value(Attr* attribute, DOMString value){
    DOMString oldValue = attribute->value;
    attribute->value = value;
    handle_attribute_changes(attribute, attribute->ownerElement, oldValue, value);
}

void append_attribute(Attr* attribute, Element* element){
    element->attributes.attribute_list.push_back(attribute);
    attribute->ownerElement = element;
    attribute->ownerDocument = element->ownerDocument;
    handle_attribute_changes(attribute, element, std::nullopt, attribute->value);
}

void remove_attribute(Attr* attribute){
    Element* element = attribute->ownerElement;
    element->attributes.attribute_list.erase(std::find(element->attributes.attribute_list.begin(), element->attributes.attribute_list.end(), attribute));
    attribute->ownerElement = nullptr;
    handle_attribute_changes(attribute, element, attribute->value, std::nullopt);
}

void replace_attribute(Attr* oldAttribute, Attr* newAttribute){
    Element* element = oldAttribute->ownerElement;
    std::replace(element->attributes.attribute_list.begin(), element->attributes.attribute_list.end(), oldAttribute, newAttribute);
    newAttribute->ownerElement = element;
    newAttribute->ownerDocument = element->ownerDocument;
    oldAttribute->ownerElement = nullptr;
    handle_attribute_changes(oldAttribute, element, oldAttribute->value, newAttribute->value);
}

Attr* fetch_attribute(DOMString qualifiedName, Element* element){
    if (element->ownerDocument->type!=XML){
        std::transform(qualifiedName.begin(), qualifiedName.end(), qualifiedName.begin(), [](unsigned char c){ return std::tolower(c); });
    }
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


DOMString fetch_attribute(Element* element, DOMString localName, std::optional<DOMString> namesp = std::nullopt){
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


void set_attribute_value(Element* element, DOMString localName, DOMString value, std::optional<DOMString> prefix = std::nullopt, std::optional<DOMString> namesp = std::nullopt){
    Attr* attribute = fetch_attribute(namesp, localName, element);
    if (attribute==nullptr){
        Attr* attr = new Attr(localName);
        attr->namespaceURI = namesp;
        attr->prefix = prefix;
        attr->value = value;
        attr->ownerDocument = element->ownerDocument;
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
    if (!ValidShadowHostName(element->localName)){ throw NotSupportedError("nope not supported boi !!"); }
    if (ValidCustomElementName(element->localName) || element->is!=std::nullopt){}
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
    shadow->ownerDocument = element->ownerDocument;
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
        return pre_insert_node(node, element->parentNode, element);
    }
    else if (where=="afterbegin"){
        return pre_insert_node(node, element, element->firstChild());
    }
    else if (where=="beforeend"){
        return pre_insert_node(node, element, nullptr);
    }
    else if (where=="afterend"){
        if (element->parentNode==nullptr){ return nullptr; }
        return pre_insert_node(node, element->parentNode, element->nextSibling());
    }
    else{
        throw SyntaxError("syntax errrrrror boi !!");
    }
}

DOMString replace_data(Node* node, unsigned long offset, unsigned long count, DOMString data){
    unsigned length = node->length();
    if (offset>length){ throw IndexSizeError("greater than error !!"); }
    if ((offset+count)>length){ count = length-offset; }
    // queue mutation record
	return "";
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
    Text* currentNode = dynamic_cast<Text*>(node->previousSibling());
    while (currentNode && !dynamic_cast<CDATASection*>(currentNode)){
        temp.insert(temp.begin(), currentNode);
        currentNode = dynamic_cast<Text*>(currentNode->previousSibling());
    }
    currentNode = dynamic_cast<Text*>(node->nextSibling());
    while (currentNode && !dynamic_cast<CDATASection*>(currentNode)){
        temp.push_back(currentNode);
        currentNode = dynamic_cast<Text*>(currentNode->nextSibling());
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
        if (temp2){
            data += temp2->getdata();
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
    unsigned long length = node->length();
    if (offset>length){ throw IndexSizeError("size issues ! You are fat :) "); }
    unsigned long count = length - offset;

    DOMString data = substring_data(node, offset, count);
    Text* new_node = new Text(data);
    new_node->ownerDocument = node->ownerDocument;

    Node* parent = node->parentNode;
    if (parent!=nullptr){
        insert_node(new_node, parent, node->nextSibling());
    }
    replace_data(node, offset, count, "");
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

void set_start_end(Range* range, Node* node, int offset, bool start = true){
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
    fragment->ownerDocument = range->startContainer->ownerDocument;
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
        pre_insert_node(clone, fragment, nullptr);
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
        pre_insert_node(clone, fragment, nullptr);
        replace_data(original_endnode, 0, original_endoffset, "");
    }
    else if (first_partially_contained_child!=nullptr){
        Node* temp = clone_node(last_partially_contained_child);
        CharacterData* clone = dynamic_cast<CharacterData*>(temp);
        pre_insert_node(clone, fragment, nullptr);
        Range* subrange = new Range();
        subrange->startContainer = last_partially_contained_child;
        subrange->startOffset = 0;
        subrange->endContainer = original_endnode;
        subrange->endOffset = original_endoffset;
        DocumentFragment* subfragment = extract_range(subrange);
        pre_insert_node(subfragment, clone, nullptr);   
    }
    range->startContainer = new_node;
    range->endContainer = new_node;
    range->startOffset = new_offset;
    range->endOffset = new_offset;
    return fragment;
}



DocumentFragment* clone_contents(Range* range){
    DocumentFragment* fragment = new DocumentFragment();
    fragment->ownerDocument = range->startContainer->ownerDocument;
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
        pre_insert_node(clone, fragment, nullptr);
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
        pre_insert_node(clone, fragment, nullptr);
    }
    else if (first_partially_contained_child!=nullptr){
        Node* temp = clone_node(first_partially_contained_child);
        CharacterData* clone = dynamic_cast<CharacterData*>(temp);
        pre_insert_node(clone, fragment, nullptr);
        Range* subrange = new Range();
        subrange->startContainer = original_startnode;
        subrange->startOffset = original_startoffset;
        subrange->endContainer = first_partially_contained_child;
        subrange->endOffset = first_partially_contained_child->length();
        DocumentFragment* subfragment = cloen_contents(subrange);
        pre_insert_node(subfragment, clone, nullptr);  
    }
    for (auto child: contained_children){
        Node* clone = clone_node(child);
        pre_insert_node(clone, fragment, nullptr);
    }

    if (dynamic_cast<CharacterData*>(last_partially_contained_child)){
        Node* temp = clone_node(original_endnode);
        CharacterData* clone = dynamic_cast<CharacterData*>(temp);
        clone->setdata(substring_data(original_endnode, 0, original_endoffset));
        pre_insert_node(clone, fragment, nullptr);
    }
    else if (first_partially_contained_child!=nullptr){
        Node* temp = clone_node(last_partially_contained_child);
        CharacterData* clone = dynamic_cast<CharacterData*>(temp);
        pre_insert_node(clone, fragment, nullptr);
        Range* subrange = new Range();
        subrange->startContainer = last_partially_contained_child;
        subrange->startOffset = 0;
        subrange->endContainer = original_endnode;
        subrange->endOffset = original_endoffset;
        DocumentFragment* subfragment = clone_contents(subrange);
        pre_insert_node(subfragment, clone, nullptr);  
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
        if (next!=nullptr){
            node_iterator->referenceNode = next;
            return;
        }
        else{
            node_iterator->pointerBeforeReferenceNode = false;
        }
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




#endif