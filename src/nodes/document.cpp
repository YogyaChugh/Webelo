#include "../base.cpp"
#include "../include/nodes/document.hpp"
#include "../exceptions.cpp"
#include "../algos/algos_node.cpp"
#include "../algos/algos_docs.cpp"
#include "../algos/algos_base.cpp"
#include "../algos/basic.cpp"
#include "../algos/mutation_algos.cpp"
#include <optional>



void ParentNode::prepend(std::vector<std::variant<Node*, DOMString>> &nodes) {
    Node* temp = convert_nodes_to_node(nodes, this->ownerDocument);
    auto smth = dynamic_cast<Node*>(this);
    pre_insert_node(temp, dynamic_cast<Node*>(this), smth->firstChild());
}

void ParentNode::append(std::vector<std::variant<Node*, DOMString>> &nodes){
    Node* temp = convert_nodes_to_node(nodes, this->ownerDocument);
    pre_insert_node(temp, dynamic_cast<Node*>(this), nullptr);
}

void ParentNode::replaceChildren(std::vector<std::variant<Node*, DOMString>> &nodes){
    Node* temp = convert_nodes_to_node(nodes, this->ownerDocument);
    ensure_pre_insert_validity(temp, dynamic_cast<Node*>(this), nullptr);
    replace_all(temp, dynamic_cast<Node*>(this));
}

void ParentNode::moveBefore(Node* node, Node* child){
    Node* referenceChild = child;
    if (*referenceChild == *node){
        referenceChild = node->nextSibling();
    }
    move_node(node, dynamic_cast<Node*>(this), referenceChild);
}






Element* Element::previousElementSibling(){
    auto smth = dynamic_cast<Node*>(this);
    Node* prev = smth->previousSibling();
    while (prev){
        auto bro = dynamic_cast<Element*>(prev);
        if (bro){
            return bro;
        }
        prev = prev->previousSibling();
    }
    return nullptr;
}

Element* Element::nextElementSibling(){
    auto smth = dynamic_cast<Node*>(this);
    Node* next = smth->nextSibling();
    while (next){
        auto bro = dynamic_cast<Element*>(next);
        if (bro){
            return bro;
        }
        next = next->nextSibling();
    }
    return nullptr;
}

Element* CharacterData::previousElementSibling(){
    auto smth = dynamic_cast<Node*>(this);
    Node* prev = smth->previousSibling();
    while (prev){
        if (dynamic_cast<Element*>(prev)){
            return dynamic_cast<Element*>(prev);
        }
        prev = prev->previousSibling();
    }
    return nullptr;
}

Element* CharacterData::nextElementSibling(){
    auto smth = dynamic_cast<Node*>(this);
    Node* next = smth->nextSibling();
    while (next){
        if (dynamic_cast<Element*>(next)){
            return dynamic_cast<Element*>(next);
        }
        next = next->nextSibling();
    }
    return nullptr;
}





void before(std::vector<std::variant<Node*, DOMString>> &nodes, Node* obj){
    Node* parent = obj->parentNode;
    if (parent==nullptr){return;}
    Node* viablePreviousSibling = nullptr;
    Node* prev = obj->previousSibling();
    bool found = false;
    while (prev){
        for (auto a: nodes){
            if (std::holds_alternative<Node*>(a)){
                if (std::get<Node*>(a)->isEqualNode(prev)){
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
    Node* node = convert_nodes_to_node(nodes, obj->ownerDocument);
    if (viablePreviousSibling==nullptr){
        viablePreviousSibling = parent->firstChild();
    }
    else{
        viablePreviousSibling = viablePreviousSibling->nextSibling();
    }
    pre_insert_node(node, parent, viablePreviousSibling);
}


void after(std::vector<std::variant<Node*, DOMString>>& nodes, Node* obj){
    Node* parent = obj->parentNode;
    if (parent==nullptr){return;}
    Node* viableNextSibling = nullptr;
    Node* next = obj->nextSibling();
    bool found = false;
    while (next){
        for (auto a: nodes){
            if (std::holds_alternative<Node*>(a)){
                if (std::get<Node*>(a)->isEqualNode(next)){
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
    Node* node = convert_nodes_to_node(nodes, obj->ownerDocument);
    pre_insert_node(node, parent, viableNextSibling);
}

void replaceWith(std::vector<std::variant<Node*, DOMString>> &nodes, Node* obj){
    Node* parent = obj->parentNode;
    if (parent==nullptr){return;}
    Node* viableNextSibling = nullptr;
    Node* next = obj->nextSibling();
    bool found = false;
    while (next){
        for (auto a: nodes){
            if (std::holds_alternative<Node*>(a)){
                if (std::get<Node*>(a)->isEqualNode(next)){
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
    Node* node = convert_nodes_to_node(nodes, obj->ownerDocument);
    if (*obj->parentNode==*parent){
        replace(obj, node, parent);
    }
    else{
        pre_insert_node(node, parent, viableNextSibling);
    }
}

void remove(Node* obj){
    if (obj->parentNode==nullptr){return;}
    remove_node(obj);
}
















std::optional<DOMString> Document::lookupPrefix(std::optional<DOMString> namesp){
    if (namesp==std::nullopt || namesp.value()==""){ return std::nullopt; }
    if (this->documentElement()==nullptr){ return std::nullopt; }
    return locate_a_namespace_prefix(this->documentElement() , namesp);
}


DOMString Document::compatMode(){
    if (this->mode==QUIRKS){
        return "BackCompat";
    }
    return "CSS1Compat";
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
    return list_of_elements(qualifiedName, dynamic_cast<Node*>(this));
}

HTMLCollection Document::getElementsByTagNameNS(std::optional<DOMString> namesp, DOMString localname){
    return list_of_elements(namesp, localname, dynamic_cast<Node*>(this));
}

HTMLCollection Document::getElementsByClassName(std::vector<DOMString> &classNames){
    return list_of_elements(classNames, dynamic_cast<Node*>(this));
}

Element* Document::createElement(DOMString localName, std::variant<DOMString,ElementCreationOptions> options){
    if (!valid_element_local_name(localName)){ throw InvalidCharacterError("Character Name invalid !!"); }
    if (this->type!=XML){
        std::transform(localName.begin(), localName.end(), localName.begin(), [](unsigned char c){ return std::tolower(c); });
    }
    CustomElementRegistry* registry;
    std::optional<DOMString> is;
    std::optional<DOMString> namesp;
    flatten_element_creation_options(options, this, registry, is);
    if (this->type!=XML || this->contentType=="application/xhtml+xml"){
        namesp = "http://www.w3.org/1999/xhtml";
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
    temp->setdata(data);
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
    temp->setdata(data);
    temp->ownerDocument = this;
    return temp;
}

Node* Document::importNode(Node* node, std::variant<bool,ImportNodeOptions> options){
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
    if (!valid_attribute_local_name(localName)){ throw InvalidCharacterError("Invalid Attribute Name"); }
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
    validate_and_extract(namesp, qualifiedName, "attribute",prefix, localName);
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
	return constructor;
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
    if (!valid_doctype_name(name)){ throw InvalidCharacterError("Invalid Chars !!"); }
    DocumentType* temp = new DocumentType(name, publicId, systemId);
    temp->ownerDocument = this->associated_doc;
    return temp;
}

XMLDocument* DOMImplementation::createDocument(std::optional<DOMString> namesp, DOMString qualifiedName, std::optional<DocumentType> doctype){
    XMLDocument* document = new XMLDocument();
    Element* element = nullptr;
    if (qualifiedName!=""){
        element = internal_create_element_ns(dynamic_cast<Document*>(document), namesp, qualifiedName, ElementCreationOptions());
    }
    if (doctype.has_value()){ pre_insert_node(dynamic_cast<Node*>(document), dynamic_cast<Node*>(&doctype.value()), nullptr); }
    if (element!=nullptr){ pre_insert_node(dynamic_cast<Node*>(document), dynamic_cast<Node*>(element), nullptr); }
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
    pre_insert_node(dynamic_cast<Node*>(document), dynamic_cast<Node*>(doct), nullptr);
    Element* htmlElement = create_element(document, "html", "http://www.w3.org/1999/xhtml", nullptr);
    pre_insert_node(dynamic_cast<Node*>(document), dynamic_cast<Node*>(htmlElement), nullptr);
    Element* headElement = create_element(document, "head", "http://www.w3.org/1999/xhtml", nullptr);
    pre_insert_node(dynamic_cast<Node*>(htmlElement), dynamic_cast<Node*>(headElement), nullptr);
    if (title!=std::nullopt){
        Element* titleElement = create_element(document, "title", "http://www.w3.org/1999/xhtml", nullptr);
        pre_insert_node(dynamic_cast<Node*>(headElement), dynamic_cast<Node*>(titleElement), nullptr);
        Text* text = new Text(title.value());
        text->ownerDocument = document;
        pre_insert_node(dynamic_cast<Node*>(titleElement), dynamic_cast<Node*>(text), nullptr);
    }
    pre_insert_node(dynamic_cast<Node*>(htmlElement), dynamic_cast<Node*>(create_element(document, "body", "http://www.w3.org/1999/xhtml")), nullptr);
    document->origin = this->associated_doc->origin;
    return document;
}



bool DOMImplementation::hasFeature(){ return true; }




bool Element::hasAttributes(){
    if (this->attributes.attribute_list.size()==0){
        return false;
    }
    return true;
}

std::vector<DOMString> Element::getAttributeNames(){
    std::vector<DOMString> attribute_qualified_names = {};
    for (auto a: this->attributes.attribute_list){
        if (a->prefix==std::nullopt){
            attribute_qualified_names.push_back(a->localName);
        }
        else{
            attribute_qualified_names.push_back(a->prefix.value() + ":" + a->localName);
        }
    }
    return attribute_qualified_names;
}


std::optional<DOMString> Element::getAttribute(DOMString qualifiedName){
    Attr* attr = fetch_attribute(qualifiedName, this);
    if (attr==nullptr){ return std::nullopt; }
    return attr->value;
}

std::optional<DOMString> Element::getAttributeNS(std::optional<DOMString> namesp, DOMString localName){
    Attr* attr = fetch_attribute(namesp, localName, this);
    if (attr==nullptr){ return std::nullopt; }
    return attr->value;
}


void Element::setAttribute(DOMString qualifiedName, DOMString value){
    if (!valid_attribute_local_name(qualifiedName)){ throw InvalidCharacterError("Invalid name for attribute !!"); }
    //later !
    if (this->ownerDocument->type!=XML){
        std::transform(qualifiedName.begin(), qualifiedName.end(), qualifiedName.begin(), [](unsigned char c){ return std::tolower(c); });
    }
    Attr* attribute = nullptr;
    for (auto attr: this->attributes.attribute_list){
        DOMString qualif;
        if (attr->prefix == std::nullopt){
            qualif = attr->localName;
        }
        else{
            qualif = attr->prefix.value() + ":" + attr->localName;
        }
        if (qualif==qualifiedName){
            attribute = attr;
            break;
        }
    }
    if (attribute==nullptr){
        Attr* temp = new Attr(qualifiedName);
        temp->value = value;
        temp->ownerDocument = this->ownerDocument;
        append_attribute(temp, this);
        return;
    }
    change_attribute_value(attribute, value);
}

void Element::setAttributeNS(std::optional<DOMString> namesp, DOMString qualifiedName, DOMString value){
    std::optional<DOMString> prefix;
    DOMString localName;
    validate_and_extract(namesp, qualifiedName, "element", prefix, localName);
    set_attribute_value(this, localName, value, prefix, namesp);
}

void Element::removeAttribute(DOMString qualifiedName){
    remove_attribute_by_name(qualifiedName, this);
}

void Element::removeAttributeNS(std::optional<DOMString> namesp, DOMString localName){
    remove_attribute_by_namespace(namesp, localName, this);
}


bool Element::hasAttribute(DOMString qualifiedName){
    if (this->ownerDocument->type!=XML){
        std::transform(qualifiedName.begin(), qualifiedName.end(), qualifiedName.begin(), [](unsigned char c){ return std::tolower(c); });
    }
    for (auto attr: this->attributes.attribute_list){
        DOMString qualif;
        if (attr->prefix == std::nullopt){
            qualif = attr->localName;
        }
        else{
            qualif = attr->prefix.value() + ":" + attr->localName;
        }
        if (qualif==qualifiedName){
            return true;
        }
    }
    return false;
}

bool Element::toggleAttribute(DOMString qualifiedName, std::optional<bool> force){
    if (!valid_attribute_local_name(qualifiedName)){ throw InvalidCharacterError("Invalid Attribute Name boi !"); }
    if (this->ownerDocument->type!=XML){
        std::transform(qualifiedName.begin(), qualifiedName.end(), qualifiedName.begin(), [](unsigned char c){ return std::tolower(c); });
    }
    Attr* attribute = nullptr;
    for (auto attr: this->attributes.attribute_list){
        DOMString qualif;
        if (attr->prefix == std::nullopt){
            qualif = attr->localName;
        }
        else{
            qualif = attr->prefix.value() + ":" + attr->localName;
        }
        if (qualif==qualifiedName){
            attribute = attr;
            break;
        }
    }
    if (attribute==nullptr){
        if (!force.has_value() || (force.has_value() && force.value()==true)){
            Attr* temp = new Attr(qualifiedName);
            temp->value = "";
            temp->ownerDocument = this->ownerDocument;
            append_attribute(temp, this);
            return true;
        }
        return false;
    }
    if (!force.has_value() || (force.has_value() && force.value()==false)){
        remove_attribute_by_name(qualifiedName, this);
        return false;
    }
    return true;
}

bool Element::hasAttributeNS(std::optional<DOMString> namesp, DOMString localname){
    if (namesp.has_value() && namesp.value()==""){ namesp = std::nullopt; }
    for (auto a: this->attributes.attribute_list){
        if (a->namespaceURI==namesp && a->localName==localName){
            return true;
        }
    }
    return false;
}


Attr* Element::getAttributeNode(DOMString qualifiedName){
    return fetch_attribute(qualifiedName, this);
}

Attr* Element::getAttributeNodeNS(std::optional<DOMString> namesp, DOMString localName){
    return fetch_attribute(namesp, localName, this);
}

Attr* Element::setAttributeNode(Attr* attr){
    return set_attribute(attr, this);
}

Attr* Element::setAttributeNodeNS(Attr* attr){
    return set_attribute(attr, this);
}

Attr* Element::removeAttributeNode(Attr* attr){
    bool found = false;
    for (auto a: this->attributes.attribute_list){
        if (a==attr){ found = true; }
    }
    if (!found){ throw NotFoundError("Attribute Not Found !"); }
    remove_attribute(attr);
    return attr;
}


ShadowRoot* Element::attachShadow(ShadowRootInit init){
    CustomElementRegistry* registry = this->customElementRegistry;
    if (init.customElementRegistry!=nullptr){
        registry = init.customElementRegistry;
        if (registry!=this->ownerDocument->custom_element_registry){ throw NotSupportedError("This ain't supported !"); }
    }
    attach_shadow_root(this, init.mode, init.clonable, init.serializable, init.delegatesFocus, init.slotAssignment, *registry);
    return this->getshadow_root();
}

Element* Element::insertAdjacentElement(DOMString where, Element element){
    return dynamic_cast<Element*>(insert_adjacent(this, where, dynamic_cast<Node*>(element)));
}

void Element::insertAdjacentText(DOMString where, DOMString data){
    Text* text = new Text(data);
    text->ownerDocument = this->ownerDocument;
    insert_adjacent(this, where, dynamic_cast<Node*>(text));
}

HTMLCollection Element::getElementsByTagName(DOMString qualifiedName){
    return list_of_elements(qualifiedName, dynamic_cast<Node*>(this));
}

HTMLCollection Element::getElementsByTagNameNS(std::optional<DOMString> namesp, DOMString localName){
    return list_of_elements(namesp, localName, dynamic_cast<Node*>(this));
}

HTMLCollection Element::getElementsByClassName(DOMString classNames){
    return list_of_elements(classNames, dynamic_cast<Node*>(this));
}



Attr* NamedNodeMap::item(unsigned long index){
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

Attr* NamedNodeMap::getNamedItem(DOMString qualifiedName){
    return fetch_attribute(qualifiedName, this->associatedElement);
}

Attr* NamedNodeMap::getNamedItemNS(std::optional<DOMString> namesp, DOMString localName){
    return fetch_attribute(namesp, localName, this->associatedElement);
}

Attr* NamedNodeMap::setNamedItem(Attr* attr){
    return set_attribute(attr, this->associatedElement);
}

Attr* NamedNodeMap::setNamedItemNS(Attr* attr){
    return set_attribute(attr, this->associatedElement);
}

Attr* NamedNodeMap::removeNamedItem(DOMString qualifiedName){
    Attr* attr = remove_attribute_by_name(qualifiedName, this->associatedElement);
    if (attr==nullptr){ throw NotFoundError("Attribute not found !!"); }
    return attr;
}

Attr* NamedNodeMap::removeNamedItemNS(std::optional<DOMString> namesp, DOMString localName){
    Attr* attr = remove_attribute_by_namespace(namesp, localName, this->associatedElement);
    if (attr==nullptr){ throw NotFoundError("Attribute not found !!"); }
    return attr;
}




DOMString Attr::qualifiedName(){
    if (this->prefix==std::nullopt){
        return this->localName;
    }
    return this->prefix.value() + ":" + this->localName;
}


unsigned long CharacterData::length(){
    return this->data.length();
}

DOMString CharacterData::substringData(unsigned long offset, unsigned long count){
    return substring_data(dynamic_cast<Node*>(this), offset, count);
}

void CharacterData::appendData(DOMString data){
    replace_data(dynamic_cast<Node*>(this), this->length(), 0, data);
}

void CharacterData::insertData(unsigned long offset, DOMString data){
    replace_data(dynamic_cast<Node*>(this), offset, 0, data);
}

void CharacterData::deleteData(unsigned long offset, unsigned long count){
    replace_data(dynamic_cast<Node*>(this), offset, count, "");
}

void CharacterData::replaceData(unsigned long offset, unsigned long count, DOMString data){
    replace_data(dynamic_cast<Node*>(this), offset, count, data);
}


Text* Text::splitText(unsigned long offset){
    return split_text_node(this, offset);
}

DOMString Text::wholeText(){
    DOMString data = "";
    for (auto a: contiguous_text_nodes(this)){
        data += this->data;
    }
    return data;
}




bool AbstractRange::collapsed(){
    if (this->startContainer==this->endContainer && this->startOffset==this->endOffset){
        return true;
    }
    return false;
}


StaticRange::StaticRange(StaticRangeInit init){
    if (dynamic_cast<DocumentType*>(init.startContainer) || dynamic_cast<Attr*>(init.startContainer) || dynamic_cast<DocumentType*>(init.endContainer) || dynamic_cast<Attr*>(init.endContainer) ){
        throw InvalidNodeTypeError("invalid node type baby !!");
    }
    this->startContainer = init.startContainer;
    this->startOffset = init.startOffset;
    this->endContainer = init.endContainer;
    this->endOffset = init.endOffset;
}

Range::Range(){};

Node* Range::commonAncestorContainer(){
    Node* container = this->startContainer;
    while (!check_ancestor(this->endContainer, container, true)){
        container = container->parentNode;
    }
    return container;
}


void Range::setStart(Node* node, unsigned long offset){
    set_start_end(this, node, offset);
}

void Range::setEnd(Node* node, unsigned long offset){
    set_start_end(this, node, offset, false);
}

void Range::setStartBefore(Node* node){
    Node* parent = node->parentNode;
    if (parent==nullptr){ throw InvalidNodeTypeError("invalid node type dummy !"); }
    set_start_end(this, parent, node->index());
}

void Range::setStartAfter(Node* node){
    Node* parent = node->parentNode;
    if (parent==nullptr){ throw InvalidNodeTypeError("invalid node type dummy !"); }
    set_start_end(this, parent, node->index()+1);
}

void Range::setEndBefore(Node* node){
    Node* parent = node->parentNode;
    if (parent==nullptr){ throw InvalidNodeTypeError("invalid node type dummy !"); }
    set_start_end(this, parent, node->index(), false);
}

void Range::setEndAfter(Node* node){
    Node* parent = node->parentNode;
    if (parent==nullptr){ throw InvalidNodeTypeError("invalid node type dummy !"); }
    set_start_end(this, parent, node->index()+1, false);
}

void Range::collapse(bool toStart){
    if (toStart){
        this->endContainer = this->startContainer;
        this->endOffset = this->startOffset;
    }
    else{
        this->startContainer = this->endContainer;
        this->startOffset = this->endOffset;
    }
}

void Range::selectNode(Node* node){
    select_node_within_rangee(node, this);
}

void Range::selectNodeContents(Node* node){
    if (dynamic_cast<DocumentType*>(node)){ throw InvalidNodeTypeError("invalid node type boi !!!"); }
    unsigned long length = node->length();
    this->startContainer = node;
    this->startOffset = 0;
    this->endContainer = node;
    this->endOffset = length;
}

short Range::compareBoundaryPoints(unsigned short how, Range* sourceRange){
    if (how!=START_TO_START && how!=START_TO_END && how!=END_TO_END && how!=END_TO_START){
        throw NotSupportedError("not supported this start end whatever !");
    }
    if (this->startContainer->getRootNode()!=sourceRange->startContainer->getRootNode()){
        throw WrongDocumentError("wrong document ! read it u sick boi !!");
    }
    Node* thisnode;
    unsigned long thisoffset;
    Node* othernode;
    unsigned long otheroffset;
    if (how==START_TO_START){
        thisnode = this->startContainer;
        thisoffset = this->startOffset;
        othernode = sourceRange->startContainer;
        otheroffset = sourceRange->startOffset;
    }
    else if (how==START_TO_END){
        thisnode = this->endContainer;
        thisoffset = this->endOffset;
        othernode = sourceRange->startContainer;
        otheroffset = sourceRange->startOffset;
    }
    else if (how==END_TO_END){
        thisnode = this->endContainer;
        thisoffset = this->endOffset;
        othernode = sourceRange->endContainer;
        otheroffset = sourceRange->endOffset;
    }
    else if (how==END_TO_START){
        thisnode = this->startContainer;
        thisoffset = this->startOffset;
        othernode = sourceRange->endContainer;
        otheroffset = sourceRange->endOffset;
    }
    return position(thisnode, thisoffset, othernode, otheroffset);
}


void Range::deleteContents(){
    if (this->collapsed()){
        return;
    }
    Node* original_startnode = this->startContainer;
    unsigned long original_startoffset = this->startOffset;
    Node* original_endnode = this->endContainer;
    unsigned long original_endoffset = this->endOffset;
    
    if (original_startnode==original_endnode && dynamic_cast<CharacterData*>(original_startnode)){
        replace_data(original_startnode, original_startoffset, original_endoffset - original_startoffset, "");
        return;
    }
    std::vector<Node*> nodes_to_remove = {};
    Node* new_node;
    unsigned long new_offset;
    if (check_ancestor(original_endnode, original_startnode, true)){
        new_node = original_startnode;
        new_offset = original_startoffset;
    }
    else{
        Node* reference_node = original_startnode;
        while(reference_node->parentNode!=nullptr && !check_ancestor(original_endnode, reference_node, true)){
            reference_node = reference_node->parentNode;
        }
        new_node = reference_node->parentNode;
        new_offset = reference_node->index() + 1;
    }
    if (dynamic_cast<CharacterData*>(original_startnode)){
        replace_data(original_startnode, original_startoffset, original_startnode->length() - original_startoffset, "");
    }
    for (auto node: nodes_to_remove){
        remove_node(node);
    }
    if (dynamic_cast<CharacterData*>(original_endnode)){
        replace_data(original_endnode, 0, original_endoffset, "");
    }
    this->startContainer = new_node;
    this->startOffset = new_offset;
    this->endContainer = new_node;
    this->endOffset = new_offset;
}

DocumentFragment* Range::extraContents(){
    return new DocumentFragment();
}

DocumentFragment* Range::cloneContents(){
    return new DocumentFragment();
}

void Range::insertNode(Node* node){
    insert_node_in_range(node, this);
}

void Range::surroundContents(Node* newParent){
    if (dynamic_cast<Document*>(newParent) || dynamic_cast<DocumentType*>(newParent) || dynamic_cast<DocumentFragment*>(newParent)){
        throw InvalidNodeTypeError("invalid node type baby !!");
    }
    DocumentFragment* fragment = extract_range(this);
    if (newParent->hasChildNodes()){
        replace_all(nullptr, newParent);
    }
    insert_node_in_range(newParent, this);
    pre_insert_node(dynamic_cast<Node*>(fragment), newParent, nullptr);
    select_node_within_rangee(newParent, this);
}


Range* Range::cloneRange(){
    Range* temp = new Range();
    temp->startContainer = this->startContainer;
    temp->startOffset = this->startOffset;
    temp->endContainer = this->endContainer;
    temp->endOffset = this->endOffset;
    return temp;
}

bool Range::isPointInRange(Node* node, unsigned long offset){
    if (node->getRootNode()!=this->startContainer->getRootNode()){
        return false;
    }
    if (dynamic_cast<DocumentType*>(node)){
        throw InvalidNodeTypeError("u got from the name !");
    }
    if (offset>node->length()){
        throw IndexSizeError("index is not fit !!");
    }
    if (position(node, offset, this->startContainer, this->startOffset)==-1 || position(node, offset, this->endContainer, this->endOffset)==1){
        return false;
    }
    return true;
}


short Range::comparePoint(Node* node, unsigned long offset){
    if (node->getRootNode()!=this->startContainer->getRootNode()){
        throw WrongDocumentError("Wrong document !!");
    }
    if (dynamic_cast<DocumentType*>(node)){
        throw InvalidNodeTypeError("invalid node type !!");
    }
    if (offset>node->length()){
        throw IndexSizeError("index size issue !!");
    }
    if (position(node, offset, this->startContainer, this->startOffset)==-1){
        return -1;
    }
    if (position(node, offset, this->endContainer, this->endOffset)==1){
        return 1;
    }
    return 0;
}


bool Range::intersectsNode(Node* node){
    if (node->getRootNode()!=this->startContainer->getRootNode()){
        return false;
    }
    Node* parent = node->parentNode;
    if (parent==nullptr){
        return true;
    }
    unsigned long offset = node->index();
    if (position(parent, offset, this->endContainer, this->endOffset)==-1 && position(parent, offset+1, this->startContainer, this->startOffset)==1){
        return true;
    }
    return false;
}

DOMString Range::stringification_behavior(){
    DOMString s = "";
    Text* temp = dynamic_cast<Text*>(this->startContainer);
    if (this->startContainer==this->endContainer && temp){
    //     return temp->getdata().substr(this->startOffset, this->endOffset - this->startOffset);
    }
    if (temp){
        // s += temp->getdata().substr(this->startOffset);
    }
    temp = dynamic_cast<Text*>(this->endContainer);
    if (temp){
        // s += temp->getdata().substr(0, this->endOffset);
    }
    return s;
}



unsigned short NodeIterator::filter_node(Node* node){
    //!Later

    // if (this->active){ throw InvalidStateError("INVALID STATE ! HAHA"); }
    // int n = node->nodeType - 1;
    // if (this->filter==nullptr){
    //     return FILTER_ACCEPT;
    // }
    // this->active = true;
    // //some work
    // this->active = false;
    // return result;
	return 1;
}

unsigned short TreeWalker::filter_node(Node* node){
    //!Later

    // if (this->active){ throw InvalidStateError("INVALID STATE ! HAHA"); }
    // int n = node->nodeType - 1;
    // if (this->filter==nullptr){
    //     return FILTER_ACCEPT;
    // }
    // this->active = true;
    // //some work
    // this->active = false;
    // return result;
	return 1;
}



//Node* NodeIterator::nextNode(){
//    return traverse(this, 1);
//}

//Node* NodeIterator::previousNode(){
//    return traverse(this, -1);
//}

Node* TreeWalker::parentNode(){
    Node* node = this->currentNode;
    while (node!=nullptr && node!=this->root){
        node = node->parentNode;
        if (node!=nullptr && this->filter_node(node)==FILTER_ACCEPT){
            this->currentNode = node;
            return node;
        }
    }
    return nullptr;
}

//Node* TreeWalker::firstChild(){
//    return traverse_children(this, 1);
//}

//Node* TreeWalker::lastChild(){
//    return traverse_children(this, -1);
//}


//Node* TreeWalker::nextSibling(){
//    return traverse_sibling(this, 1);
//}

//Node* TreeWalker::previousSibling(){
//    return traverse_sibling(this, -1);
//}

//Node* TreeWalker::previousNode(){
//    Node* node = this->currentNode;
//    while (node!=this->root){
//        Node* sibling = node->previousSibling();
//        while (sibling!=nullptr){
//            node = sibling;
//            int result = this->filter_node(node);
//           while (result!="FILTER_REJECT" && node->hasChildNodes()){
//                node = node->lastChild();
//                result = this->filter_node(node);
//            }
//           if (result==FILTER_ACCEPT){
//                this->currentNode = node;
//                return node;
//            }
//            sibling = node->previousSibling();
//        }
//        if (node==this->root || node->parentNode==nullptr){
//            return nullptr;
//        }
//        // node = node->parentNode();
//        // if (this->filter_node(node)==FILTER_ACCEPT){
//       //    this->currentNode = node;
//        //    return node;
//        //}
//    }
//    return nullptr;
//}


Node* TreeWalker::nextNode(){
    Node* node = this->currentNode;
    unsigned short result = FILTER_ACCEPT;
    while (true){
        while (result!=FILTER_REJECT && node->hasChildNodes()){
            node = node->firstChild();
            result = this->filter_node(node);
            if (result == FILTER_ACCEPT){
                this->currentNode = node;
                return node;
            }
        }
        Node* sibling = nullptr;
        Node* temporary = node;
        while (temporary!=nullptr){
            if (temporary==this->root){
                return nullptr;
            }
            sibling = temporary->nextSibling();
            if (sibling!=nullptr){
                node = sibling;
                break;
            }
            temporary = temporary->parentNode;
        }
        result = this->filter_node(node);
        if (result==FILTER_ACCEPT){
            this->currentNode = node;
            return node;
        }
    }
}



void DOMTokenList::add(std::vector<DOMString> tokens){
    for (auto token: tokens){
        if (token==""){ throw SyntaxError("sytaxxxxxx"); }
        if (token.find(" ")!=std::string::npos){ throw InvalidCharacterError("uk !"); }
    }
    for (auto token: tokens){
        this->list.insert(token);
    }
    this->update();
}


void DOMTokenList::remove(std::vector<DOMString> tokens){
    for (auto token: tokens){
        if (token==""){ throw SyntaxError("sytaxxxxxx"); }
        if (token.find(" ")!=std::string::npos){ throw InvalidCharacterError("uk !"); }
    }
    for (auto token: tokens){
        this->list.erase(token);
    }
    this->update();
}

bool DOMTokenList::toggle(DOMString token, std::optional<bool> force){
    if (token==""){ throw SyntaxError("sytaxxxxxx"); }
    if (token.find(" ")!=std::string::npos){ throw InvalidCharacterError("uk !"); }
    if (this->list.find(token)!=this->list.end()){
        if (!force.has_value() || !force.value()){
            this->list.erase(token);
            this->update();
            return true;
        }
    }
    else{
        if (!force.has_value() || force){
            this->list.insert(token);
            this->update();
            return true;
        }
    }
    return false;
}

bool DOMTokenList::replace(DOMString token, DOMString newToken){
    if (token=="" || newToken==""){ throw SyntaxError("sytaxxxxxx"); }
    if (token.find(" ")!=std::string::npos || newToken.find(" ")!=std::string::npos){ throw InvalidCharacterError("uk !"); }
    if (this->list.find(token)==this->list.end()){ return false; }
    this->list.erase(token);
    this->list.insert(newToken);
    this->update();
    return true;
}


bool DOMTokenList::supports(DOMString token){
    return this->validate(token);
}