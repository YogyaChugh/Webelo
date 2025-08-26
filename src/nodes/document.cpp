#include "../../include/nodes/document.hpp"
#include "../../include/base.hpp"
#include "../include/exceptions.hpp"
#include <bits/stdc++.h>
#include <optional>


Node* convert_nodes_to_node(std::initializer_list<std::variant<Node,DOMString>> nodes, Document* ownerDocument) {
    Node* node = nullptr;
    for (size_t i = 0; i < nodes.size(); i++) {
        if (dynamic_cast<DOMString*>(nodes[i])) {
            nodes[i] = Text(nodes[i]);
            nodes[i].ownerDocument = ownerDocument;
        }
        else {
            node = &(nodes[0]);
        }
    }
    if (!node) {
        node = new DocumentFragment();
        node->ownerDocument = ownerDocument;
        for (auto a: nodes) {
            node
        }
    }
}


void ParentNode::prepend(std::initializer_list<std::variant<Node,DOMString>> nodes) {
    convert_nodes_to_node(nodes, ownerDocument);
}






// GOD KNOWS WHAT THIS DOES !!
// Docment::get_the_parent(Event* event) override{
//     if (event->type=="load"){
//         return nullptr
//     }
// }

Document::Document(): Node(DOCUMENT_NODE, "#document", nullptr, this, nullptr, nullptr){
    this->implementation->associated_doc = this;
};


std::optional<DOMString> Document::lookupPrefix(std::optional<DOMString> namesp){
    if (namesp==std::nullopt || namesp.value==""){ return std::nullopt; }
    if (this->documentElement()==nullptr){ return std::nullopt; }
    return locateNamespacePrefix(this->documentElement() , namesp);
}


DOMString Document::compatMode(){
    if (mode=="quirks"){
        return "BackCompat"
    }
    return "CSS1Compat"
}

DocumentType* Document::doctype(){
    for (size_t i=0;  i<this->childNodes.length(); i++){
        if (dynamic_cast<DocumentType*>(this->childNodes.item(i))){
            return this->childNodes.item(i);
        }
    }
    return nullptr;
}

HTMLCollection Document::getElementsByTagName(DOMString qualifiedName){
    return listElementsWithQualifiedName(this);
}

HTMLCollection Document::getElementsByTagNameNS(std::optional<DOMString> namesp, DOMString localname){
    return listElementsWithNamespaceAndLocalName(this);
}

HTMLCollection Document::getElementsByClassName(DOMString classNames){
    return listElementsWithClassNames(this);
}

Element Document::createElement(DOMString localName, std::variant<DOMString,ElementCreationOptions> options){
    if (!validElementLocalName(localName)){ throw InvalidCharacterError("Character Name invalid !!" + localName); }
    if (this->type!="xml"){
        std::transform(localName.begin(), localName.end(), localName.begin(), ::tolower());
    }
    CustomElementRegistry registry;
    DOMString is;
    std::optional<DOMString> namesp;
    flattenElementCreationOptions(options, this, registry, is);
    if (this->type!="xml" || this->contentType=="application/xhtml+xml"){
        namesp = "http://www.w3.org/1999/xhtml"
    }
    else{
        namesp = std::nullopt;
    }
    return CreateElement(this, localName, namesp, nullptr, is, true, registry);
}

Element Document::createElementNS(std::optional<DOMString> namesp, DOMString qualifiedName, std::variant<DOMString,ElementCreationOptions> options){
    return InternalCreateElementNS(this, namesp, qualifiedName, options);
}

DocumentFragment* Document::createDocumentFragment(){
    DocumentFragment* temp = new DocumentFragment();
    temp->nodeDocument = this;
    return temp;
}

Text* Document::createTextNode(DOMString data){
    Text* temp = new Text(data);
    temp->nodeDocument = this;
    return temp;
}

CDATASection* Document::createCDATASection(DOMString data){
    if (this->type!="xml"){ return NotSupportedError("Html Doc ain't supported !"); }
    if (data.find("]]>") != std::string::npos) { throw InvalidCharacterError("Invalid Characters !"); }
    CDATASection* temp = new CDATASection();
    temp->data = data;
    temp->nodeDocument = this;
}

Comment* Document::createComment(DOMString data){
    Comment* temp = new Comment(data);
    temp->nodeDocument = this;
    return temp;
}

ProcessingInstruction* Document::createProcessingInstruction(DOMString target, DOMString data){
    //TODO
    if (data.find("?>") != std::string::npos){ throw InvalidCharacterError("Invalid Characters !"); }
    ProcessingInstruction* temp = new ProcessingInstruction();
    temp->target = target;
    temp->data = data;
    temp->nodeDocument = this;
    return temp;
}

Node* Document::importNode(Node* node, std::variant<bool,ImportNodeOptions> options = false){
    if (dynamic_cast<Document*>(node) || dynamic_cast<ShadowRoot*>(node)){ throw NotSupportedError("Document and Shadow Root not supported !!"); }
    bool subtree = false;
    CustomElementRegistry* registry = nullptr;
    if (std::holds_alternative<bool>(options)){ subtree = options; }
    else{
        subtree = !options.selfOnly;
        if (options.customElementRegistry!=nullptr){ registry = options.customElementRegistry; }
        if (registry && registry->isscoped)
    }
    // if (registry == nullptr){
    //     registry = 
    // }
    //TODO: AFTER HTML STANDARD IMPLEMENTATION !!
    return cloneANode(node, this, subtree, registry);
}

Node* Document::adoptNode(Node* node){
    if (dynamic_cast<Document*>(node)){ throw NotSupportedError("Document ain't supported !"); }
    if (dynamic_cast<ShadowRoot*>(node)){ throw HeirarchyRequestError("IDK WHY THIS !!"); }
    if (dynamic_cast<DocumentFragment*>(node) && node->host!=nullptr){
        return nullptr;
    }
    AdoptAlgo(node, this);
    return node;
}

Attr* Document::createAttribute(DOMString localName){
    if (!validAttributeLocalName(localName)){ throw InvalidCharacterError("Invalid Attribute Name"); }
    if (this->type!="xml"){
        std::transform(localName.begin(), localName.end(), localName.begin(), ::tolower());
    }
    Attr* temp = new Attr();
    temp->localName = localName;
    temp->nodeDocument = this;
    return temp;
}

Attr* Document::createAttributeNS(std::optional<DOMString> namesp, DOMString qualifiedName){
    std::optional<DOMString> prefix;
    DOMString localName;
    ValidateAndExtract(namesp, qualifiedName, prefix, localName);
    Attr* temp = new Attr();
    temp->namespaceURI = namesp;
    temp->prefix = prefix;
    temp->nodeDocument = this;
    return temp;
}






DocumentType DOMImplementation::createDocumentType(DOMString name, DOMString publicId, DOMString systemId){
    if (!validDocTypeName(name)){ throw InvalidCharacterError("Invalid Chars !!"); }
    DocumentType* temp = new DocumentType(name, publicId, systemId);
    temp->nodeDocument = this->associated_doc;
    return temp
}

XMLDocument DOMImplementation::createDocument(std::optional<DOMString> namesp, DOMString qualifiedName, std::optional<DocumentType> doctype = std::nullopt){
    XMLDocument* document = new XMLDocument();
    Element* element = nullptr;
    if (qualifiedName!=""){
        element = InternalCreateElementNS(document, namesp, qualifiedName, {});
    }
    if (doctype!=std::nullopt){ preInsertNode(document, doctype, nullptr); }
    if (element!=nullptr){ preInsertNode(document, element, nullptr); }
    document->origin=this->associated_doc->origin;
    if (namesp.value=="http://www.w3.org/1999/xhtml"){
        document->contentType = "application/xhtml+xml";
    }
    elif (namesp.value=="http://www.w3.org/2000/svg"){
        document->contentType = "image/svg+xml";
    }
    else{
        document->contentType = "application/xml"
    }
    return document;
}

Document DOMImplementation::createHTMLDocument(std::optional<DOMString> title){
    Document* document = new Document();
    document->type = "html";
    document->contentType = "text/html"
    DocumentType* doct = new DocumentType("html");
    doct->nodeDocument = document;
    preInsertNode(document, doct, nullptr);
    Element* htmlElement = CreateElement(document, "html", "http://www.w3.org/1999/xhtml");
    preInsertNode(document, htmlElement, nullptr);
    Element* headElement = CreateElement(document, "head", "http://www.w3.org/1999/xhtml");
    preInsertNode(htmlElement, headElement, nullptr);
    if (title!=std::nullopt){
        Element* titleElement = CreateElement(document, "title", "http://www.w3.org/1999/xhtml");
        preInsertNode(headElement, titleElement, nullptr);
        Text* text = new Text(title.value);
        text->nodeDocument = document;
        preInsertNode(titleElement, text, nullptr);
    }
    preInsertNode(htmlElement, CreateElement(document, "body", "http://www.w3.org/1999/xhtml"));
    document->origin = this->associated_doc->origin;
    return document;
}



bool DOMImplementation::hasFeature(){ return true; }



Element* ShadowRoot::get_the_parent(Event* event) override{
    if (!event->composed_flag && event->path.at(0)!=event->path.end() && this==event->path.at(0)->invocation_target){
        return nullptr;
    }
    return this->associatedHost;
}



Element::Element(){
    attributes->associatedElement = this;
}


bool Element::hasAttributes(){
    if (this->attributes.attribute_list.size()==0){
        return false;
    }
    return true;
}

std::vector<DOMString> Element::getAttributeNames(){
    std::vector<DOMString> attribute_qualified_names = {};
    for (auto a: this->attributes.attribute_list){
        attribute_qualified_names.push_back(a->qualifiedName());
    }
    return attribute_qualified_names;
}


std::optional<DOMString> Element::getAttribute(DOMString qualifiedName){
    Attr* attr = FetchAttributeByName(qualifiedName, this);
    if (attr==nullptr){ return nullptr; }
    return attr->value;
}

std::optional<DOMString> Element::getAttributeNS(std::optional<DOMString> namesp, DOMString localName){
    Attr* attr = FetchAttributeByNamespaceAndLocalName(namesp, localName, this);
    if (attr==nullptr){ return nullptr; }
    return attr->value;
}


void Element::setAttribute(DOMString qualifiedName, DOMString value){
    if (!validAttributeLocalName(qualifiedName)){ throw InvalidCharacterError("Invalid name for attribute !!"); }
    //later !
}

void Element::setAttributeNS(std::optional<DOMString> namesp, DOMString qualifiedName, DOMString value){
    std::optional<DOMString> prefix;
    DOMString localName;
    ValidateAndExtract(namesp, qualifiedName, prefix, localName);
    SetAttributeValue(this, localName, value, prefix, namesp);
}

void Element::removeAttribute(DOMString qualifiedName){
    RemoveAttributeByName(qualifiedName, this);
}

void Element::removeAttributeNS(std::optional<DOMString> namesp, DOMString localName){
    RemoveAttributeByNamespaceAndLocalName(namesp, localName, this);
}

bool Element::hasAttribute(DOMString qualifiedName){
    //TODO
    return false;
}

bool Element::toggleAttribute(DOMString qualifiedName, bool force){
    if (!validAttributeLocalName(qualifiedName)){ throw InvalidCharacterError("Invalid Attribute Name boi !"); }
    //TODO
    return true;
}

bool Element::hasAttributeNS(std::optional<DOMString> namesp, DOMString localname){
    if (namesp.value==""){ namesp = std::nullopt; }
    for (auto a: attributes->attribute_list){
        if (a->namespaceURI==namesp && a->localName==localName){
            return true;
        }
    }
    return false;
}


std::optional<Attr> Element::getAttributeNode(DOMString qualifiedName){
    return FetchAttributeByName(qualifiedName, this);
}

std::optional<Attr> Element::getAttributeNodeNS(std::optional<DOMString> namesp, DOMString localName){
    return FetchAttributeByNamespaceAndLocalName(namesp, localName, this);
}

std::optional<Attr> Element::setAttributeNode(Attr attr){
    return SetAttribute(attr, this);
}

std::optional<Attr> Element::setAttributeNodeNS(Attr attr){
    return SetAttribute(attr, this);
}

Attr Element::removeAttributeNode(Attr attr){
    bool found = false;
    for (auto a: this->attributes->attribute_list){
        if (*a==attr){ found = true; }
    }
    if (!found){ throw NotFoundError("Attribute Not Found !"); }
    RemoveAttribute(attr);
    return attr;
}


ShadowRoot* Element::attachShadow(ShadowRootInit init){
    CustomElementRegistry* registry = this->customElementRegistry;
    if (init.customElementRegistry!=nullptr){
        registry = init.customElementRegistry;
        if (registry.is_scoped==false && registry!=this->nodeDocument->customElementRegistry){ throw NotSupportedError("This ain't supported !"); }
    }
    AttachShadowRoot(this, init.mode, init.clonable, init.serializable, init.delegatesFocus, init.slotAssignment, registry);
    return this->shadow_root;
}


std::optional<Element> Element::insertAdjacentElement(DOMString where, Element element){
    return InsertAdjacent(this, where, element);
}

void Element::insertAdjacentText(DOMString where, DOMString data){
    Text* text = new Text(data);
    text->nodeDocument = this->nodeDocument;
    InsertAdjacent(this, where, text);
}



std::optional<Attr> NamedNodeMap::item(unsigned long index){
    try {
        return attribute_list.at(index);
    }
    catch (const std::out_of_range&) {
        return nullptr;
    }
}


unsigned long NamedNodeMap::length(){
    return attribute_list.size();
}

std::optional<Attr> NamedNodeMap::getNamedItem(DOMString qualifiedName){
    return FetchAttributeByName(qualifiedName, associatedElement);
}

std::optional<Attr> NamedNodeMap::getNamedItemNS(std::optional<DOMString> namesp, DOMString localName){
    return FetchAttributeByNamespaceAndLocalName(namesp, localName, associatedElement);
}

std::optional<Attr> NamedNodeMap::setNamedItem(Attr attr){
    return SetAttribute(attr, associatedElement);
}

std::optional<Attr> NamedNodeMap::setNamedItemNS(Attr attr){
    return SetAttribute(attr, associatedElement);
}

Attr NamedNodeMap::removeNamedItem(DOMString qualifiedName){
    Attr* attr = RemoveAttributeByName(qualifiedName, associatedElement);
    if (attr==nullptr){ throw NotFoundError("Attribute not found !!"); }
    return attr;
}

Attr removeNamedItemNS(std::optional<DOMString> namesp, DOMString localName){
    Attr* attr = RemoveAttributeByNamespaceAndLocalName(namesp, localName, associatedElement);
    if (attr==nullptr){ throw NotFoundError("Attribute not found !!"); }
    return attr;
}




DOMString Attr::qualifiedName(){
    if (this->prefix==std::nullopt){
        return this->localName;
    }
    return this->prefix + ":" + this->localName;
}

Attr::Attr(DOMString localName){
    this->localName = localName;
    this->name = this->qualifiedName();
}



unsigned long CharacterData::length(){
    return this->data.length();
}

DOMString CharacterData::substringData(unsigned long offset, unsigned long count){
    return SubstringData(this, offset, count);
}

void CharacterData::appendData(DOMString data){
    return ReplaceDataNode(this, this->length(), 0, data);
}

void CharacterData::insertData(unsigned long offset, DOMString data){
    return ReplaceDataNode(this, offset, 0, data);
}

void CharacterData::deleteData(unsigned long offset, unsigned long count){
    return ReplaceDataNode(this, offset, count, "");
}

void CharacterData::replaceData(unsigned long offset, unsigned long count, DOMString data){
    return ReplaceDatNode(this, offset, count, data);
}




Text splitText(unsigned long offset){
    return SplitTextNode(this, offset);
}