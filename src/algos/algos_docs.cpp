#include "nodes/document.hpp"
#include "algos_base.cpp"
#include "mutation_algos.cpp"
#include "base.cpp"
#include "basic.cpp"
#include <algorithm>
#include "exceptions.cpp"
#include "assert.h"

void flatten_element_creation_options(std::variant<DOMString,ElementCreationOptions> options, Document* document, CustomElementRegistry* registry, std::optional<DOMString> &is){
    if (std::holds_alternative<ElementCreationOptions>(options)){
        ElementCreationOptions temp = std::get<ElementCreationOptions>(options);
        if (temp.CustomElementRegistry){
            registry = temp.CustomElementRegistry;
        }
        if (registry!=document->custom_element_registry){
            throw NotSupportedError("not supported boi !!");
        }
        if (temp.is.has_value()){
            is = temp.is;
        }
        if (registry!=nullptr && is!=std::nullopt){
            throw NotSupportedError("not supported boi !!");
        }
    }
    if (registry==nullptr){}
}

void adopt(Node* node, Document* document){
    Document* oldDocument = node->ownerDocument;
    if (node->parentNode!=nullptr){ remove_node(node); }
    if (document!=oldDocument){
        for (auto inclusiveDescendant: node->shad)
    }
}

Element* internal_create_element_ns(Document* document, std::optional<DOMString> namesp, DOMString qualifiedName, std::variant<DOMString,ElementCreationOptions> options){
    std::optional<DOMString> prefix;
    DOMString localName;
    ValidateAndExtract(namesp, qualifiedName, "element", prefix, localName);
    CustomElementRegistry* registry;
    std::optional<DOMString> is;
    flatten_element_creation_options(options, document, registry, is);
    return create_element(document, localName, namesp, prefix, is, true, registry);
}


Element* create_element(Document* document, DOMString localName, std::optional<DOMString> namesp, std::optional<DOMString> prefix = std::nullopt, std::optional<DOMString> is = std::nullopt, bool synchronousCustomElements = false, std::variant<DOMString,std::nullptr_t,CustomElementRegistry> registry = "default"){
    return new Element("global","e","k",new CustomElementRegistry(), UNDEFINED);
}

void change_attribute_value(Attr* attribute, DOMString value){
    DOMString oldValue = attribute->value;
    attribute->value = value;
    handle_attribute_changes(attribute, attribute->ownerElement, oldValue, value);
}

void append_attribute(Attr* attribute, Element* element){
    element->attributes.attribute_list.push_back(attribute);
    attribute->ownerElement = element;
    attribute->ownerDocument = element->ownerDocument;
    handle_attribute_changes(attribute, element, std::nullopt, attribute->value);
}

void remove_attribute(Attr* attribute){
    Element* element = attribute->ownerElement;
    element->attributes.attribute_list.erase(std::find(element->attributes.attribute_list.begin(), element->attributes.attribute_list.end(), attribute));
    attribute->ownerElement = nullptr;
    handle_attribute_changes(attribute, element, attribute->value, std::nullopt);
}

void replace_attribute(Attr* oldAttribute, Attr* newAttribute){
    Element* element = oldAttribute->ownerElement;
    std::replace(element->attributes.attribute_list.begin(), element->attributes.attribute_list.end(), oldAttribute, newAttribute);
    newAttribute->ownerElement = element;
    newAttribute->ownerDocument = element->ownerDocument;
    oldAttribute->ownerElement = nullptr;
    handle_attribute_changes(oldAttribute, element, oldAttribute->value, newAttribute->value);
}

Attr* fetch_attribute(DOMString qualifiedName, Element* element){
    if (element->ownerDocument->type!=XML){
        std::transform(qualifiedName.begin(), qualifiedName.end(), qualifiedName.begin(), [](unsigned char c){ return std::tolower(c); });
    }
    for (auto attr: element->attributes.attribute_list){
        if (attr->qualifiedName()==qualifiedName){
            return attr;
        }
    }
    return nullptr;
}

Attr* fetch_attribute(std::optional<DOMString> namesp, DOMString localName, Element* element){
    if (namesp.has_value() && namesp.value()==""){ namesp = std::nullopt; }
    for (auto attr: element->attributes.attribute_list){
        if (attr->namespaceURI==namesp && attr->localName==localName){
            return attr;
        }
    }
    return nullptr;
}


DOMString fetch_attribute(Element* element, DOMString localName, std::optional<DOMString> namesp = std::nullopt){
    Attr* attr = fetch_attribute(namesp, localName, element);
    if (attr==nullptr){ return ""; }
    return attr->value;
}


Attr* set_attribute(Attr* attr, Element* element){
    if (attr->ownerElement!=nullptr && !dynamic_cast<Element*>(attr->ownerElement)){ throw InUseAttributeError("In use !!"); }
    Attr* oldAttr = fetch_attribute(attr->namespaceURI, attr->localName, element);
    if (oldAttr==attr){ return attr; }
    if (oldAttr!=nullptr){
        replace_attribute(oldAttr, attr);
    }
    else{
        append_attribute(attr, element);
    }
    return oldAttr;
}


void set_attribute_value(Element* element, DOMString localName, DOMString value, std::optional<DOMString> prefix = std::nullopt, std::optional<DOMString> namesp = std::nullopt){
    Attr* attribute = fetch_attribute(namesp, localName, element);
    if (attribute==nullptr){
        Attr* attr = new Attr(localName);
        attr->namespaceURI = namesp;
        attr->prefix = prefix;
        attr->value = value;
        attr->ownerDocument = element->ownerDocument;
        append_attribute(attr, element);
        return;
    }
    change_attribute_value(attribute, value);
}

Attr* remove_attribute_by_name(DOMString qualifiedName, Element* element){
    Attr* attr = fetch_attribute(qualifiedName, element);
    if (attr!=nullptr){
        remove_attribute(attr);
    }
    return attr;
}

Attr* remove_attribute_by_namespace(std::optional<DOMString> namesp, DOMString localName, Element* element){
    Attr* attr = fetch_attribute(namesp, localName, element);
    if (attr!=nullptr){
        remove_attribute(attr);
    }
    return attr;
}

void attach_shadow_root(Element* element, ShadowRootMode mode, bool clonable, bool serializable, bool delegatesFocus, SlotAssignmentMode slotAssignment, std::optional<CustomElementRegistry> registry){
    if (element->namespaceURI!="http://www.w3.org/1999/xhtml"){ throw NotSupportedError("nope not supported"); }
    if (!ValidShadowHostName(element->localName)){ throw NotSupportedError("nope not supported boi !!"); }
    if (ValidCustomElementName(element->localName) || element->is!=std::nullopt){}
    if (element->getshadow_root()!=nullptr){
        ShadowRoot* currentShadowRoot = element->getshadow_root();
        if (!currentShadowRoot->declarative || currentShadowRoot->mode!=mode){ throw NotSupportedError("nope not supporting :) !"); }
        else{
            for (auto child: currentShadowRoot->childNodes.node_list){
                remove_node(child);
            }
            currentShadowRoot->declarative = false;
            return;
        }
    }
    ShadowRoot* shadow = new ShadowRoot();
    shadow->ownerDocument = element->ownerDocument;
    shadow->associatedHost = element;
    shadow->mode = mode;
    shadow->delegatesFocus = delegatesFocus;
    if (element->customElementState==PRECUSTOMIZED && element->customElementState==CUSTOM){
        shadow->availableToElementInternals = true;
    }
    shadow->slotAssignment = slotAssignment;
    shadow->declarative = false;
    shadow->clonable = clonable;
    shadow->serializable = serializable;
    shadow->custom_element_registry = &registry.value();
    element->shadow_root = shadow;
}

Node* insert_adjacent(Element* element, DOMString where, Node* node){
    std::transform(where.begin(), where.end(), where.begin(), [](unsigned char c){ return std::tolower(c); } );
    if (where=="beforebegin"){
        if (element->parentNode==nullptr){ return nullptr; }
        return pre_insert_node(node, element->parentNode, element);
    }
    else if (where=="afterbegin"){
        return pre_insert_node(node, element, element->firstChild());
    }
    else if (where=="beforeend"){
        return pre_insert_node(node, element, nullptr);
    }
    else if (where=="afterend"){
        if (element->parentNode==nullptr){ return nullptr; }
        return pre_insert_node(node, element->parentNode, element->nextSibling());
    }
    else{
        throw SyntaxError("syntax errrrrror boi !!");
    }
}

DOMString replace_data(Node* node, unsigned long offset, unsigned long count, DOMString data){
    unsigned length = node->length();
    if (offset>length){ throw IndexSizeError("greater than error !!"); }
    if ((offset+count)>length){ count = length-offset; }
    // queue mutation record
}


DOMString substring_data(Node* node, unsigned long offset, unsigned long count){
    unsigned length = node->length();
    if (offset>length){ throw IndexSizeError("greater than error !!"); }
    CharacterData* temp = dynamic_cast<CharacterData*>(node);
    if ((offset+count)>length){ return temp->getdata().substr(offset); }
    return temp->getdata().substr(offset, count);
}


bool check_exclusive_text_node(Text* node){
    if (dynamic_cast<CDATASection*>(node)){ return false; }
    return true;
}

std::vector<Text*> contiguous_text_nodes(Text* node){
    std::vector<Text*> temp = {node};
    Text* currentNode = dynamic_cast<Text*>(node->previousSibling());
    while (currentNode){
        temp.insert(temp.begin(), currentNode);
        currentNode = dynamic_cast<Text*>(currentNode->previousSibling());
    }
    currentNode = dynamic_cast<Text*>(node->nextSibling());
    while (currentNode){
        temp.push_back(currentNode);
        currentNode = dynamic_cast<Text*>(currentNode->nextSibling());
    }
    return temp;
}

std::vector<Text*> contiguous_exclusive_text_nodes(Text* node){
    std::vector<Text*> temp = {node};
    Text* currentNode = dynamic_cast<Text*>(node->previousSibling());
    while (currentNode && !dynamic_cast<CDATASection*>(currentNode)){
        temp.insert(temp.begin(), currentNode);
        currentNode = dynamic_cast<Text*>(currentNode->previousSibling());
    }
    currentNode = dynamic_cast<Text*>(node->nextSibling());
    while (currentNode && !dynamic_cast<CDATASection*>(currentNode)){
        temp.push_back(currentNode);
        currentNode = dynamic_cast<Text*>(currentNode->nextSibling());
    }
    return temp;
}




DOMString child_text_content(Node* node){
    DOMString temp = "";
    for (auto a: node->childNodes.node_list){
        Text* temp2 = dynamic_cast<Text*>(a);
        if (temp2){ temp+= temp2->getdata(); }
    }
    return temp;
}

DOMString descendant_text_content(Node* node){
    Node* currentNode = node->childNodes[0];
    std::vector<Node*> temp = {currentNode};
    Text* temp2;
    DOMString data = "";
    while (currentNode!=nullptr){
        temp2 = dynamic_cast<Text*>(currentNode);
        if (temp2){
            data += temp2->getdata();
        }
        if (currentNode->childNodes.length()!=0){
            temp.push_back(currentNode);
            currentNode = currentNode->firstChild();
            continue;
        }
        currentNode = currentNode->nextSibling();
        while (currentNode==nullptr && !temp.empty()){
            currentNode = (*(temp.end() -1))->nextSibling();
            temp.erase(temp.end()-1);
        }
    }
    return data;
}


Text* split_text_node(Text* node, unsigned long offset){
    unsigned long length = node->length();
    if (offset>length){ throw IndexSizeError("size issues ! You are fat :) "); }
    unsigned long count = length - offset;

    DOMString data = substring_data(node, offset, count);
    Text* new_node = new Text(data);
    new_node->ownerDocument = node->ownerDocument;

    Node* parent = node->parentNode;
    if (parent!=nullptr){
        insert_node(new_node, parent, node->nextSibling());
    }
    replace_data(node, offset, count, "");
    return new_node;
}


int position(Node* nodeA, unsigned long offsetA, Node* nodeB, unsigned long offsetB){
    assert(nodeA->getRootNode()==nodeB->getRootNode());
    if (nodeA==nodeB){
        if (offsetA==offsetB){ return 0; }
        if (offsetA<offsetB){ return -1; }
        return 1;
    }
    if (*nodeA^nodeB){
        int a = position(nodeB, offsetB, nodeA, offsetA);
        if (a==-1){ return 1; }
        if (a==1){ return -1; }
    }
    if (check_ancestor(nodeB, nodeA)){
        Node* child = nodeB;
        bool ischild = false;
        int index;
        while (!ischild){
            index = 0;
            for (auto a: nodeA->childNodes.node_list){
                if (a==child){ ischild = true; break; }
                index++;
            }
            if (!ischild){
                child = child->parentNode;
            }
        }
        if (index<offsetA){
            return 1;
        }
    }
    return -1;
}


bool static_range_valid(StaticRange* range){
    if (range->startContainer->getRootNode(true)!=range->endContainer->getRootNode(true)){
        return false;
    }
    if (range->startOffset<0 || range->startOffset>range->startContainer->length()){
        return false;
    }
    if (range->endOffset<0 || range->endOffset>range->endContainer->length()){
        return false;
    }
    int temp = position(range->startContainer, range->startOffset, range->endContainer, range->endOffset);
    if (temp==1){
        return false;
    }
    return true;
}

bool contained_in_range(Node* node, Range* range){
    if (node->getRootNode()!=range->startContainer->getRootNode()){
        return false;
    }
    int temp = position(node, 0, range->startContainer, range->startOffset);
    if (temp==0 || temp==-1){
        return false;
    }
    temp = position(node, node->length(), range->endContainer, range->endOffset);
    if (temp==0 || temp==1){
        return false;
    }
    return true;
}

bool partially_contained_in_range(Node* node, Range* range){
    bool one = check_ancestor(range->startContainer, node, true);
    bool two = check_ancestor(range->endContainer, node, true);
    if ((one && !two) || (!one && two)){
        return true;
    }
    return false;
}

void pre_remove_range(Node* node){
    Node* parent = node->parentNode;
    assert(parent!=nullptr);
    unsigned long index = node->index();
}

void set_start_end(Range* range, Node* node, unsigned long offset, bool start = true){
    if (dynamic_cast<DocumentType*>(node)){ throw InvalidNodeTypeError("invalid node type !!!!!"); }
    if (offset>node->length()){ throw IndexSizeError("size issues, fatty !!"); }
    if (start){
        if ((range->startContainer->getRootNode()!=node->getRootNode()) || position(node, offset, range->endContainer, range->endOffset)==1){
            range->endContainer = node;
            range->endOffset = offset;
        }
        range->startContainer = node;
        range->startOffset = offset;
    }
    else{
        if ((range->startContainer->getRootNode()!=node->getRootNode()) || position(node, offset, range->startContainer, range->startOffset)==-1){
            range->startContainer = node;
            range->startOffset = offset;
        }
        range->endContainer = node;
        range->endOffset = offset;
    }

}

void select_node_within_range(Node* node, Range* range){
    Node* parent = node->parentNode;
    if (parent==nullptr){ throw InvalidNodeTypeError("invalid node type dummy !"); }
    unsigned long index = node->index();
    range->startContainer = parent;
    range->startOffset = index;
    range->endContainer = parent;
    range->endOffset = index + 1;
}