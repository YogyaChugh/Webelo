#pragma once

#include <variant>
#include <vector>
#include <optional>
#include <initializer_list>
#include <stdexcept>
#include <map>

#include "../events/events.hpp"
#include "../base.hpp"
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
class Element;
class XMLDocument;
class DOMImplementation;
class Node;
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

const unsigned short START_TO_START = 0;
const unsigned short START_TO_END = 1;
const unsigned short END_TO_END = 2;
const unsigned short END_TO_START = 3;

Element* getElementById(const Node* node,const DOMString &elementId){
    if (node->childNodes.length()==0){ return nullptr; }
    Element* currentElement = node->childNodes[0];
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
        currentElement = currentElement->nextSibling();
        while (currentElement==nullptr && !temp.empty()){
            currentElement = (*(temp.end() -1))->nextSibling();
            temp.erase(temp.end()-1);
        }
    }
    
    return nullptr;
}

//Exposed to window only
class AbstractRange{
    protected:
        Node* startContainer;
        unsigned long startOffset;
        Node* endContainer;
        unsigned long endOffset;
        bool collapsed;
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
    protected:
        Node* commonAncestorContainer;
    public:
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
        DocumentFragment extraContents(); //NewObject
        DocumentFragment cloneContents(); //NewObject
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
    protected:
        HTMLCollection children;
    public:
        Element* firstElementChild() const{
            return children->item(0);
        };
        Element* lastElementChild() const{
            return children->element_list.back();
        };

        unsigned long childElementCount() const{
            return children->length();
        };

        void evaluate_children(){
            for (auto a: this->childNodes){
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
};




//Exposed to window only
class Attr: public Node{
    public:
        std::optional<DOMString> namespaceURI;
        std::optional<DOMString> prefix;
        DOMString localName;
        DOMString name;
        Element* ownerElement;
        bool specified = true;
        //CEReactions
        DOMString value;
        DOMString qualifiedName();

        Attr(DOMString localName);
};

//Exposed to window only
class CharacterData: Node{
    public:
        unsigned long length();
        DOMString data; //TODO: LegacyNullToEmptyString
        DOMString substringData(unsigned long offset, unsigned long count);
        void appendData(DOMString data);
        void insertData(unsigned long offset, DOMString data);
        void deleteData(unsigned long offset, unsigned long count);
        void replaceData(unsigned long offset, unsigned long count, DOMString data);
        Element* previousElementSibling() const;
        Element* nextElementSibling() const;

        friend void before(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj = this);
        friend void after(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj = this);
        friend void replaceWith(std::vector<std::variant<Node*, DOMString>> &nodes, constNode* obj = this);
        friend void remove(const Node* obj = this);
};


//Exposed to window only
class Text: CharacterData{
    public:
        DOMString wholeText;
        DOMString slot=""; //! IMPORTANT SOMEWHERE in dispatch_event (slottable check)
        DOMString* assignedSlot;
        
        Text(DOMString data = "");
        Text splitText(unsigned long offset); //NewObject
};

//Exposed to window only
class ProcessingInstruction: CharacterData{
    public:
        DOMString target;
};


//Exposed to window only
class Comment: CharacterData{
    public:
        Comment(DOMString data = "");
};

//Exposed to window only
class CDATASection: Text{};



//Exposed to window only
class DocumentType: Node{
    protected:
        DOMString name;
        DOMString publicId;
        DOMString systemId;
    public:
    
        friend void before(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj = this);
        friend void after(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj = this);
        friend void replaceWith(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj = this);
        friend void remove(const Node* obj = this);

        DocumentType(name, publicId="", systemId=""){
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

class DocumentFragment: ParentNode{
    public:
        Element* associatedHost = nullptr;
        friend Element* getElementById(const Node* node = this,const DOMString &elementId);
        DocumentFragment(){};
};

//Exposed to window only
class ShadowRoot: DocumentFragment{
    public:
        CustomElementRegistry* custom_element_registry = nullptr;
        ShadowRootMode mode;
        bool delegatesFocus = false;
        bool availableToElementInternals = false;
        bool declarative = false;
        SlotAssignmentMode slotAssignment;
        bool clonable = false;
        bool serializable = false;
        Element* host(){ return this->associatedHost };
        EventHandler onslotchange;

        bool keepCustomElementRegistryNull = false;

        CustomElementRegistry* getcustom_element_registry() const{
            return this->custom_element_registry;
        }

        Element* get_the_parent(Event* event) override;
};


struct ElementCreationOptions{
    CustomElementRegistry CustomElementRegistry;
    DOMString is;
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
        std::optional<Attr> item(unsigned long index);
        std::optional<Attr> getNamedItem(DOMString qualifiedName);

        std::optional<Attr> getNamedItemNS(std::optional<DOMString> namesp, DOMString localName);

        //CEReactions
        std::optional<Attr> setNamedItem(Attr attr);
        std::optional<Attr> setNamedItemNS(Attr attr);
        Attr removeNamedItem(DOMString qualifiedName);
        Attr removeNamedItemNS(std::optional<DOMString> namesp, DOMString localName);
};

enum class ElementState{
    UNDEFINED, FAILED, UNCUSTOMIZED, PRECUSTOMIZED, CUSTOM
}


class Element: ParentNode{
    public:
        std::optional<DOMString> namespaceURI;
        std::optional<DOMString> prefix;
        DOMString localName;
        DOMString tagName;
        DOMTokenList classList; //TODO-js: Sameobject & PutForwards=value
        NamedNodeMap attributes;
        ShadowRoot* shadow_root = nullptr;
        CustomElementRegistry* customElementRegistry;
        ElementState customElementState;
        //CEReactions
        DOMString id;
        DOMString className;
        DOMString slot=""; //TODO-js: Unscopable

        DOMString* assignedSlot; // TODO: CHANGE TYPE AFTER HTML SPEC !!

        Element();

        Element* previousElementSibling() const;
        Element* nextElementSibling() const;


        void setAttribute(DOMString qualifiedName, DOMString value);
        void setAttributeNS(std::optional<DOMString> namesp, DOMString qualifiedName, DOMString value);
        void removeAttribute(DOMString qualifiedName);
        void removeAttributeNS(std::optional<DOMString> namesp, DOMString localName);
        bool toggleAttribute(DOMString qualifiedName, bool force); //force is optional
        std::optional<Attr> setAttributeNode(Attr attr);
        std::optional<Attr> setAttributeNodeNS(Attr attr);
        Attr removeAttributeNode(Attr attr);
        
        bool hasAttributes();
        std::vector<DOMString> getAttributeNames();
        std::optional<DOMString> getAttribute(DOMString qualifiedName);
        std::optional<DOMString> getAttributeNS(std::optional<DOMString> namesp, DOMString localName);
        bool hasAttribute(DOMString qualifiedName);
        bool hasAttributeNS(std::optional<DOMString> namesp, DOMString localname);

        std::optional<Attr> getAttributeNode(DOMString qualifiedName);
        std::optional<Attr> getAttributeNodeNS(std::optional<DOMString> namesp, DOMString localName);

        ShadowRoot* attachShadow(ShadowRootInit init);
        std::optional<Element> closest(DOMString selectors);
        bool matches(DOMString selectors);
        bool webkitMatchesSelectors(DOMString selectors); //legacy .matches

        HTMLCollection getElementsByTagName(DOMString qualifiedName);
        HTMLCollection getElementsByTagNameNS(std::optional<DOMString> namesp, DOMString localName);
        HTMLCollection getElementsByClassName(DOMString classNames);

        std::optional<Element> insertAdjacentElement(DOMString where, Element element); //legacy
        void insertAdjacentText(DOMString where, DOMString data); //legacy

        friend void before(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj = this);
        friend void after(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj = this);
        friend void replaceWith(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj = this);
        friend void remove(const Node* obj = this);
};


enum class DocType: DOMString{
    "xml",
    "html",
    "xml+xhtml"
}

enum class DocMode: DOMString{
    "no-quirks",
    "quirks",
    "limited-quirks"
}

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
        DocType type = "xml";
        DOMString* origin = nullptr; //lateeeeeer
        DocMode mode = "no-quirks";
        bool allow_declarative_shodow_roots = false;

        Document();

        DOMString compatMode();

        std::optional<DOMString> Document::lookupPrefix(std::optional<DOMString> namesp); //Redefining for Node class

        HTMLCollection getElementsByTagName(DOMString qualifiedName);
        HTMLCollection getElementsByTagNameNS(std::optional<DOMString> namesp, DOMString localname);
        HTMLCollection getElementsByClassName(DOMString classNames);
        friend Element* getElementById(const Node* node = this, const DOMString &elementId);


        Element createElement(DOMString localName, std::variant<DOMString,ElementCreationOptions> options); //NOTE: Keep last argument as optional
        Element createElementNS(std::optional<DOMString> namesp, DOMString qualifiedName, std::variant<DOMString,ElementCreationOptions> options); //NOTE: Keep last argument as optional
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
};

//Exposed to window only
class XMLDocument: Document{};


class DOMImplementation{
public:
    Document* associated_doc = nullptr;
    //NewObject
    DocumentType createDocumentType(DOMString name, DOMString publicId, DOMString systemId);
    XMLDocument createDocument(std::optional<DOMString> namesp, DOMString qualifiedName, std::optional<DocumentType> doctype = std::nullopt);
    //qualifiedName is LegacyNullToEmptyString
    Document createHTMLDocument(std::optional<DOMString> title);
    bool hasFeature();
};
