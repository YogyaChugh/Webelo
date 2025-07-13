#include "document.hpp"
#include "../../include/nodes/document.hpp"
#include "../../include/base.hpp"
#include <optional>

serialize_url(){};

std::optional<Node> NodeList::item(unsigned long index){
    try{
        temp = node_list.at(index);
        return temp;
    }catch (const out_of_range& e){
        return std::nullopt;
    }
}

Node::Node(){
    // TODO: Set baseURI to node document's document base URL #Serialized!

}

bool Node::hasChildNodes(){
    if (childNodes->length() == 0) {
        return false;
    }
    return true;
}

Node* Node::firstChild() {
    return childNodes->item(0);
}

Node* Node::lastChild() {
    return childNodes->item(childNodes.length() - 1);
}







Node* convert_nodes_to_node(std::initializer_list<std::variant<Node,DOMString>> nodes, Document* ownerDocument) {
    Node* node = nullptr;
    for (size_t i = 0; i < nodes.size(); i++) {
        if (dynamic_cast<DOMString*>(nodes[i])) {
            nodes[i] = Text(nodes[i]);
            nodes[i].ownerDocument = ownerDocument;
        }
        else {
            node = &(nodes[0]);
        }
    }
    if (!node) {
        node = new DocumentFragment();
        node->ownerDocument = ownerDocument;
        for (auto a: nodes) {
            node
        }
    }
}


void ParentNode::prepend(std::initializer_list<std::variant<Node,DOMString>> nodes) {
    convert_nodes_to_node(nodes, ownerDocument);
}