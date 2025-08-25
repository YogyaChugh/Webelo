#ifndef NODE_DOM
#define NODE_DOM

#include "../base.hpp"
#include "../events/events.hpp"

class Node;
class Document;
class Element;


struct GetRootNodeOptions{
    bool composed = false;
};



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
private:
    std::vector<Node*> node_list = {};
public:

    // Returns the Node ptr on the index provided !
    Node* item(unsigned long index) const;

    // Returns the Node ptr on the index provided !
    Node* operator[](unsigned long index) const {
        return this->item(index);
    }

    // Returns the length of the list stored ! Must be stored in a variable.
    [[nodiscard]] unsigned long length() const;

    ~NodeList();
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
private:
    std::vector<Element*> element_list = {};
public:

    // Returns the Node ptr on the index provided !
    Element* item(unsigned long index) const;

    // Returns the Node ptr on the index provided !
    Element* operator[](unsigned long index) const {
        return this->item(index);
    }

    Element* namedItem(DOMString name) const;

    Element* operator[](DOMString name) const {
        return this->namedItem(name);
    }

    // Returns the length of the list stored ! Must be stored in a variable.
    [[nodiscard]] unsigned long length() const;

    ~HTMLCollection();
};




// Types of Node objects possible !!
enum class node_type: unsigned short{
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

//! make this abstract
// The Mega Boss & almost everything in a DOM tree - Node object !! Abstract class
class Node: public EventTarget{
public:

    //Basic INFO.
    node_type nodeType;
    DOMString nodeName;
    USVString baseURI;
    Document* ownerDocument;
    Document* nodeDocument;

    // Not necessary that parent is element ! could be some other type of node baby !
    Node* parentNode;
    Element* parentElement;

    bool isConnected();

    //Babies !!! ( Children )
    NodeList childNodes;
    Node* firstChild();
    Node* lastChild();
    Node* previousSibling();
    Node* nextSibling();

    bool hasChildNodes();

    Node* getRootNode(bool composed = false) {};

    std::optional<DOMString> nodeValue = nullptr;
    std::optional<DOMString> textContent = nullptr;
    void normalize();
    Node cloneNode(bool subtree = false);

    bool isEqualNode(Node* otherNode);
    bool isSameNode(Node* otherNode);

    unsigned short compareDocumentPosition(Node* other);
    bool contains(Node* other);

    std::optional<DOMString> lookupPrefix(std::optional<DOMString> namesp);
    std::optional<DOMString> lookupNamespaceURI(std::optional<DOMString> prefix);

    bool isDefaultNamespace(std::optional<DOMString> namesp);

    Node insertBefore(Node* node, Node* child);
    Node appendChild(Node* node);
    Node replaceChild(Node* node, Node* child);
    Node removeChild(Node* child);

    EventTarget* get_the_parent(Event* event) override;
};


#endif