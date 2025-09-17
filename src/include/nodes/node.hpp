#ifndef NODE_DOM
#define NODE_DOM

#include "../base.hpp"
#include "../events/events.hpp"

class Node;
class Document;
class Element;



#define DOCUMENT_POSITION_DISCONNECTED 0x01
#define DOCUMENT_POSITION_PRECEDING 0x02
#define DOCUMENT_POSITION_FOLLOWING 0x04
#define DOCUMENT_POSITION_CONTAINS 0x08
#define DOCUMENT_POSITION_CONTAINED_BY 0x10
#define DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC 0x20



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
    protected:
        std::vector<Node*> node_list = {};
    public:

        // Returns the Node ptr on the index provided !
        Node* item(const unsigned long &index) const;

        // Returns the Node ptr on the index provided !
        Node* operator[](unsigned long &index) const {
            return this->item(index);
        }

        bool operator==(const NodeList* otherNodeList) const;

        // Returns the length of the list stored ! Must be stored in a variable.
        [[nodiscard]] unsigned long length() const;

        void append(const Node* node){
            this->node_list.push_back(node);
        }

        void insert(const Node* node, const unsigned long &index){
            if (index<0){return;}
            this->node_list.insert(this->node_list.begin()+index, node);
        }

        void remove(const Node* node){
            unsigned int i = 0;
            for (auto a: this->node_list){
                if (*a == *node){
                    this->node_list.erase(this->node_list.begin()+i);
                    return;
                }
                i++;
            }
        }

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
    protected:
        std::vector<Element*> element_list = {};
    public:

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

        void append(const Element* node){
            this->element_list.push_back(node);
        }

        void insert(const Element* node, const unsigned long &index){
            if (index<0){return;}
            this->element_list.insert(this->element_list.begin()+index, node);
        }

        void remove(const Element* node){
            unsigned int i = 0;
            for (auto a: this->element_list){
                if (*a == *node){
                    this->element_list.erase(this->element_list.begin()+i);
                    return;
                }
                i++;
            }
        }

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
        bool isConnected() const inline;

        //Babies !!! ( Children )
        NodeList childNodes;
        Node* firstChild() const inline;
        Node* lastChild() const inline;
        Node* previousSibling() const;
        Node* nextSibling() const;

        bool hasChildNodes() const inline;

        Node* getRootNode(bool &composed = false) const;

        DOMString nodeValue;
        DOMString textContent;
        void normalize();
        Node* cloneNode(bool &subtree = false);

        unsigned long length() const{
            if (dynamic_cast<DocumentType*>(this) || dynamic_cast<Attr*>(this)){
                return 0;
            }
            CharacterData* temp = dynamic_cast<CharacterData*>(this);
            if (temp){
                return temp->data.length();
            }
            return this->childNodes.length();
        }

        bool isEqualNode(const Node* otherNode) const;
        bool isSameNode(const Node* otherNode) const;

        unsigned short compareDocumentPosition(Node* other) const;
        bool contains(const Node* other) const;

        std::optional<DOMString> lookupPrefix(std::optional<DOMString> &namesp) const;
        std::optional<DOMString> lookupNamespaceURI(std::optional<DOMString> &prefix) const;

        bool isDefaultNamespace(std::optional<DOMString> &namesp) const;

        Node* insertBefore(Node* node, Node* child);
        Node* appendChild(Node* node);
        Node* replaceChild(Node* node, Node* child);
        Node* removeChild(Node* child);

        virtual Node* get_the_parent(Event* event) override;

        virtual std::optional<DOMString> getnodeValue(){
            return std::nullopt;
        }
        virtual void setnodeValue(DOMString &val){};
        virtual std::optional<DOMString> gettextContent(){
            return std::nullopt;
        }
        virtual void settextContent(DOMString  &val){};

        virtual void making_it_abstract() = 0;

        bool operator==(Node* other){ return this->isEqualNode(other); }
};


#endif