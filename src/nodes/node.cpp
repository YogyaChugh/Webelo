#include "../include/nodes/node.hpp"
#include "../include/nodes/document.hpp"
#include "../algos/algos_base.cpp"
#include "../algos/mutation_algos.cpp"
#include "../algos/algos_node.cpp"


#define DOCUMENT_POSITION_DISCONNECTED 1
#define DOCUMENT_POSITION_PRECEDING 2
#define DOCUMENT_POSITION_FOLLOWING 4
#define DOCUMENT_POSITION_CONTAINS 8
#define DOCUMENT_POSITION_CONTAINED_BY 16
#define DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC 32



// NodeList

Node* NodeList::item(const unsigned long &index) const{
    try {
        return node_list.at(index);
    }
    catch (const std::out_of_range&) {
        return nullptr;
    }
}

unsigned long NodeList::length() const{
    return node_list.size();
}

bool NodeList::operator==(const NodeList* otherNodeList) const{
    if (this->length() != otherNodeList->length()){
        return false;
    }
    for (size_t i=0; i<this->length(); i++){
        if (this->item(i)->isEqualNode(otherNodeList->item(i))){
            continue;
        }
        return false;
    }
    return true;
}

NodeList::~NodeList(){
    for (auto a: node_list) {
        delete a;
    }
    node_list = {};
}




// HTMLCollection

Element* HTMLCollection::item(const unsigned long &index) const{
    try {
        return element_list.at(index);
    }
    catch (const std::out_of_range&) {
        return nullptr;
    }
}

Element* HTMLCollection::namedItem(const DOMString &name) const{
    if (name=="") {
        return nullptr;
    }
    for (auto element: element_list) {
        //! CHECK IF `element` IS IN THE HTML NAMESPACE
        //! CHECK IF `element` HAS A NAME ATTRIBUTE WHOSE VALUE IS name
        if (element->id==name) {
            return element;
        }
    }
    return nullptr;
}

unsigned long HTMLCollection::length() const{
    return element_list.size();
}

HTMLCollection::~HTMLCollection(){
    for (auto a: element_list) {
        delete a;
    }
    element_list.clear();
}




// Node

Node::Node(node_type nodeType, DOMString nodeName, Document* ownerDocument, Node* parentNode){
    this->nodeType = nodeType;
    this->nodeName = nodeName;
    this->ownerDocument = ownerDocument;
    this->parentNode = parentNode;
    if (dynamic_cast<Element*>(parentNode)){
        this->parentElement = dynamic_cast<Element*>(parentNode);
    }
}


bool Node::isConnected(){
    if (dynamic_cast<Document*>(this->getRootNode(true))){
        return true;
    }
    return false;
}

Node* Node::getRootNode(bool composed) {
    if (composed){
        auto temp = dynamic_cast<ShadowRoot*>(this);
        if (temp){
            return temp->host()->getRootNode(composed);
        }
    }
    if (this->parentNode){
        return this->parentNode->getRootNode(composed);
    }
    return this;
}

bool Node::hasChildNodes(){
    if (this->childNodes.length()==0){ return false; }
    return true;
}

Node* Node::firstChild(){
    return childNodes[0];
}
Node* Node::lastChild(){
    return childNodes.node_list.back();
}
Node* Node::previousSibling(){
    if (this->parentNode){
        auto vect = this->parentNode->childNodes->node_list;
        auto it = std::find(vect.begin(), vect.end(), this) - 1;
        if (it==vect.begin() + 1){ return nullptr; };
        return *it;
    }
    return nullptr;
}
Node* Node::nextSibling(){
    if (this->parentNode){
        auto vect = this->parentNode->childNodes->node_list;
        auto it = std::find(vect.begin(), vect.end(), this) + 1;
        if (it==vect.end() - 1){ return nullptr; };
        return *it;
    }
    return nullptr;
}

Node* Node::get_the_parent(Event* event){
    Element* temp = dynamic_cast<Element*>(this);
    if (temp){
        if (temp->assignedSlot!=nullptr){
            return temp->assignedSlot;
        }
    }
    Text* temp2 = dynamic_cast<Text*>(this);
    if (temp2){
        if (temp2->assignedSlot!=nullptr){
            return temp2->assignedSlot;
        }
    }
    return this->parentNode;
}

Node* Node::cloneNode(bool &subtree){
    // node is self, document is nodeDocument, subtree is arg, parent is null, fallbackRegistry is null
    return clone_node(this, subtree=subtree);
    //TODO
}

bool Node::isEqualNode(Node* otherNode){
    if (otherNode==nullptr){ return false; }
    if (nodequals(this, otherNode)){
        return true;
    }
    return false;
}

bool Node::isSameNode(Node* otherNode){
    if (otherNode==this){
        return true;
    }
    return false;
}

unsigned short Node::compareDocumentPosition(Node* other){
    if (this->isSameNode(other)){
        return 0;
    }
    Node* node1 = other;
    Node* node2 = this;
    Attr* attr1 = nullptr;
    Attr* attr2 = nullptr;
    Attr* temp = dynamic_cast<Attr*>(node1);
    Element* temp2;
    if (temp){
        attr1 = temp;
        node1 = attr1->ownerElement;
        temp3 = attr1->ownerElement;
    }
    temp = dynamic_cast<Attr*>(node2);
    Element* temp3;
    if (temp){
        attr2 = temp;
        node2 = attr2->ownerElement;
        temp3 = attr2->ownerElement;
        if (attr2!=nullptr && node1!=nullptr && node2->isSameNode(node1)){
            for (auto attr: temp3->attributes.attribute_list){
                if (attr == attr1){
                    return DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC + DOCUMENT_POSITION_PRECEDING;
                }
                if (attr == attr2){
                    return DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC + DOCUMENT_POSITION_FOLLOWING;
                }
            }
        }
    }
    if (node1==nullptr || node2==nullptr || get_node_root(node1)->isSameNode(get_node_root(node2))){
        return DOCUMENT_POSITION_DISCONNECTED + DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC + DOCUMENT_POSITION_PRECEDING;
    }
    if ((check_ancestor(node2->ownerDocument, node2, node1) && attr1==nullptr) || (node1->isSameNode(node2) && attr2!=nullptr)){
        return DOCUMENT_POSITION_CONTAINS + DOCUMENT_POSITION_PRECEDING;
    }
    if ((check_descendant(node2, node1) && attr2==nullptr) || (node1==node2 && attr1!=nullptr)){
        return DOCUMENT_POSITION_CONTAINED_BY + DOCUMENT_POSITION_FOLLOWING;
    }
    if (check_node_precedes(node2->ownerDocument, node2, node1)){
        return DOCUMENT_POSITION_PRECEDING;
    }
    return DOCUMENT_POSITION_FOLLOWING;
}

bool Node::contains(Node* other){
    if (other==nullptr){return false;}
    return check_descendant(this, other, true);
}

std::optional<DOMString> Node::lookupPrefix(std::optional<DOMString> namesp){
    if (namesp==std::nullopt || namesp==""){ return std::nullopt; }
    if (this->parentElement==nullptr){ return std::nullopt; }
    return locate_a_namespace_prefix(this->parentElement, namesp);
}

std::optional<DOMString> Node::lookupNamespaceURI(std::optional<DOMString> &prefix){
    if (prefix==""){ prefix=std::nullopt; }
    return locate_a_namespace(this, prefix);
}

bool Node::isDefaultNamespace(std::optional<DOMString> &namesp){
    if (namesp==""){ namesp=std::nullopt; }
    std::optional<DOMString> defaultNamespace = locate_a_namespace(this, std::nullopt);
    if (defaultNamespace==namesp){ return true; }
    return false;
}

Node Node::insertBefore(Node* node, Node* child){
    return pre_insert_node(node, this, child);
}

Node Node::appendChild(Node* node){
    return pre_insert_node(node, this, nullptr);
}

Node Node::replaceChild(Node* node, Node* child){
    return replace_node(node, this, child);
}

Node Node::removeChild(Node* child){
    return pre_remove_node(child, this);
}


void Node::normalize(){
    if (node->childNodes.length()==0){ return; }
    Element* currentNode = node->childNodes[0];
    std::vector<Element*> temp = {currentNode};
    while (currentNode!=nullptr){
        if (dynamic_cast<Text*>(currentNode) && !dynamic_cast<CDATASection*>(currentNode)){
            unsigned long length = this->length();
            if (length==0){
                remove_node(currentNode);
            }
            else{
            }
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
}