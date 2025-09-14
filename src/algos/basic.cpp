#include <variant>
#include "../include/nodes/node.hpp"
#include "../include/nodes/document.hpp"

int determine_node_length(Node* node){
    if ((dynamic_cast<DocumentType*>(node)) || (dynamic_cast<Attr*>(node))){
        return 0;
    }
    if (dynamic_cast<CharacterData*>(node)){
        return node->data.length();
    }
    return node->childNodes.size();
}

// void update_slot_name(Element* element, DOMString &name,  namespace = nullptr){

// }

Node* convert_nodes_to_node(std::vector<std::variant<Node*, DOMString>> nodes, Document* document) {
    Node* node = nullptr;
    int count = 0
    for (auto a: nodes){
        if (std::holds_alternative<DOMString>(a)){
            Text* temp = new Text(std::get<DOMString>(a));
            temp->nodeDocument = document;
            std::replace (nodes.begin(), nodes.end(), a, temp);
        }
        count++;
    }
    if (count==1){
        node = nodes.at(0);
    }
    else{
        node = new DocumentFragment();
        node->nodeDocument = document;
        node->childNodes = nodes;
    }
    return node;
}