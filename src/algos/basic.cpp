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