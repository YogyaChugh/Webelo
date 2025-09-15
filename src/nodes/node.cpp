#include "include/nodes/node.hpp"
#include "../algos.cpp"


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

Node::Node(node_type nodeType, DOMString nodeName, Document* ownerDocument, Document* nodeDocument, Node* parentNode, Element* parentElement){
    this->nodeType = nodeType;
    this->nodeName = nodeName;
    this->ownerDocument = ownerDocument;
    this->nodeDocument = nodeDocument;
    this->parentNode = parentNode;
    this->parentElement = parentElement;
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
        if temp{
            return temp->host->getRootNode(composed);
        }
    }
    if (parentNode){
        return parentNode->getRootNode(composed);
    }
    return this;
}

bool Node::hasChildNodes(){
    if (this->childNodes.lengt()==0){ return false; }
    return true;
}

Node* Node::firstChild(){
    return childNodes.item(0);
}
Node* Node::lastChild(){
    return childNodes.item(childNodes.length() - 1);
}
Node* Node::previousSibling(){
    if (this->parentNode){
        auto vect = this->parentNode->childNodes->node_list;
        auto it = std::find(vect.begin(), vect.end(), this) - 1;
        if (it==vect.begin()){ return nullptr; };
        return *it;
    }
    return nullptr;
}
Node* Node::nextSibling(){
    if (this->parentNode){
        auto vect = this->parentNode->childNodes->node_list;
        auto it = std::find(vect.begin(), vect.end(), this) + 1;
        if (it==vect.end()){ return nullptr; };
        return *it;
    }
    return nullptr;
}

Node* Node::get_the_parent(Event* event){
    if (typeid(*this) == typeid(Element)){
        Element* temp = dynamic_cast<Element*>(this);
        if (temp->assignedSlot!=nullptr){
            return temp->assignedSlot;
        }
    }
    else if (typeid(*this) == typeid(Text)){
        Text* temp = dynamic_cast<Text*>(this);
        if (temp->assignedSlot!=nullptr){
            return temp->assignedSlot;
        }
    }
    return this->parentNode;
}

Node Node::cloneNode(bool subtree = false){
    // node is self, document is nodeDocument, subtree is arg, parent is null, fallbackRegistry is null
    clone_a_single_node(this, nodeDocument, nullptr)
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
    //TODO
    if (this==other){
        return 0;
    }
    return 0;
}

bool Node::contains(Node* other){
    if (other==nullptr){ return false; }
    if (this->isSameNode(other)){ return true; }
    for (size_t i=0; i<this->childNodes.length(); i++){
        if (this->childNodes.item(i)->isSameNode(other)){
            return true;
        }
    }
    return false;
}

std::optional<DOMString> Node::lookupPrefix(std::optional<DOMString> namesp){
    if (namesp==std::nullopt || namesp.value==""){ return std::nullopt; }
    if (this->parentElement==nullptr){ return std::nullopt; }
    return locate_a_namespace_prefix(this->parentElement, namesp); //algo incomplete
}

std::optional<DOMString> Node::lookupNamespaceURI(std::optional<DOMString> prefix){
    if (prefix.value == ""){ prefix=std::nullopt; }
    return locate_a_namespace(this, prefix);
}

bool Node::isDefaultNamespace(std::optional<DOMString> namesp){
    if (namesp.value==""){ namesp=std::nullopt; }
    std::optional<DOMString> defaultNamespace = locate_a_namespace(this, nullptr);
    if (defaultNamespace==namesp){ return true; }
    return false;
}

Node Node::insertBefore(Node* node, Node* child){
    return preInsertNode(this, node, child);
}

Node Node::appendChild(Node* node){
    return preInsertNode(this, node, nullptr);
}

Node Node::replaceChild(Node* node, Node* child){
    return replaceNode(this, node, child);
}

Node Node::removeChild(Node* child){
    return preRemoveNode(this, child);
}