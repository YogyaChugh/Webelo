# TODO'S

## GLOBAL TODO'S
- Comment Sorting
- Resolve Header Files
- Private/Public Resolve
- CEReactions ?
- NewObject, SameObject
- This setter/getter resolving !
- There could be a problem in the future with null character cause it's \0 and also end of string ! So just noting it down !!

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

## Events
- Realm implementation in `inner_event_creation_steps` & `base.cpp`
- Special event constructing steps for each specification in `inner_event_creation_steps` - **JUST A NOTE**
- Implementation of `relative_high_resolution_coarse_time` in `inner_event_creation_steps`

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
- Constructor work to set origin to origin of current global object's associated Doc #HTML
- Resolve this in createProcessingInstruction for Document -> If target does not match the Name production
- Step 3 in otherwise for importNode() in Document !! After CustomElementRegistry implementation :)
- Complete:
    - createEvent()
    - createRange()
    - createNodeIterator()
    - createTreeWalker()


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