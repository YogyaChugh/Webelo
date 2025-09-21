#include "nodes/document.hpp"
#include "algos_base.cpp"
#include "base.cpp"
#include <algorithm>
#include "exceptions.cpp"

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