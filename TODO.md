# TODO'S

## GLOBAL TODO'S
- Comment Sorting
- Resolve Header Files
- Private/Public Resolve
- CEReactions ?
- NewObject, SameObject
- This setter/getter resolving !
- There could be a problem in the future with null character cause it's \0 and also end of string ! So just noting it down !!
- ServiceWorkerGlobalScope implementation in:
    - add_event_listener
    - removeEventListener
    - removeAllEventListeners
- Remember to remove MouseEvent from events.hpp when later rewriting & also adding to algos_events.cpp dispatch_event algo.


## Personal Remember
- Do check `events.md` currentTarget value explanation. Might need improv
- Change reference to `shadow.md` in `events.md`
- Add `path_structs` in docs
- DO NOT RUN THIS BEFORE HAVING THE FULL Windows OBJECT FROM HTML SPEC
- DO CHECK dispatchEvent for associatedDocument of target before running
- add_abort_algo() for abortsignal
- Do change slot in dispatch_event in case the name changes in Element & Text ! Also, it's implementation
- Just logging a possible error: preceding struct check in invoke algo for events.
- Could be later ! Add eventConstructor in fire_event

## Algorithms
> Remember to check all calls to these algo's in-order to rectify arg issues !
- ~~ParseOrderedSet~~
- ~~SerializeOrderedSet~~
- ScopeMatchSelectorString
- cloneANode
- cloneSingleNode
- equalAlgo
- locateNamespacePrefix
- locateNamespace
- preInsertNode
- replaceNode
- preRemoveNode
- ~~ValidNamespacePrefix~~
- ~~ValidElementLocalName~~
    - ~~Very Important ! Just 2 steps left !!~~
- ~~ValidAttributeLocalName~~
- ~~ValidDocTypeName~~
- flattenElementCreationOptions
- CreateElement
- InternalCreateElementNS
- AdoptAlgo
- ~~ValidateAndExtract~~
    - ~~Check for namespace XML, XMLNS~~
- CheckHostIncludingInclusiveAncestor
- ClosedShadowHidden
- ReTarget
- CreateElementInternal
- HandleAttributeChanges
- ChangeAttributeValue
- AppendAttributeToElement
- RemoveAttribute
- ReplaceAttribute
- FetchAttributeByName
- FetchAttributeByNamespaceAndLocalName
- FetchAttributeValue
- SetAttribute
- SetAttributeValue
- RemoveAttributeByName
- RemoveAttributeByNamespaceAndLocalName
- AttributeChangeSteps
- HTMLUpperCasedQualifiedName
- AttachShadowRoot
- listElementsWithQualifiedName
- listElementsWithNamespaceAndLocalName
- listElementsWithClassNames
- InsertAdjacent
- SetExistingAttributeValue
- ReplaceDataNode
- SubstringData
- DetermineNodeLength
- SplitTextNode
- StrictSplitText

## Event
- Realm implementation in `inner_event_creation_steps` & `base.cpp`
- Special event constructing steps for each specification in `inner_event_creation_steps` - **JUST A NOTE**
- Implementation of `relative_high_resolution_coarse_time` in `inner_event_creation_steps`

## CustomEvent

## EventTarget
- In algo for events, `default_passive_value` needs to be complete after HTML work done.
- Add `algo` for `add_event_listener`
- Set `targetOverride` to target's `associatedDocument` in `dispatch_event`
- Assert for `slot` check in `dispatch_event` after implementation of Slot
- Implement check for **shadow-including inclusive ancestor** in `dispatch_event`
- After implementation of realm/global object, remember to complete `inner_invoke` func in `algos_events`
- Relevant `realm` implementation with `eventConstructor` in `fire_event` in algos for events.
- This `realm` boi implementation in `create_event` tooooo.
- Complete the `retard` function after shadow-inclusing ancestor.

## AbortController

## AbortSignal
- Mf global object to trouble again !
- Current realm implementation in `_any` method
- The same thing above in the creating
- `onabort` implementation after HTML

## Mutation Algo's
- `host-including inclusive ancestor` implementation, then for `ensure_pre_insert_validity`
- Point 6 in `ensure_pre_insert_validity` after figuring out best way to find type of child.


## Node
- Meaningfull virtual func -> abstract class
- Implementing `adopt` algo
- ~~`getTheParent` algo~~
- `registered_observer_list` implementation
- `serialize` algo
- `baseURI`
- `normalize()`
- `cloneNode()`
- JS Work for equalAlgo - isEqualNode()
- `compareDocumentPosition()`
- tolower() to be made especially for ASCII

## Document
- Opaque Origin
- `getTheParent` algo
- `serialize` algo
- Constructor work to set origin to origin of current global object's `associated Doc` #HTML
- Resolve this in `createProcessingInstruction` for `Document` -> If target does not match the Name production
- Step 3 in otherwise for `importNode()` in `Document` !! After `CustomElementRegistry` implementation :)
- Complete:
    - `createEvent()`
    - `createRange()`
    - `createNodeIterator()`
    - `createTreeWalker()`


## DOMImplementation
- Empty dict passing to internalCreateElementNS resolving !

## DocumentType

## DocumentFragment
- Define it's constructor using current global object value req #HTML

## ShadowRoot
- onslotchange attribute event handler

## Element
- customElementDefinition implementation
- is value
- validCustomElementName #HTML
- tagName getter steps with HTMLUpperCasedQualifiedName
- If something is in the HTML namespace
- Complete CustomElementRegistry class !
- shadowRoot resolve with getter steps !
- Implement
    - setAttribute()
    - hasAttribute()
    - toggleAttribute()
    - closest()
    - matches()
    - webkitMatchesSelector()
- Implement `refect`

## NamedNodeMap
- supported property names

## Attr
- ownerElement & value

## CharacterData
- Setter steps for data

## Text
- Constructor after figuring out current global object from Realm
- wholeText() implementation later after learning tree structure implementation

## ProcessingInstruction

## Comment
- Constructor after figuring out dude about curreng global object !