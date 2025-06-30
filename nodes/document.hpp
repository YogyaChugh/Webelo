#include "node.hpp"
#include <variant>
#include <vector>
#include "../events/events.hpp"
#include "../extra.hpp"

class ShadowRoot{};


//Exposed to window only
class Attr: Node{
    private:
        std::optional<DOMString> namespaceURI;
        std::optional<DOMString> prefix;
        DOMString localName;
        DOMString name;
        std::optional<Element> ownerElement;
        bool specified;
    public:
        //CEReactions
        DOMString value;
}

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
}


//Exposed to window only
class Text: CharacterData{
    private:
        DOMString wholeText;
    public:
        Text(DOMString data = "");
        Text splitText(unsigned long offset); //NewObject
}

//Exposed to window only
class ProcessingInstruction: CharacterData{
    private:
        DOMString target;
}


//Exposed to window only
class Comment: CharacterData{
    public:
        Comment(DOMString data = "");
}

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
}

class DocumentFragment: Node{
    public:
    DocumentFragment(){};
}

enum ShadowRootMode{ open, closed};
enum SlotAssignmentMode{ manual, named};

//Exposed to window only
class ShadowRoot: DocumentFragment{
    private:
        ShadowRootMode mode;
        bool delegatesFocus;
        SlotAssignmentMode slotAssignment;
        bool clonable;
        bool serializable;
        Element host;
    public:
        EventHandler onslotchange;
}


struct ElementCreationOptions{
    CustomElementRegistry CustomElementRegistry;
    DOMString is;
}

struct ImportNodeOptions{
    CustomElementRegistry customElementRegistry;
    bool selfOnly = false;
}

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
}

//Exposed to window only + LegacyUnenumerableNamedProperties
class NamedNodeMap{
    private:
        unsigned long length;
    public:
        std::optional<Attr> item(unsigned long index);
        std::optional<Attr> getNamedItem(DOMString qualifiedName);

        std::optionaL<Attr> getNamedItemNS(std::optional<DOMString> namesp, DOMString localName);

        //CEReactions
        std::optional<Attr> setNamedItem(Attr attr);
        std::optional<Attr> setNamedItemNS(Attr attr);
        Attr removeNamedItem(DOMString qualifiedName);
        Attr removeNamedItemNS(std::optional<DOMString> namesp, DOMString localName);
}

//Exposed to window only
class Element: Node{
    private:
        std::optional<DOMString> namespaceURI;
        std::optional<DOMString> prefix;
        DOMString localName;
        DOMString tagName;
        DOMTokenList classList; //TODO-js: Sameobject & PutForwards=value
        NamedNodeMap attributes; //Sameobject
        std::optional<ShadowRoot> ShadowRoot;
        std::optional<CustomElementRegistry> customElementRegistry;
    public:
        //CEReactions
        DOMString id;
        DOMString className;
        DOMString slot; //TODO-js: Unscopable
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

        ShadowRoot attachShadow(ShadowRootInit init);
        std::optional<Element> closest(DOMString selectors);
        bool matches(DOMString selectors);
        bool webkitMatchesSelectors(DOMString selectors); //legacy .matches

        HTMLCollection getElementsByTagName(DOMString qualifiedName);
        HTMLCollection getElementsByTagNameNS(std::optional<DOMString> namesp, DOMString localName);
        HTMLCollection getElementsByClassName(DOMString classNames);

        void insertAdjacentElement(DOMString where, DOMString data); //legacy
}

//Exposed to window only
class Document: Node {
    private:
        DOMImplementation implementation;
        USVString URL;
        USVString documentURI;
        DOMString compatMode;
        DOMString characterSet;
        DOMString charset; //legacy alias (characterSet)
        DOMString inputEncoding; //same
        DOMString contentType;

        std::optional<DocumentType> doctype;
        std::optional<Element> docuementElement;
    public:
        Document();

        HTMLCollection getElementsByTagName(DOMString qualifiedName);
        HTMLCollection getElementsByTagNameNS(std::optional<DOMString> namesp, DOMString localname);
        HTMLCollection getElementsByClassName(DOMString classNames);


        //CEReactions + NewObject
        Element createElement(DOMString localName, std::variant<DOMString,ElementCreationOptions> options); //*NOTE: Keep last argument as optional
        Element createElementNS(std::optional<DOMString> namesp, DOMString qualifiedName, std::variant<DOMString,ElementCreationOptions> options); //*NOTE: Keep last argument as optional
        Node importNode(Node node, std::variant<bool,ImportNodeOptions> options = false);
        Node adoptNode(Node node); //no NewObject

        //NewObject
        DocumentFragment createDocumentFragment();
        Text createTextNode(DOMString data);
        CDATASection createCDATASection(DOMString data);
        Comment createComment(DOMString data);
        ProcessingInstruction createProcessingInstruction(DOMString target, DOMString data);
        Attr createAttribute(DOMString localName);
        Attr createAttributeNS(std::optional<DOMString> namesp, DOMString qualifiedName);
        Event createEvent(DOMString interface); //LEGACY
        Range createRange();
        NodeIterator createNodeIterator(Node root, unsigned long whatToShow = 0xFFFFFFFF, std::optional<NodeFilter> filter = std::nullopt);
        TreeWalker createTreeWalker(Node root, unsigned long whatToShow = 0xFFFFFFFF, std::optional<NodeFilter> filter = std::nullopt);

}

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
}
