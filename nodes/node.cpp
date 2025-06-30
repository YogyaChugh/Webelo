#include "node.hpp"
#include <optional>

std::optional<Node> NodeList::item(unsigned long index){
    try{
        temp = node_list.at(index);
        return temp;
    }catch (const out_of_range& e){
        return std::nullopt;
    }
}