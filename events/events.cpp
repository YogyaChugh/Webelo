#include "events.hpp"
#include <typeinfo>


Event::Event(DOMString type, EventInit eventInitDict = {}){
    // run inner event creation steps !
    this->type = temptype;
    this->initialized_flag = true;
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
    if (dispatch_flag){
        return;
    }
    isTrusted = false;
    initialized_flag = true;
    stop_propagation_flag = false;
    stop_immediate_propagation_flag = false;
    canceled_flag = false;
    target = nullptr;
    this->type = type;
    this->bubbles = bubbles;
    this->cancelable = cancelable;
}

std::vector<EventTarget> Event::composedPath(){
    std::vector<EventTarget> composed_path;
    if path.empty(){
        return composed_path;
    }
    // *asserts if currentTarget is of type `EventTarget`
    if typeid(currentTarget) != typeid(EventTarget){
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



// *Custom Event - Inherited from Event class


CustomEvent::CustomEvent(DOMString type, CustomEventInit eventInitDict = {}): Event(type, eventInitDict){
    if (eventInitDict!={}){
        detail = eventInitDict.detail;
    }
}

void CustomEvent::initCustomEvent(DOMString type, auto detail, bool bubbles = false, bool cancelable = false){
    if (dispatch_flag){
        return;
    }
    if (detail){
        this->detail = detail;
    }
    this->initEvent(type, bubbles, cancelable);
}