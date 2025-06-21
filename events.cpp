#include "events.hpp"

std::vector<EventTarget> Event::composedPath(){
    std::vector<EventTarget> composed_path;
    if path.isNull(){
        return composed_path;
    }
    // assert currentTarget is EventTarget object
    composed_path.push_back(currentTarget)
    int currentTargetIndex = 0;
    int currentTargetHiddenSubtreeLevel = 0;
    int index = path.size() - 1;
    while (index>=0){
        if (path[index].root_of_closed_tree){
            currentTargetHiddenSubtreeLevel++;
        }
        if (path[index].invocation_target==currentTarget){
            currentTargetIndex = index
            break;
        }
        if (path[index].slot_in_closed_tree){
            currentTargetHiddenSubtreeLevel--;
        }
        index--;
    }
    int currentHiddenLevel = currentTargetHiddenSubtreeLevel;
    int maxHiddenLevel = currentTargetHiddenSubtreeLevel;
    index = currentTargetIndex + 1;
    while (index<path.size()){
        if (path[index].slot_in_closed_tree){
            currentHiddenLevel++;
        }
        if (currentHiddenLevel<=maxHiddenLevel){
            composed_path.push_back(path[index].invocation_target)
        }
        if (path[index].root_of_closed_tree){
            currentHiddenLevel--;
            if (currentHiddenLevel<maxHiddenLevel){
                maxHiddenLevel = currentHiddenLevel;
            };
        };
        index++;
    };
    return composed_path;
};