#include "include/nodes/node.hpp"
#include "include/nodes/document.hpp"
#include "include/base.hpp"


/*
TODOS:
1) 
*/


Node* clone_a_single_node(Node* node, Document* nodeDocument, CustomElementRegistry* fallbackRegistry){
    // auto copy = nullptr;
    // Element* element = dynamic_cast<Element*>(node)
    // if (element){
    //     CustomElementRegistry* registry = node->customElementRegistry
    //     if (registry==nullptr){ registry = fallbackRegistry;}

    // }
    return nullptr;
}

locate_a_namespace_prefix(Element* some_element,std::optional<DOMString> namesp){
    if (some_element->namespace == namesp && some_element->namespacePrefix!=nullptr){ return some_element->namespacePrefix;}

}