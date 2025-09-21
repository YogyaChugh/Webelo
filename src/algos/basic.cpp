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


bool check_ancestor(Node* node, Node* target, bool inclusive = false){
    if (inclusive && node->isSameNode(target)){
        return true;
    }
    if (node==nullptr || target==nullptr){
        return false;
    }
    Node* parent = node->parentNode;
    while (!dynamic_cast<Document*>(parent) && parent!=nullptr){
        if (parent == target){
            return true;
        }
        parent = parent->parentNode;
    }
    return false;
}

bool check_descendant(Node* node, Node* target, bool inclusive = false){
    if (node==nullptr || target==nullptr){
        return false;
    }
    if (node->childNodes.length()==0){ return false; }
    if (inclusive && node->isSameNode(target)){
        return true;
    }
    Node* currentNode = node->childNodes[0];
    std::vector<Node*> temp = {currentNode};
    while (currentNode!=nullptr){
        if (currentNode == target){
            return true;
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
    return false;
}

bool check_node_precedes(Document* doc, Node* node, Node* target){
    if (doc==nullptr || node==nullptr || target==nullptr){
        return false;
    }
    if (doc->childNodes.length()==0){ return false; }
    Node* currentNode = doc->childNodes[0];
    std::vector<Node*> temp = {currentNode};
    while (currentNode!=nullptr){
        if (currentNode == target){
            return true;
        }
        if (currentNode == node){
            break;
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
    return false;
}


bool check_shadow_including_descendant(Node* node, Node* target, bool inclusive = false){
    if (node==nullptr || target==nullptr){
        return false;
    }
    if (check_descendant(node, target, inclusive)){ return true; }
    ShadowRoot* temp = dynamic_cast<ShadowRoot*>(target->getRootNode());
    if (temp){
        return check_shadow_including_descendant(node, dynamic_cast<Node*>(temp->host()));
    }
    return false;
}


bool is_closed_shadow_hidden(Node* A, Node* B){
    ShadowRoot* temp = dynamic_cast<ShadowRoot*>(A->getRootNode());
    if (temp){
        if (!check_shadow_including_descendant(dynamic_cast<Node*>(temp), B, true)){
            if (temp->mode==closed || is_closed_shadow_hidden(dynamic_cast<Node*>(temp->host()), B)){
                return true;
            }
        }
    }
    return false;
}

Node* retarget(Node* A, Node* B){
    Node* temp;
    while (true){
        temp = A->getRootNode();
        if (!dynamic_cast<Node*>(A) || !dynamic_cast<ShadowRoot*>(temp) || (dynamic_cast<Node*>(B) && check_shadow_including_descendant(B, temp))){
            return A;
        }
        A = dynamic_cast<Node*>(dynamic_cast<ShadowRoot*>(temp)->host());
    }
}