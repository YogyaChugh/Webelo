# TODOS

## Events
- Something missing for js in events - inner_event_creation_steps
- create an event for js at https://dom.spec.whatwg.org/#concept-event-create
- CEReactions in node.hpp
- For events, implement legacy unforgeable property for isTrusted.
- Legacy functions/attributes - srcElement (target)
- Implementation of realm class. (Refer to page 13 - to create an event)
- Time Implementation for high-res (inner_event_creation_steps)
- Implement the ServiceWorkerGlobalScope object stuff in addEventListener at https://dom.spec.whatwg.org/#add-an-event-listener !
- Follow the add the following algo for addEventListener at https://dom.spec.whatwg.org/#add-an-event-listener
- Correct add event listener after node.hpp !
- Add check if target is associated Document of the current window in dispath event algo !
- Assert: parent is a slot in dispatchEvent()
- Name updation for slot algo - KEEP IN MIND

## COMPLETE LIST
- Garbage Collection 3.2.1
- 3.3 Using AbortController and AbortSignal objects in APIs

## EXTRAS
- Complete cycle run for the API
- Complete check for the whole DOM STANDARD
> To be done later !

## Mix Later
NonElementParentNode
- Document
- DocumentFragment
DocumentOrShadowRoot
- Document
- ShadowRoot
ParentNode
- Document
- DocumentFragment
- Element
NonDocumentTypeChildNode
- Element
- CharacterData
ChildNode
- DocumentType
- Element
- CharacterData
Slottable
- Element
- Text