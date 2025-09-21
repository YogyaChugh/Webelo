#include "base.cpp"
#include "nodes/document.hpp"
#include "exceptions.cpp"
#include "algos_node.cpp"
#include "algos_docs.cpp"
#include "algos_base.cpp"
#include <bits/stdc++.h>
#include <optional>


void ParentNode::prepend(std::vector<std::variant<Node*, DOMString>> &nodes) {
    Node* temp = convert_nodes_to_node(nodes, this->nodeDocument);
    pre_insert_node(temp, this, this->firstChild());
}

void ParentNode::append(std::vector<std::variant<Node*, DOMString>> &nodes){
    Node* temp = convert_nodes_to_node(nodes, this->nodeDocument);
    pre_insert_node(temp, this, nullptr);
}

void ParentNode::replaceChildren(std::vector<std::variant<Node*, DOMString>> &nodes){
    Node* temp = convert_nodes_to_node(nodes, this->nodeDocument);
    ensure_pre_insert_validity(temp, this, nullptr);
    replace_all(temp, this);
}

void ParentNode::moveBefore(Node* node, Node* child){
    Node* referenceChild = child;
    if (*referenceChild == *node){
        referenceChild = node->nextSibling();
    }
    move_node(node, this, referenceChild);
}






Element* Element::previousElementSibling() const{
    Node* prev = this->previousSibling();
    while (prev){
        if (dynamic_cast<Element*>(prev)){
            return prev;
        }
        prev = prev->previousSibling();
    }
    return nullptr;
}

Element* Element::nextElementSibling() const{
    Node* next = this->nextSibling();
    while (next){
        if (dynamic_cast<Element*>(next)){
            return next;
        }
        next = next->nextSibling();
    }
    return nullptr;
}

Element* CharacterData::previousElementSibling() const{
    Node* prev = this->previousSibling();
    while (prev){
        if (dynamic_cast<Element*>(prev)){
            return prev;
        }
        prev = prev->previousSibling();
    }
    return nullptr;
}

Element* CharacterData::nextElementSibling() const{
    Node* next = this->nextSibling();
    while (next){
        if (dynamic_cast<Element*>(next)){
            return next;
        }
        next = next->nextSibling();
    }
    return nullptr;
}





void before(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj){
    Node* parent = this->parentNode;
    if (parent==nullptr){return;}
    Node* viablePreviousSibling = nullptr;
    Node* prev = this->previousSibling();
    bool found = false;
    while (prev){
        for (auto a: nodes){
            if (std::holds_alternative<Node*>(a)){
                if (*(std::get<Node*>(a))==prev){
                    found = true;
                    break;
                }
            }
        }
        if (!found){
            viablePreviousSibling = prev;
            break;
        }
        prev = prev->previousSibling();
        found = false;
    }
    Node* node = convert_nodes_to_node(nodes, this->nodeDocument);
    if (viablePreviousSibling==nullptr){
        viablePreviousSibling = parent->firstChild();
    }
    else{
        viablePreviousSibling = viablePreviousSibling->nextSibling();
    }
    pre_insert_node(node, parent, viablePreviousSibling);
}


void after(std::vector<std::variant<Node*, DOMString>>& nodes, const Node* obj){
    Node* parent = this->parentNode;
    if (parent==nullptr){return;}
    Node* viableNextSibling = nullptr;
    Node* next = this->nextSibling();
    bool found = false;
    while (next){
        for (auto a: nodes){
            if (std::holds_alternative<Node*>(a)){
                if (*(std::get<Node*>(a))==next){
                    found = true;
                    break;
                }
            }
        }
        if (!found){
            viableNextSibling = next;
            break;
        }
        next = next->nextSibling();
        found = false;
    }
    Node* node = convert_nodes_to_node(nodes, this->nodeDocument);
    pre_insert_node(node, parent, viableNextSibling);
}

void replaceWith(std::vector<std::variant<Node*, DOMString>> &nodes, const Node* obj){
    Node* parent = this->parentNode;
    if (parent==nullptr){return;}
    Node* viableNextSibling = nullptr;
    Node* next = this->nextSibling();
    bool found = false;
    while (next){
        for (auto a: nodes){
            if (std::holds_alternative<Node*>(a)){
                if (*(std::get<Node*>(a))==next){
                    found = true;
                    break;
                }
            }
        }
        if (!found){
            viableNextSibling = next;
            break;
        }
        next = next->nextSibling();
        found = false;q 
    }
    Node* node = convert_nodes_to_node(nodes, this->nodeDocument);
    if (*this->parent==*parent){
        replace(this, node, parent);
    }
    else{
        pre_insert_node(node, parent, viableNextSibling);
    }
}

void remove(Node* obj){
    if (obj->parentNode==nullptr){return;}
    remove_node(obj);
}



















Document::Document(Document* ownerdoc = nullptr, Node* parentnode = nullptr): ParentNode(DOCUMENT_NODE, "#document", ownerdoc, parentnode){
    this->implementation->associated_doc = this;
};


std::optional<DOMString> Document::lookupPrefix(std::optional<DOMString> namesp){
    if (namesp==std::nullopt || namesp.value()==""){ return std::nullopt; }
    if (this->documentElement()==nullptr){ return std::nullopt; }
    return locate_a_namespace_prefix(this->documentElement() , namesp);
}


DOMString Document::compatMode(){
    if (this->mode==QUIRKS){
        return "BackCompat"
    }
    return "CSS1Compat"
}

DocumentType* Document::doctype(){
    for (size_t i=0;  i<this->childNodes.length(); i++){
        DocumentType* temp = dynamic_cast<DocumentType*>(this->childNodes[i]);
        if (temp){
            return temp;
        }
    }
    return nullptr;
}

Element* Document::documentElement(){
    for (size_t i=0;  i<this->childNodes.length(); i++){
        Element* temp = dynamic_cast<Element*>(this->childNodes[i]);
        if (temp){
            return temp;
        }
    }
    return nullptr;
}



HTMLCollection Document::getElementsByTagName(DOMString qualifiedName){
    return list_of_elements(qualifiedName, this);
}

HTMLCollection Document::getElementsByTagNameNS(std::optional<DOMString> namesp, DOMString localname){
    return list_of_elements(namesp, localname, this);
}

HTMLCollection Document::getElementsByClassName(std::vector<DOMString> &classNames){
    return list_of_elements(classNames, this);
}

Element* Document::createElement(DOMString localName, std::variant<DOMString,ElementCreationOptions> options){
    if (!validElementLocalName(localName)){ throw InvalidCharacterError("Character Name invalid !!"); }
    if (this->type!=XML){
        std::transform(localName.begin(), localName.end(), localName.begin(), [](unsigned char c){ return std::tolower(c); });
    }
    CustomElementRegistry* registry;
    std::optional<DOMString> is;
    std::optional<DOMString> namesp;
    flatten_element_creation_options(options, this, registry, is);
    if (this->type!=XML || this->contentType=="application/xhtml+xml"){
        namesp = "http://www.w3.org/1999/xhtml"
    }
    else{
        namesp = std::nullopt;
    }
    return create_element(this, localName, namesp, nullptr, is, true, registry);
}

Element* Document::createElementNS(std::optional<DOMString> namesp, DOMString qualifiedName, std::variant<DOMString,ElementCreationOptions> options){
    return internal_create_element_ns(this, namesp, qualifiedName, options);
}

DocumentFragment* Document::createDocumentFragment(){
    DocumentFragment* temp = new DocumentFragment();
    temp->ownerDocument = this;
    return temp;
}

Text* Document::createTextNode(DOMString data){
    Text* temp = new Text(data);
    temp->ownerDocument = this;
    return temp;
}

CDATASection* Document::createCDATASection(DOMString data){
    if (this->type!=XML){ throw NotSupportedError("Html Doc ain't supported !"); }
    if (data.find("]]>") != std::string::npos) { throw InvalidCharacterError("Invalid Characters !"); }
    CDATASection* temp = new CDATASection();
    temp->data = data;
    temp->ownerDocument = this;
    return temp;
}

Comment* Document::createComment(DOMString data){
    Comment* temp = new Comment(data);
    temp->ownerDocument = this;
    return temp;
}

ProcessingInstruction* Document::createProcessingInstruction(DOMString target, DOMString data){
    // If target doesn't match some Name production, throw InvalidCharacterError exception
    if (data.find("?>") != std::string::npos){ throw InvalidCharacterError("Invalid Characters !"); }
    ProcessingInstruction* temp = new ProcessingInstruction();
    temp->target = target;
    temp->data = data;
    temp->ownerDocument = this;
    return temp;
}

Node* Document::importNode(Node* node, std::variant<bool,ImportNodeOptions> options = false){
    if (dynamic_cast<Document*>(node) || dynamic_cast<ShadowRoot*>(node)){ throw NotSupportedError("Document and Shadow Root not supported !!"); }
    bool subtree = false;
    CustomElementRegistry* registry = nullptr;
    if (std::holds_alternative<bool>(options)){ subtree = std::get<bool>(options); }
    else{
        ImportNodeOptions temp = std::get<ImportNodeOptions>(options);
        subtree = !temp.selfOnly;
        if (temp.customElementRegistry!=nullptr){ registry = temp.customElementRegistry; }
        if (registry && registry!=this->custom_element_registry){ throw NotSupportedError("NOT SUPPORTED :) !"); }
    }
    return clone_node(node, this, subtree, nullptr, registry);
}

Node* Document::adoptNode(Node* node){
    if (dynamic_cast<Document*>(node)){ throw NotSupportedError("Document ain't supported !"); }
    if (dynamic_cast<ShadowRoot*>(node)){ throw HeirarchyRequestError("IDK WHY THIS !!"); }
    DocumentFragment* temp = dynamic_cast<DocumentFragment*>(node);
    if (temp && temp->associatedHost!=nullptr){
        return nullptr;
    }
    adopt(node, this);
    return node;
}

Attr* Document::createAttribute(DOMString localName){
    if (!ValidAttributeLocalName(localName)){ throw InvalidCharacterError("Invalid Attribute Name"); }
    if (this->type!=XML){
        std::transform(localName.begin(), localName.end(), localName.begin(), [](unsigned char c){ return std::tolower(c); });
    }
    Attr* temp = new Attr(localName);
    temp->ownerDocument = this;
    return temp;
}

Attr* Document::createAttributeNS(std::optional<DOMString> namesp, DOMString qualifiedName){
    std::optional<DOMString> prefix;
    DOMString localName;
    ValidateAndExtract(namesp, qualifiedName, "attribute",prefix, localName);
    Attr* temp = new Attr(localName);
    temp->namespaceURI = namesp;
    temp->prefix = prefix;
    temp->ownerDocument = this;
    return temp;
}

Event* Document::createEvent(DOMString interface){
    Event* constructor = nullptr;
    if (constructor==nullptr){
        throw NotSupportedError("Not supported :)) !!");
    }
}

Range* createRange(){
    Range* temp = new Range();
    return temp;
}

NodeIterator* createNodeIterator(Node* root, unsigned long whatToShow, NodeFilter* filter){
    NodeIterator* iterator = new NodeIterator();
    return iterator;
}

TreeWalker* createTreeWalker(Node* root, unsigned long whatToShow, NodeFilter* filter){
    TreeWalker* walker = new TreeWalker();
    return walker;
}



DocumentType* DOMImplementation::createDocumentType(DOMString name, DOMString publicId, DOMString systemId){
    if (!validDocTypeName(name)){ throw InvalidCharacterError("Invalid Chars !!"); }
    DocumentType* temp = new DocumentType(name, publicId, systemId);
    temp->ownerDocument = this->associated_doc;
    return temp;
}

XMLDocument* DOMImplementation::createDocument(std::optional<DOMString> namesp, DOMString qualifiedName, std::optional<DocumentType> doctype = std::nullopt){
    XMLDocument* document = new XMLDocument();
    Element* element = nullptr;
    if (qualifiedName!=""){
        element = internal_create_element_ns(dynamic_cast<Document*>(document), namesp, qualifiedName, ElementCreationOptions());
    }
    if (doctype.has_value()){ pre_insert_node(document, dynamic_cast<Node*>(doctype.value()), nullptr); }
    if (element!=nullptr){ pre_insert_node(document, element, nullptr); }
    document->origin=this->associated_doc->origin;
    if (namesp.value()=="http://www.w3.org/1999/xhtml"){
        document->contentType = "application/xhtml+xml";
    }
    else if (namesp.value()=="http://www.w3.org/2000/svg"){
        document->contentType = "image/svg+xml";
    }
    else{
        document->contentType = "application/xml";
    }
    return document;
}

Document* DOMImplementation::createHTMLDocument(std::optional<DOMString> title){
    Document* document = new Document();
    document->type = HTML;
    document->contentType = "text/html";
    DocumentType* doct = new DocumentType("html");
    doct->ownerDocument = document;
    pre_insert_node(document, doct, nullptr);
    Element* htmlElement = create_element(document, "html", "http://www.w3.org/1999/xhtml");
    pre_insert_node(document, htmlElement, nullptr);
    Element* headElement = create_element(document, "head", "http://www.w3.org/1999/xhtml");
    pre_insert_node(htmlElement, headElement, nullptr);
    if (title!=std::nullopt){
        Element* titleElement = create_element(document, "title", "http://www.w3.org/1999/xhtml");
        pre_insert_node(headElement, titleElement, nullptr);
        Text* text = new Text(title.value());
        text->ownerDocument = document;
        pre_insert_node(titleElement, text, nullptr);
    }
    pre_insert_node(htmlElement, create_element(document, "body", "http://www.w3.org/1999/xhtml"));
    document->origin = this->associated_doc->origin;
    return document;
}



bool DOMImplementation::hasFeature(){ return true; }



Element* ShadowRoot::get_the_parent(Event* event){
    if (!event->composed_flag && !event->path.empty() && this == event->path.at(0).invocation_target){
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
    ValidateAndExtract(namesp, qualifiedName, "element", prefix, localName);
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