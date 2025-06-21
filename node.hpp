#include <map>

class EventTarget{};
class DOMString{};
class USVString{};
class Document{};
class Element{};
class NodeList{};

struct GetRootNodeOptions{
    bool composed = false;
}

class Node: public EventTarget{
    public:
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

        unsigned short nodeType;    // The type of node !

        //TODO
        DOMString nodeName; // Name for the node !
        USVString baseURI;  //Base URL For the node document !

        bool isConnected;
        Document ownerDocument; //can be null
        
        Node getRootNode(GetRootNodeOptions options = {});

        Node parentNode; //can be null
        Element parentElement; //can be null
        
        bool hasChildNodes();

        NodeList childNodes;

        Node firstChild; //can be null
        Node lastChild; //can be null
        Node previousSibling; //can be null
        Node nextSibling; //can be null

        // CEReactions
        DOMString nodeValue; //can be null
        DOMString textContent; //can be null
        void normalize();
        Node cloneNode(bool subtree = false);

        bool isEqualNode(Node otherNode); //can be null
        bool isSameNode(Node otherNode); //can be null

        const unsigned short DOCUMENT_POSITION_DISCONNECTED = 0x01;
        const unsigned short DOCUMENT_POSITION_PRECEDING = 0x02;
        const unsigned short DOCUMENT_POSITION_FOLLOWING = 0x04;
        const unsigned short DOCUMENT_POSITION_CONTAINS = 0x08;
        const unsigned short DOCUMENT_POSITION_CONTAINED_BY = 0x10;
        const unsigned short DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC = 0x20;
        
        unsigned short compareDocumentPosition(Node other);
        bool contains(Node other); //can be null

        DOMString lookupPrefix(DOMString namespace); // both input and output can be null
        DOMString lookupNamespaceURI(DOMString prefix); // both input and output can be null

        bool isDefaultNamespace(DOMString namespace); //can be null

        //CEReactions
        Node insertBefore(Node node, Node child); //only child can be null
        Node appendChild(Node node);
        Node replaceChild(Node node, Node child);
        Node removeChild(Node child);

        //TODO: Add associated node document, registered observer list and assigned slot
};

void Node::Node(){
    // TODO: Set baseURI to node document's document base URL #Serialized!
}

bool Node::hasChildNodes(){
    // TODO: Check if Nodelist childnodes is empty or not
}