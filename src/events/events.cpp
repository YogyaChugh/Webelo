#include "../../include/events/events.hpp"
#include "../../include/events/abort.hpp"
#include "../../include/base.hpp"
#include "../../include/window.hpp"
#include "../../include/exceptions.hpp"
#include "../../include/nodes/document.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <ctime>
#include <cassert>
#include <optional>
#include <any>
#include <functional>
#include <typeinfo>



//any retard(any a, any b){
//    //TODO: Implement (A's root is not a shadow root and B is a node and A's root is a shadow-including inclusive ancestor of B)
//    if (dynamic_cast<Node*> a){
//        return a;
//    }
//    //TODO: Set a to a's root's host
//    return a;
//}


Event::Event(DOMString type, std::unique_ptr<EventInit> eventInitDict){
    // run inner event creation steps !
    time_t timestamp;
    DOMHighResTimeStamp now = timestamp; //TODO: IMPROVE
    this->inner_event_creation_steps(nullptr, now, std::move(eventInitDict));
    this->type = type;
};

//void create_event(Event eventInterface, Realm realm = nullptr){
//};

void Event::inner_event_creation_steps(Realm* realm, DOMHighResTimeStamp time, std::unique_ptr<EventInit> dictionary){
    this->initialized_flag = true;
    this->timeStamp = time;
    if (dictionary){
        this->bubbles = dictionary->bubbles;
        this->cancelable = dictionary->cancelable;
        this->composed = dictionary->composed;
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
    if (cancelable && !in_passive_listener_flag){
        canceled_flag = true;
    }
};

void Event::preventDefault(){
    // *Cancels the event (if it is cancelable).
    set_canceled_flag();
};

void Event::initEvent(DOMString type, bool bubbles, bool cancelable){
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

std::vector<EventTarget*> Event::composedPath(){
    std::vector<EventTarget*> composed_path;
    if (path.empty()){
        return composed_path;
    }
    assert(dynamic_cast<EventTarget*>(currentTarget));
    composed_path.push_back(currentTarget);
    int currentTargetIndex = 0;
    int currentTargetHiddenSubtreeLevel = 0;
    for (size_t index = path.size() - 1; index>=0; index--){
        if (path[index]->root_of_closed_tree){
            currentTargetHiddenSubtreeLevel++;
        }
        if (path[index]->invocation_target==currentTarget){
            currentTargetIndex = index;
            break;
        }
        if (path[index]->slot_in_closed_tree){
            currentTargetHiddenSubtreeLevel--;
        }
    }
    int currentHiddenLevel = currentTargetHiddenSubtreeLevel;
    int maxHiddenLevel = currentTargetHiddenSubtreeLevel;
    for (size_t index = currentTargetIndex - 1; index>=0; index--){
        if (path[index]->root_of_closed_tree){
            currentHiddenLevel++;
        }
        if (currentHiddenLevel<=maxHiddenLevel){
            composed_path.insert(composed_path.begin(),path[index]->invocation_target);
        }
        if (path[index]->slot_in_closed_tree){
            currentHiddenLevel--;
            if (currentHiddenLevel<maxHiddenLevel){
                maxHiddenLevel = currentHiddenLevel;
            }
        }
    }
    currentHiddenLevel = currentTargetHiddenSubtreeLevel;
    maxHiddenLevel = currentTargetHiddenSubtreeLevel;
    for (size_t index = currentTargetIndex + 1; index<path.size(); index++){
        if (path[index]->slot_in_closed_tree){
            currentHiddenLevel++;
        }
        if (currentHiddenLevel<=maxHiddenLevel){
            composed_path.push_back(path[index]->invocation_target);
        }
        if (path[index]->root_of_closed_tree){
            currentHiddenLevel--;
            if (currentHiddenLevel<maxHiddenLevel){
                maxHiddenLevel = currentHiddenLevel;
            };
        }
    }
    return composed_path;
};



// *Custom Event - Inherited from Event class

CustomEvent::CustomEvent(DOMString type, std::unique_ptr<CustomEventInit> eventInitDict, std::optional<std::any> detail): Event(type, std::move(eventInitDict)){
    /*
        Have to implement the detail attribute separately even though it's present in eventInitDict because
        base class constructor requires unique_ptr to be moved to Event class.
    */
    detail = eventInitDict->detail;
}

void CustomEvent::initCustomEvent(DOMString type, bool bubbles, bool cancelable, std::optional<std::any> detail){
    if (dispatch_flag){
        return;
    }
    this->detail = detail;
    this->initEvent(type, bubbles, cancelable);
}


void remove_an_event_listener(EventTarget* eventTarget, event_listener* event_listener){
    //TODO: Implement the ServiceWorkerGlobalScope check !

    event_listener->removed = true;
    auto iter = find(eventTarget->event_listener_list.begin(),eventTarget->event_listener_list.end(),event_listener);
    if (iter!=eventTarget->event_listener_list.end()){
        delete event_listener;
        eventTarget->event_listener_list.erase(iter);
    }
}


void EventTarget::addEventListener(DOMString type, EventListener* callback, std::variant<AddEventListenerOptions, bool> options){
    event_listener* temp = this->flatten(type, callback, options);

    //TODO: Implement the ServiceWorkerGlobalScope check !

    if ((temp->signal && temp->signal->getaborted()) || !temp->callback){
        return;
    }
    if (temp->passive == std::nullopt){
        //TODO: Implement check in window class, node class !
        if (type=="touchstart" || type=="touchmove" || type=="wheel" || type=="mousewheel"){
            // ! CHECK HERE AFTER COMPLETING node.hpp ! IMPORTANT
            //TODO: Implement check for node document's document element and body element !
            if ((dynamic_cast<Window*> (this)) || (dynamic_cast<Node*> (this) && (dynamic_cast<Node*> (this))->getownerDocument()==dynamic_cast<Document*>(this))){
                temp->passive = true;
            }
        }
        temp->passive = false;
    }

    bool found = false;
    
    for (event_listener* a: event_listener_list){
        if (a->type==temp->type && a->callback==temp->callback && a->capture==temp->capture){
            found = true;
            break;
        }
    }
    if (!found){
        event_listener_list.push_back(temp);
    }

    if (temp->signal){
        if (temp->signal->getaborted()){
            return;
        }
        temp->signal->abort_algos.push_back(std::bind(remove_an_event_listener, this, temp));
    }
}


void EventTarget::removeEventListener(DOMString type, EventListener* callback, std::variant<AddEventListenerOptions,bool> options){
    event_listener* temp = this-> flatten(type, callback, options);

    bool found = false;
    
    for (event_listener* a: event_listener_list){
        if (a->type==temp->type && a->callback==temp->callback && a->capture==temp->capture){
            found = true;
            break;
        }
    }
    if (!found){
        return;
    }

    remove_an_event_listener(this, temp);
}

void EventTarget::removeAllEventListeners(){
    //TODO: Implement stuff here !
    for (event_listener* a: event_listener_list){
        a->removed = true;
        delete a;
    }
    event_listener_list.clear();
}

bool EventTarget::dispatchEvent(Event* event){
    //if (event.dispatch_flag || !event.initialized_flag){
    //    throw InvalidStateError("Invalid State");
    //}
    //event.isTrusted = false;
    //
    //event.dispatch_flag = true;
//
    ////TODO: Condition for checking if (this) is associated Document of Window
    //EventTarget targetOverride = this;
//
    //std::optional<EventTarget> activationTarget = std::nullopt;
    //EventTarget relatedTarget = retard(event.relatedTarget, this);
    //bool clearTargets = false;
//
    //if (this!=relatedTarget || this==event.relatedTarget){
    //     std::vector<EventTarget> touchTargets = {};
    //     for (auto a: event.touch_target_list){
    //        touchTargets.push_back(retard(a,this));
    //     }
//
    //     bool invocationTargetInShadowTree = false;
    //     if (dynamic_cast<Node*> event){ //TODO: Also check if it's root is a shadow root
    //        invocationTargetInShadowTree = true;
    //     }
//
    //     //*Append to an event path
//
    //     bool root_of_closed_tree = false;
    //     //TODO: if event is shadow root and mode is "closed" then set root_of_closed_tree to true.
    //     path_structs nstruct = path_structs(this, invocationTargetInShadowTree, targetOverride, relatedTarget, touchTargets, root_of_closed_tree, false);
    //     event.path.push_back(nstruct);
//
    //     //*NEXT
//
    //     bool isActivationEvent = false;
//
    //     if ((dynamic_cast<MouseEvent*> event) && event.type=="click"){
    //        isActivationEvent = true;
    //     }
    //     
    //     if (isActivationEvent and this.) //COMPLETE
//
    //     //TODO: Check for slottable and assigned
    //     std::optional<EventTarget> slottable = this;
//
    //     bool slot_in_closed_tree = false;
//
    //     std::optional<EventTarget> parent = get_the_parent(event);
//
    //     while (parent!=std::nullopt){
    //        if (slottable!=std::nullopt){
    //            //assert check for slot
    //            slottable = std::nullopt;
    //            //if parent's root is shadow root whose mode is closed, set slot_in_closed_tree to true
    //        }
    //     }
//
    //     path_structs clearTargetStruct = 
//
    //}
    return true;
}

int main(){
    EventInit a;
    Event b = Event("click",std::make_unique<EventInit>(a));
    return 0;
}