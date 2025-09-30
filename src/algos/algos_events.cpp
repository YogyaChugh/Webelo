#ifndef ALGOS_EVENTS_DOM
#define ALGOS_EVENTS_DOM

#include "../include/events/events.hpp"
#include "../base.cpp"
#include "../include/window.hpp"
#include "../include/nodes/node.hpp"
#include "basic.cpp"
#include <cassert>


EventTarget* retard(EventTarget* a, EventTarget* b){
    auto temp = dynamic_cast<Node*>(a);
    if (!temp){
        return a;
    }
    if (!dynamic_cast<ShadowRoot*>(temp->getRootNode())){
        return a;
    }
    auto temp2 = dynamic_cast<Node*>(b);
    if (temp2 && (check_shadow_including_descendant(temp->getRootNode(), temp2, true))){
        return a;
    }
    auto temp3 = dynamic_cast<ShadowRoot*>(temp->getRootNode());
    if (temp3){
        a = temp3->host();
    }
    return retard(a,b);
}

bool default_passive_value(const DOMString &type, EventTarget* eventTarget){
    if (type=="touchstart" || type=="touchmove" || type=="wheel" || type=="mousewheel"){
        if (dynamic_cast<Window*>(eventTarget)){
            return true;
        }
        else{
            auto temp = dynamic_cast<Node*>(eventTarget);
            if (temp && temp->ownerDocument==(dynamic_cast<Document*>(eventTarget))){
                return true;
            }
            else if (temp && dynamic_cast<Document*>(temp->parentNode)==temp->ownerDocument){
                return true;
            }
        }
    }
    return false;
}

void add_event_listener(EventTarget* eventTarget, event_listener *listener){
    if (listener->signal != nullptr && listener->signal->isaborted()){ return; }
    if (listener->callback == nullptr){ return; }
    if (listener->passive == std::nullopt){
        listener->passive = default_passive_value(listener->type, eventTarget);
    }
    bool found = false;
    for (event_listener* ev: eventTarget->event_listener_list){
        if (ev->type == listener->type && ev->callback == listener->callback && ev->capture == listener->capture){
            found = true;
            break;
        }
    }
    if (!found){
        eventTarget->event_listener_list.push_back(listener);
    }
    if (listener->signal != nullptr ){
        add_abort_algo(std::bind(remove_event_listener, eventTarget, listener), listener->signal);
    }
}

void remove_event_listener(EventTarget* eventTarget, event_listener *listener){
    listener->removed = true;
    auto it = std::find(eventTarget->event_listener_list.begin(),eventTarget->event_listener_list.end(), listener);
    if (it!=eventTarget->event_listener_list.end()){
        eventTarget->event_listener_list.erase(it);
    }
}

event_listener* flatten(DOMString &type, EventListener *callback, std::variant<AddEventListenerOptions,bool> options){
    event_listener* temp = new event_listener(type);
    temp->type = type;
    temp->callback = callback;
    temp->once = false;
    temp->passive = std::nullopt;
    temp->signal = nullptr;
    if (std::holds_alternative<bool>(options)){
        temp->capture = std::get<bool>(options);
    }
    else if (std::holds_alternative<AddEventListenerOptions>(options)){
        auto opts = std::get<AddEventListenerOptions>(options);
        temp->capture = opts.capture;
        temp->once = opts.once;
        if (opts.passive.has_value()){
            temp->passive = opts.passive;
        }
        if (opts.signal){
            temp->signal = opts.signal;
        }
    }
    return temp;
}

bool dispatch_event(Event* event, EventTarget* target, std::optional<bool> legacy_target_override_flag = std::nullopt, std::optional<bool> legacy_output_did_listeners_throw_flag = std::nullopt){
    event->dispatch_flag = true;

    EventTarget* targetOverride;
    if (!legacy_target_override_flag.has_value()) {
        targetOverride = target;
    }
    else{
        // set targetOverride to target's associatedDocument
    }

    EventTarget* activationTarget = nullptr;
    EventTarget* relatedTarget = retard(event->getrelatedTarget(), target);
    bool clearTargets = false;

    Node* targetNode = dynamic_cast<Node*>(target);

    if (target!=relatedTarget || target==event->getrelatedTarget()) {
        std::vector<EventTarget*> touchTargets = {};
        for (auto touchTarget: event->touch_target_list){
            touchTargets.push_back(retard(touchTarget,target));
        }

        append_to_event_path(event,target,targetOverride,relatedTarget,touchTargets,false);

        bool isActivationEvent = false;
        if ((dynamic_cast<MouseEvent*>(event)) && event->gettype()=="click"){
            isActivationEvent = true;
        }
     
        if (isActivationEvent && target->has_activation_behavior){
            activationTarget = target;
        }
        EventTarget* slottable = nullptr;
        auto te = dynamic_cast<Element*>(target);
        if (te && te->assignedSlot){
            slottable = target;
        }
        else{
            auto f = dynamic_cast<Text*>(target);
            if (f && f->assignedSlot){
                slottable = target;
            }
        }

        bool slot_in_closed_tree = false;
        EventTarget* parent = target->get_the_parent(event);
        while (parent){
            auto parentNode = dynamic_cast<Node*>(parent);
            auto parentRoot = dynamic_cast<ShadowRoot*>(parentNode->getRootNode());
            if (slottable){
                assert(dynamic_cast<Element*>(parent) && parentRoot && parentRoot->host());
                slottable = nullptr;
                if (parentRoot && parentRoot->mode==closed){
                    slot_in_closed_tree = true;
                }
            }
            auto te = dynamic_cast<Element*>(parent);
            if (te && te->assignedSlot){
                slottable = parent;
            }
            else{
                auto f = dynamic_cast<Text*>(parent);
                if (f && f->assignedSlot){
                    slottable = parent;
                }
            }
            relatedTarget = retard(event->getrelatedTarget(),parent);
            std::vector<EventTarget*> touchTargets = {};
            for (EventTarget* touchboi: event->touch_target_list){
                touchTargets.push_back(retard(touchboi,parent));
            }
            if (dynamic_cast<Window*>(parent) || (parentNode && check_shadow_including_descendant(targetNode->getRootNode(),parentNode,true))){
                if (isActivationEvent && event->getbubbles() && !activationTarget && parent->has_activation_behavior){
                    activationTarget = parent;
                }
                append_to_event_path(event, parent, nullptr, relatedTarget, touchTargets, slot_in_closed_tree);
            }
            else if (parent==relatedTarget){
                parent = nullptr;
            }
            else{
                target = parent;
                if (isActivationEvent && !activationTarget && target->has_activation_behavior){
                    activationTarget = target;
                }
                append_to_event_path(event, parent, target, relatedTarget, touchTargets, slot_in_closed_tree);
            }
            if (parent){
                parent = parent->get_the_parent(event);
            }
            slot_in_closed_tree = false;
        }

        path_structs clearTargetsStruct;
        for (path_structs &a: event->path){
            if (a.shadow_adjusted_target){
                clearTargetsStruct = a;
            }
        }

        auto tempShadowAdjustedTarget = dynamic_cast<Node*>(clearTargetsStruct.shadow_adjusted_target);
        if (tempShadowAdjustedTarget && dynamic_cast<ShadowRoot*>(tempShadowAdjustedTarget->getRootNode())){
            clearTargets = true;
        }
        else{
            auto tempRelatedTarget = dynamic_cast<Node*>(clearTargetsStruct.related_target);
            if (tempRelatedTarget && dynamic_cast<ShadowRoot*>(tempRelatedTarget->getRootNode())){
                clearTargets = true;
            }
            else{
                Node* tempNode2;
                for (EventTarget* a: clearTargetsStruct.touch_target_list){
                    tempNode2 = dynamic_cast<Node*>(a);
                    if (tempNode2 && dynamic_cast<ShadowRoot*>(tempNode2->getRootNode())){
                        clearTargets = true;
                        break;
                    }
                }
            }
        }


        if (activationTarget && activationTarget->has_legacy_pre_activation_behavior){
            activationTarget->legacy_pre_activation_behavior_algorithm();
        }
        std::vector<path_structs> rev_path = std::vector<path_structs>(event->path.rbegin(),event->path.rend());
        for (path_structs &struc: rev_path){
            if (struc.shadow_adjusted_target){
                event->seteventPhase(AT_TARGET);
            }
            else{
                event->seteventPhase(CAPTURING_PHASE);
            }
            invoke_event(struc, event, CAPTURING_PHASE, legacy_output_did_listeners_throw_flag);
        }
        for (path_structs& a: event->path){
            if (a.shadow_adjusted_target){
                event->seteventPhase(AT_TARGET);
            }
            else{
                if (!(event->getbubbles())){
                    continue;
                }
                event->seteventPhase(BUBBLING_PHASE);
            }
            invoke_event(a, event, BUBBLING_PHASE, legacy_output_did_listeners_throw_flag);
        }
    }
    event->seteventPhase(NONE);
    event->currentTarget = nullptr;
    event->path.clear();
    event->dispatch_flag = false;
    event->stop_propagation_flag = false;
    event->stop_immediate_propagation_flag = false;
    if (clearTargets){
        event->target = nullptr;
        event->relatedTarget = nullptr;
        event->touch_target_list.clear();
    }
    if (activationTarget){
        if (!event->canceled_flag){
            activationTarget->activation_behavior_algorithm(event);
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


void append_to_event_path(Event* event, EventTarget* invocationTarget, EventTarget*  shadowAdjustedTarget, EventTarget* relatedTarget, std::vector<EventTarget*> &touchTargets, bool slot_in_closed_tree){
    bool invocationTargetInShadowTree = false;
    auto tempNode = dynamic_cast<Node*>(invocationTarget);
    if (tempNode &&  dynamic_cast<ShadowRoot*>(tempNode->getRootNode())){
        invocationTargetInShadowTree = true;
    }
    bool root_of_closed_tree = false;
    auto temp = dynamic_cast<ShadowRoot*>(invocationTarget);
    if (temp && temp->mode==closed){
        root_of_closed_tree = true;
    }
    event->path.push_back(path_structs(invocationTarget, invocationTargetInShadowTree, shadowAdjustedTarget, relatedTarget, touchTargets, root_of_closed_tree, slot_in_closed_tree));
}

bool inner_invoke(Event* event, std::vector<event_listener*> &listeners,enum event_phase phase, bool invocationTargetInShadowTree, std::optional<bool> legacyOutputDidListenersThrowFlag = std::nullopt){
    bool found = false;
    for (event_listener* listener: listeners) {
        if (!(listener->removed)) {
            continue;
        }
        if (event->type!=listener->type) {
            continue;
        }
        found = true;
        if ((phase==CAPTURING_PHASE && !(listener->capture)) || (phase==BUBBLING_PHASE && listener->capture)) {
            continue;
        }
        if (listener->once) {
            remove_event_listener(event->currentTarget, listener);
        }
        //! IMPORTANT BEFORE PUBLISH
        //! IMPLEMENT global OBJECT WORK HERE
        //! TEMPORARILY!
        Event* currentEvent = nullptr;
        if (listener->passive) {
            event->in_passive_listener_flag = true;
        }
        //! again global here
        event->in_passive_listener_flag = false;
        if (event->stop_immediate_propagation_flag) {
            break;
        }
    }
    return found;
}


void invoke_event(path_structs &struc, Event* event, enum event_phase phase, std::optional<bool> legacyOutputDidListenersThrowFlag = std::nullopt) {
    event->target = nullptr;
    for (const path_structs a: event->path){
        if (a.shadow_adjusted_target){
            event->target = a.shadow_adjusted_target;
        }
    }
    event->relatedTarget = struc.related_target;
    event->touch_target_list = struc.touch_target_list;
    if (event->stop_propagation_flag){ return; }
    event->currentTarget = struc.invocation_target;
    std::vector<event_listener*> listeners (event->currentTarget->event_listener_list);

    bool invocationTargetInShadowTree = struc.invocation_target_in_shadow_tree;
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

bool fire_event(DOMString e,EventTarget* target,Event* temporary_class = nullptr ,bool legacy_target_override_flag = false) {
    Event* event;
    if (!temporary_class){
        event = new Event(e);
    }
    else{
        event = temporary_class->newObject();
    }
    event->type = e;
    bool returning_val = dispatch_event(event, target, legacy_target_override_flag);
    delete event;
    return returning_val;
};









void add_abort_algo(const std::function<void()> &algo, AbortSignal* signal){
    if (signal->isaborted()){
        return;
    }
    signal->abort_algos.push_back(algo);
}

void remove_abort_algo(std::function<void()> algo, AbortSignal* signal){
    auto it = find(signal->abort_algos.begin(), signal->abort_algos.end(), algo);
    if (it!=signal->abort_algos.end()){
        signal->abort_algos.erase(it);
    }
}

void run_abort_steps(AbortSignal* signal){
    for (auto algo: signal->abort_algos){
        algo();
    }
    signal->abort_algos.clear();
    fire_event("abort", signal);
}


void signal_abort(AbortSignal* signal, std::any reason = nullptr) {
    if (signal->isaborted()) {
        return;
    }
    if (reason.has_value()){
        signal->reason = reason;
    }
    else{
        signal->reason = new AbortError("Abort errors !!");
    }

    std::vector<AbortSignal*> dependentSignalsToAbort = {};
    for (auto &dependentSignal: signal->dependent_signals) {
        if (!(dependentSignal->isaborted())) {
            dependentSignal->reason = signal->reason;
            dependentSignalsToAbort.push_back(dependentSignal);
        }
    }
    run_abort_steps(signal);
    for (const auto &dependentSignal: dependentSignalsToAbort) {
        run_abort_steps(dependentSignal);
    }
}


AbortSignal* create_dependent_abort_signal(std::vector<AbortSignal*> signals, AbortSignal* signalInterface = nullptr, Realm* realm = nullptr) {
    AbortSignal* resultSignal = signalInterface->create_object();
    for (AbortSignal* signal: signals) {
        if (signal->isaborted()) {
            resultSignal->reason = signal->reason;
            return resultSignal;
        }
    }
    resultSignal->dependent = true;
    for (AbortSignal* signal: signals) {
        if (!(signal-> dependent)) {
            resultSignal->source_signals.push_back(signal);
            signal->dependent_signals.push_back(resultSignal);
        }
        else {
            for (AbortSignal* sourceSignal: signal->source_signals) {
                assert(!(sourceSignal->isaborted()) && !(sourceSignal->dependent));
                resultSignal->source_signals.push_back(sourceSignal);
                sourceSignal->dependent_signals.push_back(resultSignal);
            }
        }
    }
    return resultSignal;
}


int main(){}


#endif