#include <iostream>
#include "include/nodes/document.hpp"

int main() {
    NodeList nodes;
    std::cout<<"hi";
    std::cout<<"hi";
    Node temp1;
    nodes.node_list.push_back(&temp1);
    Node* node = nodes.item(0);
    if (!node) {
        std::cout<<"it's a nullptr";
    }
    else {
        std::cout<<"nope it's not !";
    }
    std::cout<<"maggi";
}