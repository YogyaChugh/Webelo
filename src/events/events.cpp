#include "../../include/events/events.hpp"
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



EventTarget* retard(EventTarget* a, EventTarget* b){
    //TODO: Implement B is a node and A's root is a shadow-including inclusive ancestor of B)
    auto temp = dynamic_cast<Node*>(a);
    if (!temp || (temp && !(dynamic_cast<ShadowRoot*>(temp->getRootNode()))) || ((dynamic_cast<Node*>(b)))){
        return a;
    }
    //TODO: Set a to a's root's host
    return a;
}

Event* create_event(Event* eventInterface, Realm* realm = nullptr){
    time_t timestamp;
    DOMHighResTimeStamp now = timestamp; //TODO: IMPROVE
    eventInterface->inner_event_creation_steps(realm, now);
    eventInterface->isTrusted = true;
    return eventInterface;
};


bool fire_event(DOMString& e,EventTarget* target,Event* temporary_class = nullptr ,bool legacy_target_override_flag = false) {
    //! MODIFY LATER FOR eventConstructor
    //! AND MAKE CHANGES to signal_abort where it's called too!
    Event* event;
    if (!temporary_class){
        event = new Event(e);
    }
    else {
        event = temporary_class->create_object();
    }
    event = create_event(event);
    event->type = e;
    //! DO SOMETHING HERE
    bool returning_val = target->dispatch_an_event(event, legacy_target_override_flag);
    delete event;
    return returning_val;
};

void remove_an_event_listener(EventTarget* eventTarget, event_listener* event_listener){
    //TODO: Implement the ServiceWorkerGlobalScope check !

    event_listener->removed = true;
    auto iter = find(eventTarget->event_listener_list.begin(),eventTarget->event_listener_list.end(),event_listener);
    if (iter!=eventTarget->event_listener_list.end()){
        delete event_listener;
        eventTarget->event_listener_list.erase(iter);
    }
}

void append_to_event(Event* event, EventTarget* invocationTarget, EventTarget*  shadowAdjustedTarget, EventTarget* relatedTarget, std::vector<EventTarget*> &touchTargets, bool slot_in_closed_tree){
    bool invocationTargetInShadowTree = false;
    auto tempji = dynamic_cast<Node*>(invocationTarget);
    if (tempji &&  dynamic_cast<ShadowRoot*>(tempji->getRootNode())){
        invocationTargetInShadowTree = true;
    }
    bool root_of_closed_tree = false;
    auto temp = dynamic_cast<ShadowRoot*>(invocationTarget);
    if (temp && temp->mode==closed){
        root_of_closed_tree = true;
    }
    event->path.push_back(std::make_unique<path_structs>(invocationTarget, invocationTargetInShadowTree, shadowAdjustedTarget, relatedTarget, touchTargets, root_of_closed_tree, slot_in_closed_tree));
}

bool inner_invoke(Event* event, std::vector<event_listener*> &listeners,DOMString &phase, bool invocationTargetInShadowTree, std::optional<bool> legacyOutputDidListenersThrowFlag = std::nullopt){
    bool found = false;
    for (auto listener: listeners) {
        if (!(listener->removed)) {
            if (event->type!=listener->type) {
                continue;
            }
            found = true;
            if ((phase=="capturing" && !(listener->capture)) || (phase=="bubbling" && listener->capture)) {
                continue;
            }
            if (listener->once) {
                remove_an_event_listener(event->currentTarget, listener);
            }
            //! IMPORTANT BEFORE PUBLISH
            //! IMPLEMENT global OBJECT WORK HERE
            //! TEMPORARILY!
            if (listener->passive) {
                event->in_passive_listener_flag = true;
            }
            //! again global here
            event->in_passive_listener_flag = false;
            if (event->stop_immediate_propagation_flag) {
                break;
            }
        }
    }
    return found;
}

void invoke(path_structs* struc, Event* event, DOMString phase, std::optional<bool> legacyOutputDidListenersThrowFlag = std::nullopt) {
    event->target = nullptr;
    for (size_t i = event->path.size() - 1; i > -1; i--) {
        if (event->path[i]->shadow_adjusted_target) {
            event->target = event->path[i]->shadow_adjusted_target;
            break;
        }
    }
    event->relatedTarget = struc->related_target;
    event->touch_target_list = struc->touch_target_list;
    if (event->stop_propagation_flag){ return; }
    event->currentTarget = struc->invocation_target;
    std::vector<event_listener*> listeners = event->currentTarget->event_listener_list;

    bool invocationTargetInShadowTree = struc->invocation_target_in_shadow_tree;
    bool found = inner_invoke(event, listeners, phase, invocationTargetInShadowTree,legacyOutputDidListenersThrowFlag);

    if (!found && event->isTrusted) {
        DOMString originalEventType = event->type;
        if (event->type=="animationend") {
            event->type = "webkitAnimationEnd";
        }
        else if (event->type=="animationiteration") {
            event->type = "webkitAnimationIteration";
        }
        else if (event->type=="animationstart") {
            event->type = "webkitAnimationStart";
        }
        else if (event->type=="transitionend") {
            event->type = "webkitTransitionEnd";
        }
        else{return;}
        inner_invoke(event, listeners, phase, invocationTargetInShadowTree, legacyOutputDidListenersThrowFlag);
        event->type = originalEventType;
    }
}


Event::Event(DOMString type, std::unique_ptr<EventInit> eventInitDict){
    // run inner event creation steps !
    time_t timestamp;
    DOMHighResTimeStamp now = timestamp; //TODO: IMPROVE
    this->inner_event_creation_steps(nullptr, now, std::move(eventInitDict));
    this->type = type;
};



void Event::inner_event_creation_steps(Realm* realm, DOMHighResTimeStamp time, std::unique_ptr<EventInit> dictionary){
    //TODO: do something with realm baby !
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

void Event::initEvent(DOMString &type, bool bubbles, bool cancelable){
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



void EventTarget::addEventListener(DOMString type, EventListener* callback, std::variant<AddEventListenerOptions, bool> options){
    event_listener* temp = this->flatten(type, callback, options);

    //TODO: Implement the ServiceWorkerGlobalScope check !

    if ((temp->signal && temp->signal->aborted) || !temp->callback){
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
        if (temp->signal->aborted){
            return;
        }
        temp->signal->abort_algos.push_back(std::bind(remove_an_event_listener, this, temp));
    }
}


void EventTarget::removeEventListener(DOMString& type, EventListener* callback, std::variant<AddEventListenerOptions,bool> &options){
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

bool EventTarget::dispatchEvent(Event* event) {
    //! MAINTAIN RESPONSIBILITY FOR DELETING EVENT !
    if (event->dispatch_flag || !event->initialized_flag){
        throw InvalidStateError("Invalid State");
    }
    event->isTrusted = false;
    return dispatch_an_event(event, false);
}

bool EventTarget::dispatch_an_event(Event* event, bool legacy_target_override_flag){

    //*DISPATCH AN EVENT ALGO STEPS
    event->dispatch_flag = true;

    //TODO: Condition for checking if (this) is associated Document of Window
    EventTarget* targetOverride;
    if (!legacy_target_override_flag) {
        targetOverride = this;
    }

    EventTarget* activationTarget = nullptr;
    EventTarget* relatedTarget = retard(event->relatedTarget, this);
    bool clearTargets = false;

    if (this!=relatedTarget || this==event->relatedTarget) {
        std::vector<EventTarget*> touchTargets = {};
        for (auto touchTarget: event->touch_target_list){
            touchTargets.push_back(retard(touchTarget,this));
        }

        append_to_event(event,this,targetOverride,relatedTarget,touchTargets,false);

        bool isActivationEvent = false;
        if ((dynamic_cast<MouseEvent*>(event)) && event->type=="click"){
            isActivationEvent = true;
        }
     
        if (isActivationEvent && this->has_activation_behavior){
            activationTarget = this;
        }
        EventTarget* slottable = nullptr;
        //! CHECK LATER
        auto temp = dynamic_cast<Element*>(this);
        auto temp2 = dynamic_cast<Text*>(this);
        if ((temp && !(temp->slot.empty())) || (temp2 && !(temp2->slot.empty()))){
            slottable = this;
        }

        bool slot_in_closed_tree = false;
        EventTarget* parent = get_the_parent(event);
        while (parent){
            if (slottable){
                assert(4); //!COMPLETE
                slottable = nullptr;
                auto pakkatemp = dynamic_cast<Node*>(parent);
                auto temporary = dynamic_cast<ShadowRoot*>(pakkatemp->getRootNode());
                if (temporary && temporary->mode==closed){
                    slot_in_closed_tree = true;
                }
            }
            auto temporary1 = dynamic_cast<Element*>(parent);
            auto temporary2 = dynamic_cast<Text*>(parent);
            if (( temporary1 && !(temporary2->slot.empty())) || (temporary2 && !(temporary2->slot.empty()))){
                slottable = parent;
            }
            relatedTarget = retard(event->relatedTarget,parent);
            touchTargets = {};
            for (auto a: event->touch_target_list){
                touchTargets.push_back(retard(a,parent));
            }
            auto tempodabaccha = dynamic_cast<Node*>(parent);
            if (dynamic_cast<Window*>(parent) || (tempodabaccha && tempodabaccha->getRootNode())){
                if (isActivationEvent && event->bubbles && !activationTarget && parent->has_activation_behavior){
                    activationTarget = parent;
                }
                append_to_event(event, parent, nullptr, relatedTarget, touchTargets, slot_in_closed_tree);
            } //!COMPLETE
            else if (parent==relatedTarget){
                parent = nullptr;
            }
            else{
                //!set target to parent
                if (isActivationEvent && !activationTarget && this->has_activation_behavior){
                    activationTarget = this;
                }
                append_to_event(event, parent, this, relatedTarget, touchTargets, slot_in_closed_tree);
            }
            
            if (parent){
                parent = parent->get_the_parent(event);
            }
            slot_in_closed_tree = false;
        }

        path_structs* clearTargetsStruct = nullptr;
        for (auto& a: event->path){
            if (a->shadow_adjusted_target){
                clearTargetsStruct = a.get();
            }
        }

        auto tempboi = dynamic_cast<Node*>(clearTargetsStruct->shadow_adjusted_target);
        if (tempboi && dynamic_cast<ShadowRoot*>(tempboi->getRootNode())){
            clearTargets = true;
        }
        auto tempboi2 = dynamic_cast<Node*>(clearTargetsStruct->related_target);
        if (tempboi2 && dynamic_cast<ShadowRoot*>(tempboi2->getRootNode())){
            clearTargets = true;
        }
        Node* tempgo;
        for (auto a: clearTargetsStruct->touch_target_list){
            tempgo = dynamic_cast<Node*>(a);
            if (tempgo && dynamic_cast<ShadowRoot*>(tempgo->getRootNode())){
                clearTargets = true;
            }
        }


        if (activationTarget && activationTarget->has_legacy_pre_activation_behavior){
            activationTarget->legacy_pre_activation_behavior_algorithm();
        }
        for (size_t i = event->path.size() - 1;i > -1; i--){
            if (event->path[i]->shadow_adjusted_target){
                event->eventPhase = AT_TARGET;
            }
            else{
                event->eventPhase = CAPTURING_PHASE;
            }
            invoke(event->path[i].get(),event,"capturing");
        }
        for (auto& a: event->path){
            if (a->shadow_adjusted_target){
                event->eventPhase = AT_TARGET;
            }
            else{
                if (!(event->bubbles)){
                    continue;
                }
                event->eventPhase = BUBBLING_PHASE;
            }
            invoke(a.get(),event,"bubbling");

        }
    }
    event->eventPhase = NONE;
    event->currentTarget = nullptr;
    event->path.clear();
    event->dispatch_flag = false;
    event->stop_propagation_flag = false;
    event->stop_immediate_propagation_flag = false;
    if (clearTargets){
        event->target = nullptr;
        event->relatedTarget = nullptr;
        event->touch_target_list = {};
    }
    if (activationTarget){
        if (!(event->canceled_flag)){
            activationTarget->activation_behavior_algorithm();
        }
        else if(activationTarget->has_legacy_canceled_activation_behavior){
            activationTarget->legacy_canceled_activation_behavior_algorithm;
        }
    }
    if (event->canceled_flag){
        return false;
    }
    return true;
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