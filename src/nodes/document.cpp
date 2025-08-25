#include "../../include/nodes/document.hpp"
#include "../../include/base.hpp"
#include <optional>


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






// GOD KNOWS WHAT THIS DOES !!
// Docment::get_the_parent(Event* event) override{
//     if (event->type=="load"){
//         return nullptr
//     }
// }

Document::Document(): Node(DOCUMENT_NODE, "#document", nullptr, this, nullptr, nullptr){

}


std::optional<DOMString> Document::lookupPrefix(std::optional<DOMString> namesp){
    if (namesp==std::nullopt || namesp.value==""){ return std::nullopt; }
    /// later dude 
    return locate_a_namespace_prefix(, namesp);
}


DOMString Document::compatMode(){
    if (mode=="quirks"){
        return "BackCompat"
    }
    return "CSS1Compat"
}

Document* Document::Document(){}