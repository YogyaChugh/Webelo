#include "../exceptions.cpp"
#include "../include/nodes/node.hpp"
#include "../include/nodes/document.hpp"

void ensure_pre_insert_validity(Node* node, Node* parent, Node* child){
    if (!(dynamic_cast<Document*>(parent)) && !(dynamic_cast<DocumentFragment*>(parent)) && !(dynamic_cast<Element*>(parent))){
        throw HeirarchyRequestError("Shit boi !");
    }
    // 1 step
    if (child != nullptr && child->parentNode != parent){
        throw NotFoundError("Not found fudge !");
    }
    if (!(dynamic_cast<DocumentFragment*>(node)) && !(dynamic_cast<DocumentType*>(node)) && !(dynamic_cast<Element*>(node)) && !(dynamic_cast<CharacterData*>(node))){
        throw HeirarchyRequestError("Shit boi !");
    }
    if ((dynamic_cast<Text*>(node) && dynamic_cast<Document*>(parent)) || (dynamic_cast<DocumentType*>(node) && !(dynamic_cast<Document*>(parent)))){
        throw HeirarchyRequestError("Shit boi !");
    }
    if (dynamic_cast<Document*>(parent)){
        if (dynamic_cast<DocumentFragment*>(node)){
        }
        elif (dynamic_cast<Element*>(node)){
        }
        elif (dynamic_cast<DocumentType*>(node)){
        }
    }
}

void pre_insert(Node* node, Node* parent, Node* child){
    ensure_pre_insert_validity(node, parent, child);
    Node* referenceChild = child;
    
}