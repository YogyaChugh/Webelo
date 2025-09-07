#ifndef ALGOS_EVENTS_DOM
#define ALGOS_EVENTS_DOM

#include "../include/events/events.hpp"
#include "../base.cpp"
#include "../include/window.hpp"



bool default_passive_value(const DOMString &type, const EventTarget* eventTarget){
    if (type=="touchstart" || type=="touchmove" || type=="wheel" || type=="mousewheel"){
        //TODO
        return true;
    }
    return false;
}

void add_event_listener(const EventTarget* eventTarget, event_listener *listener){
    if (listener->signal != nullptr && listener->signal->getaborted()){ return; }
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
        add_abort_algo(); //TODO
    }
}

event_listener* flatten(const DOMString &type,const EventListener *callback,const std::variant<AddEventListenerOptions,bool> options){
    event_listener* temp = new event_listener();
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
        temp->passive = opts.passive;
        temp->signal = opts.signal;
    }
    return temp;
}

bool dispatch_event(Event* event, EventTarget* target, std::optional<bool> legacy_target_override_flag = std::nullopt, std::optional<bool> legacy_output_did_listeners_throw_flag = std::nullopt){
    event->dispatch_flag = true;

    EventTarget* targetOverride;
    if (legacy_target_override_flag==std::nullopt) {
        targetOverride = target;
    }
    else{
        // set targetOverride to target's associatedDocument
    }

    EventTarget* activationTarget = nullptr;
    EventTarget* relatedTarget = retard(event->relatedTarget, target);
    bool clearTargets = false;

    if (target!=relatedTarget || target==event->relatedTarget) {
        std::vector<EventTarget*> touchTargets = {};
        for (auto touchTarget: event->touch_target_list){
            touchTargets.push_back(retard(touchTarget,target));
        }

        append_to_event(event,target,targetOverride,relatedTarget,touchTargets,false);

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


#endif