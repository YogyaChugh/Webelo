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
- the getnodeValue() && gettextContent() method in Node class returns a "" rather than nullptr
- Can add later (special cloning steps in other specifications) for `clone_node` in algos_node.cpp
- Could be error in node.cpp compareDocumentPosition
- Node's node document can be changed using the adopt algo
- Encoding sort for Document object
- Doctype and mode check eveywhere ! all functions change
- Controversial ownerDocument vs nodeDocument
- Running normal split instead strict split `base_algos.cpp`
- Replace seteventPhase() #Later
- Always have a newObject func in new Event derived clases
- Work on onabort attribute in `AbortSignal` object !

## Algorithms
> Remember to check all calls to these algo's in-order to rectify arg issues !
- ~~parse_ordered_set~~
- ~~serialize_ordered_set~~
- scope_match_selectors_string
- ~~clone_node~~
- ~~clone_a_single_node~~
- ~~locate_a_namespace_prefix~~
- ~~locate_a_namespace~~
- ~~add_event_listener~~
- ~~remove_event_listener~~
- preInsertNode
- replaceNode
- preRemoveNode
- ~~ValidNamespacePrefix~~
- ~~ValidElementLocalName~~
    - ~~Very Important ! Just 2 steps left !!~~
- ~~ValidAttributeLocalName~~
- ~~ValidDocTypeName~~
- ~~flatten_element_creation_options~~
- create_element
- ~~internal_create_element_ns~~
- adopt
- ~~ValidateAndExtract~~
    - ~~Check for namespace XML,d XMLNS~~
- ~~check_shadow_including_descendant~~
- ~~find_root~~
- ~~is_closed_shadow_hidden~~
- ~~retarget~~
- create_element_internal
- handle_attribute_changes
- ~~change_attribute_value~~
- ~~append_attribute~~
- ~~remove_attribute~~
- ~~replace_attribute~~
- ~~FetchAttributeByName~~
- ~~FetchAttributeByNamespaceAndLocalName~~
- ~~FetchAttributeValue~~
- ~~set_attribute~~
- ~~set_attribute_value~~
- ~~remove_attribute_by_name~~
- ~~remove_attribute_by_namespace~~
- ~~html_uppercased_qualified_name~~
- ~~attach_shadow_root~~
- listElementsWithQualifiedName
- listElementsWithNamespaceAndLocalName
- listElementsWithClassNames
- ~~insert_adjacent~~
- SetExistingAttributeValue
- replace_data
- ~~substring_data~~
- DetermineNodeLength
- ~~split_text_node~~
- ~~descendant_text_node~~
- ~~child_text_content~~
- ~~contiguous_exclusive_text_nodes~~
- ~~contiguous_text_nodes~~
- ~~check_exclusive_text_node~~
- StrictSplitText
- ~~string_replace_all~~
- replace_all
- replace
- remove_node
- move_all
- append_node
- scope_match_selectors_string
- ~~nodequals~~
- ~~position~~
- ~~static_range_valid~~
- ~~contained_in_range~~
- ~~partially_contained_in_range~~
- pre_remove_range - live range pre-remove steps
- ~~extract_range~~
- ~~insert_node_in_range~~
- ~~traverse_sibling~~
- ~~traverse_children~~
- ~~default_passive_value~~
- ~~retard~~

## Event
- Realm implementation in `inner_event_creation_steps` & `base.cpp` #JS
- Special event constructing steps for each specification in `inner_event_creation_steps` - **JUST A NOTE** #JS
- ~~Implementation of `relative_high_resolution_coarse_time` in `inner_event_creation_steps`~~

## CustomEvent

## EventTarget
- In algo for events, `default_passive_value` body element check after HTML work done. #HTML
- ~~Add `algo` for `add_event_listener`~~
- Service Worker Global Scope: #JS
    - add_event_listener
    - remove_event_listener
- Set `targetOverride` to target's `associatedDocument` in `dispatch_event` #HTML
- ~~Assert for `slot` check in `dispatch_event` after implementation of Slot~~
- ~~Implement check for **shadow-including inclusive ancestor** in `dispatch_event`~~
- After implementation of realm/global object, remember to complete `inner_invoke` func in `algos_events` #JS
- Relevant `realm` implementation with `eventConstructor` in `fire_event` in algos for events. #JS
- This `realm` boi implementation in `create_event` tooooo. #JS
- ~~Complete the `retard` function after shadow-inclusing ancestor.~~

## AbortController

## AbortSignal
- Mf global object to trouble again ! #HTML
- Current realm implementation in `_any` method #JS
- The same thing above in the creating #JS
- `onabort` implementation after HTML #HTML

## Mutation Algo's
- ~~`host-including inclusive ancestor` implementation, then for `ensure_pre_insert_validity`~~
- ~~Point 6 in `ensure_pre_insert_validity` after figuring out best way to find type of child.~~
- Next sibling stuff in `pre_insert_node`
- Insert node addition after implementation in `pre_insert_node`
- Doctype (others too) check in `ensure_pre_insert_validity`
- Some global way to have live ranges stored. Then implement in:
    - insert_node



## ParentNode
- To write definition after selector stuff:
    - Element* querySelector(DOMString selectors);
    - NodeList querySelectorAll(DOMString selectors);
- Constructor required boi

## Slottable
- Change type of `assignedSlot` from DOMString to `HTMLSlotElement` after HTML implementation. #HTML

## Node
- ~~Meaningfull virtual func -> abstract class~~
- ~~`getTheParent` algo~~
- `registered_observer_list` implementation
- `serialize` algo
- `baseURI` after node document's document base URI sorted after HTML implementation.
- `normalize()` - This is fucking tough !
- ~~`cloneNode()`~~
- ~~JS Work for equalAlgo - isEqualNode()~~
- ~~`compareDocumentPosition()`~~
- ~~tolower() to be made especially for ASCII~~
- Rewrites:
    - nodeType: all kids
    - nodeName: all kids
    - nodeValue: Attr, CharacteData
    - textContent: Attr, CharacterData, Element, DocumentFragment
    - cloneNode(): ShadowRoot
    - lookupPrefix(): all kids
- In `clone_a_single_node` algo, check for global custom element registry
- In `clone_a_single_node` algo, complete the custom element registry #HTML

## Document
- Opaque Origin #HTML
- `getTheParent` algo incomplete: browsing context & relevant global object
- `serialize` algo
- Constructor work to set origin to origin of current global object's `associated Doc` #HTML
- Resolve this in `createProcessingInstruction` for `Document` -> If target does not match the Name production
- Complete:
    - `createEvent()` #HTML
    - `createRange()` # After Range implementation
    - `createNodeIterator()` # After NodeIterator implementation
    - `createTreeWalker()` # After TreeWalker implementation
- is_scoped var in `flatten_element_creation_options` and in `importNode` #HTML
- looking up a custom element registry for `flatten_element_creation_options` and in `importNode` #HTML


## DOMImplementation
- Empty dict passing to internalCreateElementNS resolving !

## DocumentType

## DocumentFragment
- Define it's constructor using current global object value req #HTML

## ShadowRoot
- onslotchange attribute event handler

## Element
- customElementDefinition implementation #HTML
- ~~is value implementation #HTML~~
- ~~validCustomElementName #HTML~~
- ~~tagName getter steps with HTMLUpperCasedQualifiedName~~
- Complete CustomElementRegistry class !
- shadowRoot resolve with getter steps !
- Implement
    - ~~setAttribute()~~
    - ~~hasAttribute()~~
    - ~~toggleAttribute()~~
    - closest() #CSS
    - matches() #CSS
    - webkitMatchesSelector() #CSS
- ~~Implement `refect`~~
- create_element algo with #HTML
- `fetch_attribute` in HTML namespace #HTML
- getter method for classList after `DOMTokenList`
- HTML namespace check in `setAttribute` & `hasAttribute` && `toggleAttribute` #HTML
- is_scoped in `attachShadow` #HTML
- Custom stuff in `attach_shadow_root` algo in algos_docs.cpp #HTML

## NamedNodeMap
- supported property names

## Attr

## CharacterData
- Setter steps for data

## Text
- Constructor after figuring out current global object from Realm #HTML
- In `split_text_node`, complete after completing `Range`
- wholeText() implementation later after learning tree structure implementation

## ProcessingInstruction

## Comment
- Constructor after figuring out dude about current global object ! #HTML

## AbstractRange

## StaticRange

## Range
- Wtf is this `stringifier` ! check definition boi
- Constructor after figuring out dude about current global object ! #HTML
- `deleteContents()` - Implementation of nodes_to_remove
- clone children flag in `clone_contents` algo
- Text nodes contained in this range in tree order in `stringification_behavior`
- non-Text node is partially contained in range in `surroundContents` method

## NodeIterator
- `filter_node` method complete later
- `pre_remove_steps` complete
- Implement iterator collection
- After above step, complete `traverse` algo

## TreeWalker
- `filter_node` method complete later

## NodeFilter

## DOMTokenList
- Supported tokens resolve based on specifications in `validate()`