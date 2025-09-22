#pragma once

#define START_TO_START 0;
#define START_TO_END 1;
#define END_TO_END 2;
#define END_TO_START 3;

#include <variant>
#include <vector>
#include <optional>
#include <initializer_list>
#include <stdexcept>
#include <map>

#include "events/events.hpp"
#include "algos_docs.cpp"
#include "base.cpp"
#include "node.hpp"

class Attr;
class CharacterData;
class Text;
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

Element* getElementById(Node* node,const DOMString &elementId){
    if (node->childNodes.length()==0){ return nullptr; }
    Element* currentElement = dynamic_cast<Element*>(node->childNodes[0]);
    std::map<Element*, int> temp = {{currentElement, currentElement->childNodes.length()-1}};
    while (!temp.empty()){
        if (dynamic_cast<Element*>(currentElement)){
            if (currentElement->id==elementId){
                return currentElement;
            }
            if (currentElement->childNodes.length()!=0){
                temp[currentElement] = currentElement->childNodes.length()-1;
                currentElement = currentElement->firstChild();
                continue;
            }
        }
        else{
            continue;
        }
        currentElement = dynamic_cast<Element*>(currentElement->nextSibling());
        while (currentElement==nullptr && !temp.empty()){
            currentElement = (*(temp.end() -1))->nextSibling();
            temp.erase(temp.end()-1);
        }
    }
    
    return nullptr;
}

class NodeIterator{
    public:
        NodeIterator(){};
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
class StaticRange: AbstractRange{
    public:
        StaticRange(StaticRangeInit init);
};


class Range: AbstractRange{
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

        Range cloneRange(); //NewObject
        void detach();
        bool isPointInRange(Node* node, unsigned long offset);
        short comparePoint(Node* node, unsigned long offset);
        bool intersectsNode(Node* node);

        //TODO: stringifier;
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
                if (dynamic_cast<Element*>(a)){
                    this->children.append(dynamic_cast<Element*>(a));
                }
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

        DOMString setvalue(DOMString value){
            if (this->ownerElement==nullptr){ this->value = value; }
            else{ change_attribute_value(this, value); }
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
        Element* previousElementSibling() const;
        Element* nextElementSibling() const;

        friend void before(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj);
        friend void after(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj);
        friend void replaceWith(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj);
        friend void remove(Node* obj);

        DOMString getdata(){ return this->data; }
        DOMString setdata(DOMString data){
            replace_data(this, 0, this->length(),data);
        }
};


//Exposed to window only
class Text: public CharacterData{
    public:
        DOMString wholeText();
        DOMString slot=""; //! IMPORTANT SOMEWHERE in dispatch_event (slottable check)
        DOMString* assignedSlot;
        
        Text(DOMString data = "");
        Text* splitText(unsigned long offset); //NewObject

        virtual void making_it_abstract() override{};
};

//Exposed to window only
class ProcessingInstruction: public CharacterData{
    public:
        DOMString target;

        ProcessingInstruction(){};
};


//Exposed to window only
class Comment: public CharacterData{
    public:
        Comment(DOMString data = "");
};

//Exposed to window only
class CDATASection: public Text{};



//Exposed to window only
class DocumentType: public Node{
    public:
        DOMString name;
        DOMString publicId;
        DOMString systemId;
    
        friend void before(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj);
        friend void after(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj);
        friend void replaceWith(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj);
        friend void remove(Node* obj);

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
        friend Element* getElementById(Node* node ,const DOMString &elementId);
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

        virtual Element* get_the_parent(Event* event) override;
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
        Attr* setNamedItem(Attr attr);
        Attr* setNamedItemNS(Attr attr);
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
        DOMTokenList classList;
        NamedNodeMap attributes;
        ShadowRoot* shadow_root = nullptr;
        CustomElementRegistry* customElementRegistry;
        ElementState customElementState;
        //CEReactions
        DOMString id;
        DOMString className;
        DOMString slot="";
        std::optional<DOMString> is;

        DOMString* assignedSlot; // TODO: CHANGE TYPE AFTER HTML SPEC !!

        DOMString html_uppercased_qualified_name(){
            DOMString qualified_name;
            if (this->prefix==std::nullopt){ qualified_name = this->localName; }
            else{ qualified_name = this->prefix.value() + ":" + this->localName; }
            if (this->ownerDocument->type != XML){
                std::transform(qualified_name.begin(), qualified_name.end(), qualified_name.begin(), [](unsigned char c){ return std::toupper(c); });
            }
            return qualified_name;
        }

        Element(std::optional<DOMString> namesp, std::optional<DOMString> prefix, DOMString localName, CustomElementRegistry* customElementRegistry, ElementState customElementState, Document* ownerdoc = nullptr, Node* parentnode = nullptr): ParentNode(ELEMENT_NODE, this->html_uppercased_qualified_name(), ownerdoc, parentnode){
            this->namespaceURI = namesp;
            this->prefix = prefix;
            this->localName = localName;
            this->customElementRegistry = customElementRegistry;
            this->customElementState = customElementState;
        }

        Element* previousElementSibling() const;
        Element* nextElementSibling() const;

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

        std::optional<Element> insertAdjacentElement(DOMString where, Element element); //legacy
        void insertAdjacentText(DOMString where, DOMString data); //legacy

        friend void before(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj);
        friend void after(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj);
        friend void replaceWith(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj);
        friend void remove(Node* obj);

        bool operator==(Element* other){ return this->isEqualNode(other); }

        virtual void making_it_abstract(){};


        //Getter Setters
        DOMString getid(){
            return fetch_attribute(this, "id");
        }
        void setid(DOMString value){
            set_attribute_value(this, "id", value);
        }

        DOMString getclassName(){
            return fetch_attribute(this, "class");
        }
        void setclassName(DOMString value){
            set_attribute_value(this, "class", value);
        }

        DOMString getslot(){
            return fetch_attribute(this, "slot");
        }
        void setslot(DOMString value){
            set_attribute_value(this, "slot", value);
        }

        ShadowRoot* getshadow_root(){
            if (this->shadow_root==nullptr || this->shadow_root->mode==closed){ return nullptr; }
            return this->shadow_root;
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

        Document(Document* ownerdoc = nullptr, Node* parentnode = nullptr);

        DOMString compatMode();

        std::optional<DOMString> Document::lookupPrefix(std::optional<DOMString> namesp); //Redefining for Node class

        HTMLCollection getElementsByTagName(DOMString qualifiedName);
        HTMLCollection getElementsByTagNameNS(std::optional<DOMString> namesp, DOMString localname);
        HTMLCollection getElementsByClassName(std::vector<DOMString> &classNames);
        friend Element* getElementById(Node* node, const DOMString &elementId);


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
        std::optional<DOMString> item(unsigned long index);
        bool contains(DOMString token);

        //CEReactions
        void add(...);
        void remove(...);
        bool toggle(DOMString token, DOMString newToken);
        DOMString value; //TODO: Implement stringifier
        
        bool supports(DOMString token);
        std::vector<DOMString> list;
};