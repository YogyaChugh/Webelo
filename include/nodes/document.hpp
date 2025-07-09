#pragma once

#include <variant>
#include <vector>
#include <optional>
#include <initializer_list>
#include <stdexcept>

#include "../events/events.hpp"
#include "../base.hpp"

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
class Document;
class XMLDocument;
class DOMImplementation;
struct GetRootNodeOptions;
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

//Exposed to window only
class AbstractRange{
    private:
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
    private:
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

struct GetRootNodeOptions{
    bool composed = false;
};


//Exposed to Window only !
class Node: public EventTarget{
    // ! REMEMBER TO DO PRIVATE AND SET GETTER/SETTERS
    public:
        unsigned short nodeType;    // The type of node !
        DOMString nodeName; // Name for the node !
        USVString baseURI;  //Base URL For the node document !
        bool isConnected;
        Document* ownerDocument;
        Node* parentNode;
        Element* parentElement;
        NodeList* childNodes;

        Node* firstChild;
        Node* lastChild;
        Node* previousSibling;
        Node* nextSibling;
        const unsigned short ELEMENT_NODE = 1;
        const unsigned short ATTRIBUTE_NODE = 2;
        const unsigned short TEXT_NODE = 3;
        const unsigned short CDATA_SECTION_NODE = 4;
        const unsigned short ENTITY_REFERENCE_NODE = 5;
        const unsigned short ENTITY_NODE = 6;
        const unsigned short PROCESSING_INSTRUCTION_NODE = 7;
        const unsigned short COMMENT_NODE = 8;
        const unsigned short DOCUMENT_NODE = 9;
        const unsigned short DOCUMENT_TYPE_NODE = 10;
        const unsigned short DOCUMENT_FRAGMENT_NODE = 11;
        const unsigned short NOTATION_NODE = 12;


        unsigned short getNodeType() const;
        Node* getRootNode(GetRootNodeOptions options = {}) {
            //! ALTER THIS SOON
            //! MEMORY LEAKING
            return new Node();
        };
        bool hasChildNodes();

        // CEReactions
        std::optional<DOMString> nodeValue;
        std::optional<DOMString> textContent;
        void normalize();
        Node cloneNode(bool subtree = false); //to return a new object everytime !

        bool isEqualNode(Node* otherNode);
        bool isSameNode(Node* otherNode);

        const unsigned short DOCUMENT_POSITION_DISCONNECTED = 0x01;
        const unsigned short DOCUMENT_POSITION_PRECEDING = 0x02;
        const unsigned short DOCUMENT_POSITION_FOLLOWING = 0x04;
        const unsigned short DOCUMENT_POSITION_CONTAINS = 0x08;
        const unsigned short DOCUMENT_POSITION_CONTAINED_BY = 0x10;
        const unsigned short DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC = 0x20;
        
        unsigned short compareDocumentPosition(Node* other);
        bool contains(Node* other);

        std::optional<DOMString> lookupPrefix(std::optional<DOMString> namesp);
        std::optional<DOMString> lookupNamespaceURI(std::optional<DOMString> prefix);

        bool isDefaultNamespace(std::optional<DOMString> namesp);

        //CEReactions
        Node insertBefore(Node* node, Node* child);
        Node appendChild(Node* node);
        Node replaceChild(Node* node, Node* child);
        Node removeChild(Node* child);

        //TODO: Add associated node document, registered observer list and assigned slot

        Document* getownerDocument(){
            return ownerDocument;
        }
};

//Exposed to Window only
class NodeList{
public:
    std::vector<Node*> node_list;
    Node* item(unsigned long index) {
        try {
            Node* p = node_list[index];
            return p;
        }
        catch (std::out_of_range) {
            return nullptr;
        }
    }; //can be nullptr

    [[nodiscard]] size_t length() const {
        return node_list.size();
    }
};

//Exposed to Window only
//LegacyUnenumerableNamedProperties
class HTMLCollection{
    // Implement after Element
public:
    std::vector<Element*> element_list;
    Element* item(unsigned long index) {
        try {
            Element* p = node_list[index];
            return p;
        }
        catch (std::out_of_range) {
            return nullptr;
        }
    }; //can be nullptr
    Element* namedItem(DOMString name); //!Implement Later
    [[nodiscard]] size_t length() const {
        return node_list.size();
    }
};


class ParentNode: public Node {
public:
    HTMLCollection* children;
    Element* firstElementChild() {
        return children->element_list.at(0);
    };
    Element* lastElementChild() {
        return children->element_list.back();
    };

    unsigned long childElementCount{
        return children->length();
    };

    //CEReactions
    //Unscopable
    void prepend(std::initializer_list<std::variant<Node,DOMString>> nodes);
    void append(std::initializer_list<std::variant<Node,DOMString>> nodes);
    void replaceChildren(std::initializer_list<std::variant<Node,DOMString>> nodes);

    //CEReactions
    void moveBefore(Node node,Node* child);

    Element* querySelector(DOMString selectors);

    //New Object
    NodeList querySelectorAll(DOMString selectors);
};



//Exposed to window only
class Attr: public Node{
    private:
        std::optional<DOMString> namespaceURI;
        std::optional<DOMString> prefix;
        DOMString localName;
        DOMString name;
        Element* ownerElement;
        bool specified;
    public:
        //CEReactions
        DOMString value;
};

//Exposed to window only
class CharacterData: Node{
    private:
        unsigned long length;
    public:
        DOMString data; //TODO: LegacyNullToEmptyString
        DOMString substringData(unsigned long offset, unsigned long count);
        void appendData(DOMString data);
        void insertData(unsigned long offset, DOMString data);
        void deleteData(unsigned long offset, unsigned long count);
        void replaceData(unsigned long offset, unsigned long count, DOMString data);
};


//Exposed to window only
class Text: CharacterData{
    private:
        DOMString wholeText;
    public:
        DOMString slot=""; //! IMPORTANT SOMEWHERE in dispatch_event (slottable check)
        Text(DOMString data = "");
        Text splitText(unsigned long offset); //NewObject
};

//Exposed to window only
class ProcessingInstruction: CharacterData{
    private:
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
    private:
        DOMString name;
        DOMString publicId;
        DOMString systemId;
    public:
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

class DocumentFragment: Node{
    public:
        DocumentFragment(){};
        friend Element* getElementById(DOMString elementId);
};

//Exposed to window only
class ShadowRoot: DocumentFragment{
    public:
        ShadowRootMode mode;
        bool delegatesFocus;
        SlotAssignmentMode slotAssignment;
        bool clonable;
        bool serializable;
        Element* host;
        EventHandler onslotchange;

        CustomElementRegistry* custom_element_registry = nullptr;

        CustomElementRegistry* get_custom_element_registry() {
            return custom_element_registry;
        }
};


struct ElementCreationOptions{
    CustomElementRegistry CustomElementRegistry;
    DOMString is;
};

struct ImportNodeOptions{
    CustomElementRegistry customElementRegistry;
    bool selfOnly = false;
};

struct ShadowRootInit{
    ShadowRootMode mode;
    bool delegatesFocus = false;
    SlotAssignmentMode slotAssignment = named;
    bool clonable = false;
    bool serializable = false;
    CustomElementRegistry customElementRegistry;

    ShadowRootInit(ShadowRootMode mod){
        mode = mod;
    }
};

//Exposed to window only + LegacyUnenumerableNamedProperties
class NamedNodeMap{
    private:
        unsigned long length;
    public:
        std::optional<Attr> item(unsigned long index);
        std::optional<Attr> getNamedItem(DOMString qualifiedName);

        std::optional<Attr> getNamedItemNS(std::optional<DOMString> namesp, DOMString localName);

        //CEReactions
        std::optional<Attr> setNamedItem(Attr attr);
        std::optional<Attr> setNamedItemNS(Attr attr);
        Attr removeNamedItem(DOMString qualifiedName);
        Attr removeNamedItemNS(std::optional<DOMString> namesp, DOMString localName);
};

//Exposed to window only
class Element: Node{
    private:
        std::optional<DOMString> namespaceURI;
        std::optional<DOMString> prefix;
        DOMString localName;
        DOMString tagName;
        DOMTokenList classList; //TODO-js: Sameobject & PutForwards=value
        NamedNodeMap attributes; //Sameobject
        ShadowRoot* shadow_root;
        std::optional<CustomElementRegistry> customElementRegistry;
    public:
        //CEReactions
        DOMString id;
        DOMString className;
        DOMString slot=""; //TODO-js: Unscopable
        void setAttribute(DOMString qualifiedName, DOMString value);
        void setAttributeNS(std::optional<DOMString> namesp, DOMString qualifiedName, DOMString value);
        void removeAttribute(DOMString qualifiedName);
        void removeAttributeNS(std::optional<DOMString> namesp, DOMString localName);
        bool toggleAttribute(DOMString qualifiedName, bool force); //force is optional
        std::optional<Attr> setAttributeNode(Attr atter);
        std::optional<Attr> setAttributeNodeNS(Attr attr);
        Attr removeAttributeNode(Attr attr);
        std::optional<Element> insertAdjacentElement(DOMString where, Element element); //legacy
        
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

        void insertAdjacentElement(DOMString where, DOMString data); //legacy
};

//Exposed to window only
class Document: public Node {
public:
        DOMImplementation* implementation;
        USVString URL;
        USVString documentURI;
        DOMString compatMode;
        DOMString characterSet;
        DOMString charset; //legacy alias (characterSet)
        DOMString inputEncoding; //same
        DOMString contentType;

        DocumentType* doctype;
        Element* docuementElement;

        CustomElementRegistry* custom_element_registry = nullptr;

        Document();

        friend Element* getElementById(DOMString elementId);

        HTMLCollection getElementsByTagName(DOMString qualifiedName);
        HTMLCollection getElementsByTagNameNS(std::optional<DOMString> namesp, DOMString localname);
        HTMLCollection getElementsByClassName(DOMString classNames);


        //CEReactions + NewObject
        Element createElement(DOMString localName, std::variant<DOMString,ElementCreationOptions> options); //*NOTE: Keep last argument as optional
        Element createElementNS(std::optional<DOMString> namesp, DOMString qualifiedName, std::variant<DOMString,ElementCreationOptions> options); //*NOTE: Keep last argument as optional
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


        CustomElementRegistry* get_custom_element_registry() {
            return custom_element_registry;
        }
};

//Exposed to window only
class XMLDocument: Document{};

//Exposed to window only
class DOMImplementation{
    public:
    //NewObject
    DocumentType createDocumentType(DOMString name, DOMString publicId, DOMString systemId);
    XMLDocument createDocument(std::optional<DOMString> namesp, DOMString qualifiedName, std::optional<DocumentType> doctype = std::nullopt);
    //qualifiedName is LegacyNullToEmptyString
    Document createHTMLDocument(DOMString title);
    bool hasFeature();
};


Element* getElementById(DOMString elementId) {
    //! LET'S DO IT LATER DUDE ! IT'S CONFUSING CURRENTLY
    std::vector<Node*> elements;
    while (!(elements.empty())) {
        Node* top_stack_element = *(elements.back());
        int visited = 0;
        while (visited!=)
    }
}
