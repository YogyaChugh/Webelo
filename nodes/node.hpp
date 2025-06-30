#include "../events/events.hpp"
#include <optional>
#include "../base.hpp"
#include "../nodes/node.hpp"

struct GetRootNodeOptions{
    bool composed = false;
}


//Exposed to Window only !
class Node: public EventTarget{
    private:
        unsigned short nodeType;    // The type of node !
        DOMString nodeName; // Name for the node !
        USVString baseURI;  //Base URL For the node document !
        bool isConnected;
        std::optional<Document> ownerDocument;
        std::optional<Node> parentNode;
        std::optional<Element> parentElement;
        NodeList childNodes;

        std::optional<Node> firstChild;
        std::optional<Node> lastChild;
        std::optional<Node> previousSibling;
        std::optional<Node> nextSibling;
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
        Node getRootNode(GetRootNodeOptions options = {});
        bool hasChildNodes();

        // CEReactions
        std::optional<DOMString> nodeValue;
        std::optional<DOMString> textContent;
        void normalize();
        Node cloneNode(bool subtree = false); //to return a new objcet everytime !

        bool isEqualNode(std::optional<Node> otherNode);
        bool isSameNode(std::optional<Node> otherNode);

        const unsigned short DOCUMENT_POSITION_DISCONNECTED = 0x01;
        const unsigned short DOCUMENT_POSITION_PRECEDING = 0x02;
        const unsigned short DOCUMENT_POSITION_FOLLOWING = 0x04;
        const unsigned short DOCUMENT_POSITION_CONTAINS = 0x08;
        const unsigned short DOCUMENT_POSITION_CONTAINED_BY = 0x10;
        const unsigned short DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC = 0x20;
        
        unsigned short compareDocumentPosition(std::optional<Node> other);
        bool contains(std::optional<Node> other);

        std::optional<DOMString> lookupPrefix(std::optional<DOMString> namesp);
        std::optional<DOMString> lookupNamespaceURI(std::optional<DOMString> prefix);

        bool isDefaultNamespace(std::optional<DOMString> namesp);

        //CEReactions
        Node insertBefore(Node node, std::optional<Node> child);
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


//Exposed to Window only
class NodeList{
    public:
        std::vector<Node> node_list;
        std::optional<Node> item(unsigned long index); //can be null
}

//Exposed to Window only
class HTMLCollection{
    // Implement after Element
    public:
        std::optional<Element> item(unsigned long index);
        std::optional<Element> namedItem(DOMString name);
}