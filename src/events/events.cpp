#include "../../include/events/events.hpp"
#include "../../include/base.hpp"
#include "../../include/window.hpp"
#include "../../include/exceptions.hpp"
#include "../../include/nodes/document.hpp"
#include "../algos/algos_base.cpp"
#include <iostream>
#include <map>
#include <vector>
#include <ctime>
#include <cassert>
#include <optional>
#include <any>
#include <functional>


void Event::inner_event_creation_steps(const Event* event, const Realm* realm, const DOMHighResTimeStamp &time, bool bubbles, bool cancelable, bool composed){
    event->initialized_flag = true;
    event->timeStamp = time;
    event->bubbles = dictionary->bubbles;
    event->cancelable = dictionary->cancelable;
    event->composed = dictionary->composed;
    //NOTE: Later, special event constructing steps can be passed by specification !!
}


Event::Event(const DOMString &type, bool bubbles, bool cancelable, bool composed){
    DOMHighResTimeStamp now = time(NULL);
    inner_event_creation_steps(this, nullptr, now, bubbles, cancelable, composed);
    this->type = type;
};

Event::Event(const Event* temp){
    DOMHighResTimeStamp now = time(NULL);
    inner_event_creation_steps(this, nullptr, now, temp->bubbles, temp->cancelable, temp->composed);
    this->type = temp->type;
}

void Event::stopPropagation() inline{
    this->stop_propagation_flag = true;
};

void Event::stopImmediatePropagation() inline{
    this->stop_propagation_flag = true;
    this->stop_immediate_propagation_flag = true;
};

void Event::set_canceled_flag() inline{
    if (this->cancelable && !this->in_passive_listener_flag){
        this->canceled_flag = true;
    }
};

void Event::preventDefault(){
    // *Cancels the event (if it is cancelable).
    set_canceled_flag();
};

void Event::initEvent(DOMString &type, bool bubbles, bool cancelable){
    if (this->dispatch_flag){
        return;
    }
    this->isTrusted = false;
    this->initialized_flag = true;
    this->stop_propagation_flag = false;
    this->stop_immediate_propagation_flag = false;
    this->canceled_flag = false;
    this->target = nullptr;
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
    for (int index = path.size() - 1; index>=0; index--){
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
    for (int index = currentTargetIndex - 1; index>=0; index--){
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
    for (int index = currentTargetIndex + 1; index<path.size(); index++){
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








CustomEvent::CustomEvent(DOMString const &type, bool bubbles, bool cancelable, bool composed, std::any &detail): Event(type, bubbles, cancelable, composed){
    this->detail = detail;
}

void CustomEvent::initCustomEvent(DOMString const &type, bool bubbles, bool cancelable, std::any &detail){
    if (this->dispatch_flag){
        return;
    }
    this->initEvent(type, bubbles, cancelable);
    this->detail = detail;
}



Event* create_event(Event* eventInterface, Realm* realm = nullptr){
    DOMHighResTimeStamp now = time(NULL);
    eventInterface->inner_event_creation_steps(realm, now);
    eventInterface->isTrusted = true;
    return eventInterface;
};









EventTarget* retard(EventTarget* a, EventTarget* b){
    //TODO: Implement B is a node and A's root is a shadow-including inclusive ancestor of B)
    auto temp = dynamic_cast<Node*>(a);
    if (!temp || (temp && !(dynamic_cast<ShadowRoot*>(temp->getRootNode()))) || ((dynamic_cast<Node*>(b)))){
        return a;
    }
    //TODO: Set a to a's root's host
    return a;
}


void EventTarget::addEventListener(const DOMString &type, const EventListener* callback, const std::variant<AddEventListenerOptions,bool> &options){
    event_listener* temp = flatten(type, callback, options);
    add_event_listener(this, temp);
}

void EventTarget::removeEventListener(const DOMString &type, const EventListener* callback, bool capture){
    int i = 0;
    event_listener el = event_listener(type, callback, capture);
    for (event_listener* ev: this->event_listener_list){
        if (*ev == el){
            ev->removed = true;
            delete ev;
            eventTarget->event_listener_list.erase(eventTarget->event_listener_list.begin() + i);
            return;
        }
        i++;
    }
}

void EventTarget::removeAllEventListeners(){
    for (event_listener* a: event_listener_list){
        a->removed = true;
        delete a;
    }
    event_listener_list.clear();
}

bool EventTarget::dispatchEvent(Event* event) {
    if (event->dispatch_flag || !event->initialized_flag){
        throw InvalidStateError("Invalid State");
    }
    event->isTrusted = false;
    return dispatch_event(event, false);
}












void signal_abort(AbortSignal* signal, std::optional<std::any> reason = std::nullopt) {
    if (signal->aborted) {
        return;
    }
    if (reason.has_value()){ signal->reason = reason;}
    else{ signal->reason = AbortError("Damn ! Abort error dude :)");}

    std::vector<AbortSignal*> dependentSignalsToAbort = {};
    for (auto dependentSignal: signal->dependent_signals) {
        if (!(dependentSignal->aborted)) {
            dependentSignal->reason = signal->reason;
            dependentSignalsToAbort.push_back(dependentSignal);
        }
    }
    for (auto &algo: signal->abort_algos){ algo(); }
    signal->abort_algos.clear();
    //fire event
    for (const auto dependentSignal: dependentSignalsToAbort) {
        for (auto &algo: dependentSignal->abort_algos) {
            algo();
        }
        dependentSignal->abort_algos.clear();
        //fire event
    }
}


AbortController::AbortController(){
    signal = new AbortSignal();
}

void AbortController::abort(std::optional<std::any> reason) const{
    signal_abort(signal, reason);
}

AbortSignal* create_dependent_abort_signal(std::vector<AbortSignal*> signals, AbortSignal* signalInterface = nullptr, Realm* realm = nullptr) {
    AbortSignal* resultSignal;
    if (!signalInterface){
        resultSignal = new AbortSignal();
    }
    else {
        resultSignal = signalInterface->create_object();
    }
    for (auto a: signals) {
        if (a->aborted) {
            resultSignal->reason = a->reason;
            return resultSignal;
        }
    }
    resultSignal->dependent = true;
    for (auto signal: signals) {
        if (!(signal-> dependent)) {
            resultSignal->dependent_signals.push_back(signal);
            signal->dependent_signals.push_back(resultSignal);
        }
        else {
            for (auto sourceSignal: signal->source_signals) {
                assert(!(sourceSignal->aborted) && !(sourceSignal->dependent));
                resultSignal->source_signals.push_back(sourceSignal);
                sourceSignal->dependent_signals.push_back(resultSignal);
            }
        }
    }
    return resultSignal;
}

AbortSignal* AbortSignal::abort(std::optional<std::any> reason) {
    AbortSignal* signal = new AbortSignal();
    if (reason.has_value()) {
        signal->reason = reason;
    }
    else {
        signal->reason = AbortError("Damn ! Abort error paji! ");
    }
    return signal;
}

AbortSignal* AbortSignal::timeout(unsigned long long milliseconds) {
    AbortSignal* signal = new AbortSignal();
    //! MF GLOBAL OBJECT AGAIN HERE
    return signal;
}

AbortSignal *AbortSignal::_any(std::vector<AbortSignal *> signals) {
    return create_dependent_abort_signal(signals);
}

void AbortSignal::throwIfAborted() {
    if (aborted) {
        reason = std::nullopt;
    }
}






int main(){
    EventInit a;
    //Event b = Event("click",std::make_unique<EventInit>(a));
    return 0;
}