#include "events.hpp"
#include <typeinfo>
#include "../base.hpp"
#include <ctime>
#include <map>
#include <iostream>


Event::Event(DOMString type, EventInit eventInitDict){
    // run inner event creation steps !
    time_t timestamp;
    DOMHighResTimeStamp now = timestamp;
    this->inner_event_creation_steps(Realm(), now, eventInitDict);
    this->type = type;
};

//void create_event(Event eventInterface, Realm realm = nullptr){
//};

void Event::inner_event_creation_steps(Realm realm, DOMHighResTimeStamp time, EventInit dictionary){
    this->initialized_flag = true;
    this->timeStamp = time;
    this->bubbles = dictionary.bubbles;
    this->cancelable = dictionary.cancelable;
    this->composed = dictionary.composed;
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
    target = EventTarget();
    this->type = type;
    this->bubbles = bubbles;
    this->cancelable = cancelable;
}

std::vector<EventTarget> Event::composedPath(){
    std::vector<EventTarget> composed_path;
    if (path.empty()){
        return composed_path;
    }
    // *asserts if currentTarget is of type `EventTarget`
    if (!dynamic_cast<EventTarget*>(&currentTarget)){
        throw std::runtime_error("currentTarget isn't a type of EventTarget"); //TODO: Implement try catch while calling !
    }
    composed_path.push_back(currentTarget);
    int currentTargetIndex = 0;
    int currentTargetHiddenSubtreeLevel = 0;
    for (size_t index = path.size() - 1; index>=0; index--){
        if (path[index].root_of_closed_tree){
            currentTargetHiddenSubtreeLevel++;
        }
        if (path[index].invocation_target==currentTarget){
            currentTargetIndex = index;
            break;
        }
        if (path[index].slot_in_closed_tree){
            currentTargetHiddenSubtreeLevel--;
        }
    }
    int currentHiddenLevel = currentTargetHiddenSubtreeLevel;
    int maxHiddenLevel = currentTargetHiddenSubtreeLevel;
    for (size_t index = currentTargetIndex + 1; index<path.size(); index++){
        if (path[index].slot_in_closed_tree){
            currentHiddenLevel++;
        }
        if (currentHiddenLevel<=maxHiddenLevel){
            composed_path.push_back(path[index].invocation_target);
        }
        if (path[index].root_of_closed_tree){
            currentHiddenLevel--;
            if (currentHiddenLevel<maxHiddenLevel){
                maxHiddenLevel = currentHiddenLevel;
            };
        }
    }
    return composed_path;
};



// *Custom Event - Inherited from Event class


CustomEvent::CustomEvent(DOMString type, CustomEventInit eventInitDict): Event(type, eventInitDict){
    detail = eventInitDict.detail;
}

void CustomEvent::initCustomEvent(DOMString type, DOMString detail, bool bubbles = false, bool cancelable = false){
    if (dispatch_flag){
        return;
    }
    this->detail = detail;
    this->initEvent(type, bubbles, cancelable);
}

int main(){
    EventInit a;
    Event b = Event("click",a);
    return 0;
}