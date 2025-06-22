#include "events.hpp"
#include <typeinfo>


void Event::Event(DOMString temptype, EventInit eventInitDict = {}){
    if (dispatch_flag){
        return;
    }
    isTrusted = false;
    initialized_flag = true;
    stop_propagation_flag = false;
    stop_immediate_propagation_flag = false;
    canceled_flag = false;
    target = null;
    type = temptype;
    if (eventInitDict!={}){
        bubbles = eventInitDict.bubbles;
        cancelable = eventInitDict.cancelable;
        composed = eventInitDict.composed;
    }
    else{
        bubbles = false;
        cancelable = false;
        composed = false;
    }
};

void Event::stopPropagation(){
    stop_propagation_flag = true;
};

void Event::stopImmediatePropagation(){
    stop_propagation_flag = true;
    stop_immediate_propagation_flag = true;
};

void Event::set_canceled_flag(){
    if (cancelable and !in_passive_listener_flag){
        canceled_flag = true;
    }
};

void Event::preventDefault(){
    // *Cancels the event (if it is cancelable).
    set_canceled_flag();
};

void Event::initEvent(DOMString type, bool bubbles = false, bool cancelable = false){
    EventInit temp;
    temp.bubbles = bubbles;
    temp.cancelable = cancelable;
    this->Event(type,temp);
}

std::vector<EventTarget> Event::composedPath(){
    std::vector<EventTarget> composed_path;
    if path.isNull(){
        return composed_path;
    }
    // *asserts if currentTarget is of type `EventTarget`
    if typeid(currentTarget) == typeid(EventTarget){
        continue;
    }
    else{
        return; //TODO: ERROR
    }
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