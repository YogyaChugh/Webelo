#ifndef NODE_DOM
#define NODE_DOM

#include "../../base.cpp"
#include "../events/events.hpp"
#include "document.hpp"

#define DOCUMENT_POSITION_DISCONNECTED 0x01
#define DOCUMENT_POSITION_PRECEDING 0x02
#define DOCUMENT_POSITION_FOLLOWING 0x04
#define DOCUMENT_POSITION_CONTAINS 0x08
#define DOCUMENT_POSITION_CONTAINED_BY 0x10
#define DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC 0x20

class Node;
class Document;
class Element;

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


#endif