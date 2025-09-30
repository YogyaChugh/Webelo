#ifndef MUTATION_ALGOS
#define MUTATION_ALGOS


#include "../exceptions.cpp"
#include "../include/nodes/node.hpp"
#include "../include/nodes/document.hpp"
#include "basic.cpp"
#include "algos_docs.cpp"

bool host_including_inclusive_ancestor(Node* A, Node* B){
    if (check_ancestor(B, A, true)){
        return true;
    }
    // auto temp = dynamic_cast<ShadowRoot*>(B);
    // if (temp && temp->getRootNode()->host() && host_including_inclusive_ancestor(A, B->getRootNode()->host())){}
    return false;
}


void ensure_pre_insert_validity(Node* node, Node* parent, Node* child){
    // if (!(dynamic_cast<Document*>(parent)) && !(dynamic_cast<DocumentFragment*>(parent)) && !(dynamic_cast<Element*>(parent))){
    //     throw HeirarchyRequestError("Shit boi !");
    // }

    if (host_including_inclusive_ancestor(node, parent)){
        throw HeirarchyRequestError("Shit boi !");
    }

    if (child && child->parentNode != parent){
        throw NotFoundError("Not found fudge !");
    }
    // if (!(dynamic_cast<DocumentFragment*>(node)) && !(dynamic_cast<DocumentType*>(node)) && !(dynamic_cast<Element*>(node)) && !(dynamic_cast<CharacterData*>(node))){
    //     throw HeirarchyRequestError("Shit boi !");
    // }
    // if ((dynamic_cast<Text*>(node) && dynamic_cast<Document*>(parent)) || (dynamic_cast<DocumentType*>(node) && !(dynamic_cast<Document*>(parent)))){
    //     throw HeirarchyRequestError("Shit boi !");
    // }
    // if (true){
    //     bool element_count = 0;
    //     bool doctype_count = 0;
    //     for (auto a: parent->childNodes.node_list){
    //         if (dynamic_cast<Element*>(a)){ element_count++; }
    //         else if (dynamic_cast<DocumentType*>(a)){ doctype_count++; }
    //     }
    //     if (dynamic_cast<DocumentFragment*>(node)){
    //         int count = 0;
    //         bool has = false;
    //         for (auto a: node->childNodes.node_list){
    //             if (dynamic_cast<Element*>(a)){ count++; }
    //             if (dynamic_cast<Text*>(a)){ has = true; }
    //         }
    //         if (count>1 || has){
    //             throw HeirarchyRequestError("Shit boi !");
    //         }
    //         if (count==1){
    //             if (element_count>0 && dynamic_cast<DocumentType*>(child)){
    //                 throw HeirarchyRequestError("Shit boi !");
    //             }
    //         }
    //     }
    //     else if (dynamic_cast<Element*>(node)){
    //         if (element_count>0 && dynamic_cast<DocumentType*>(child)){
    //             throw HeirarchyRequestError("Shit boi !");
    //         }
    //     }
    //     else if (dynamic_cast<DocumentType*>(node)){
    //         if (doctype_count>0 && child){
    //             throw HeirarchyRequestError("Shit boi !");
    //         }
    //         if (!child && element_count){
    //             throw HeirarchyRequestError("Shit boi !");
    //         }
    //     }
    // }
}


void move_node(Node* node,Node* node2,Node* Child){};
void replace(Node* obj, Node* node, Node* parent){};
// void replace_data(Node* node, unsigned long offset, unsigned long count, DOMString data){}
void insert_node(Node* node, Node* parent, Node* child, bool suppress_observers = false);
void queue_tree_mutation_record(Node* node, NodeList* gg,NodeList* nodes,Node* boi,Node* girl){};

Node* pre_insert_node(Node* node, Node* parent, Node* child){
    ensure_pre_insert_validity(node, parent, child);
    Node* referenceChild = child;
    if (referenceChild == node){
        referenceChild = node->nextSibling();
    }
    insert_node(node, parent, referenceChild);
    return node;
}

void insert_node(Node* node, Node* parent, Node* child, bool suppress_observers){
    NodeList* nodes;
    // if (dynamic_cast<DocumentFragment*>(node)){
    //     nodes = &node->childNodes;
    // }
    // else{
    //     nodes = new NodeList();
    //     nodes->node_list.push_back(node);
    // }
    int count = nodes->length();
    if (count==0){ return; }
    // if (dynamic_cast<DocumentFragment*>(node)){
    //     // remove_node(node);
    //     queue_tree_mutation_record(node, new NodeList(), nodes, nullptr, nullptr);
    // }
    if (child){
        //TODO
    }
    Node* previousSibling;
    if (child){
        previousSibling = child->previousSibling();
    }
    else{
        previousSibling = parent->lastChild();
    }
    for (auto tempnode: nodes->node_list){
        // adopt(tempnode, parent->ownerDocument);
        if (!child){
            parent->childNodes.append(tempnode);
        }
        else{
            auto gg = std::find(parent->childNodes.node_list.begin(), parent->childNodes.node_list.end(), child);
            if (gg!=parent->childNodes.node_list.end()){
                // parent->childNodes.node_list.insert(parent->childNodes.node_list.begin()+index, node);
            }
        }
        // auto bro = dynamic_cast<Element*>(parent);
        // if (bro->shadow_root && bro->shadow_root->slotAssignment==named && (dynamic_cast<Element*>(node) || dynamic_cast<Node*>(node))){
        //     assign_slot(node);
        // }
        // assign_slottables_for_tree(node->getRootNode());
    }
}


void remove_node(Node* node){}

#endif