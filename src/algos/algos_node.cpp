#ifndef NODE_ALGOS
#define NODE_ALGOS

#include "../include/nodes/node.hpp"
#include "../include/nodes/document.hpp"
#include "algos_base.cpp"
#include "mutation_algos.cpp"
#include <string>
#include <cassert>

class Document;
Node* clone_a_single_node(Node* node, Document* document, CustomElementRegistry* fallbackRegistry);
// Node* create_element(Document* document, DOMString name, std::optional<DOMString> namespaceURI, std::optional<DOMString> prefix, bool gtem, CustomElementRegistry*istry){
//     return dynamic_cast<Node*>(new Element(namespaceURI, prefix, name));
// };

Node* clone_node(Node* node, Document* document = nullptr, bool subtree = false, Node* parent = nullptr, CustomElementRegistry* fallbackRegistry = nullptr){
    if (document==nullptr){
        document = node->ownerDocument;
    }
    // assert(!dynamic_cast<Document*>(node) || (dynamic_cast<Document*>(node)==document));
    Node* copy = clone_a_single_node(node, document, fallbackRegistry);
    if (parent != nullptr){
        pre_insert_node(copy, parent, nullptr);
    }
    if (subtree){
        for (auto child: node->childNodes.node_list){
            clone_node(child, document, subtree, copy, fallbackRegistry);
        }
    }
    // Element* temp = dynamic_cast<Element*>(node);
    // if (temp && temp->shadow_root!=nullptr && temp->shadow_root->clonable){
    //     Element* temp2 = dynamic_cast<Element*>(copy);
    //     assert(temp2->shadow_root==nullptr);
    //     CustomElementRegistry* shadowRootRegistry = temp->shadow_root->custom_element_registry;
    //     attach_shadow_root(temp2, temp->shadow_root->mode, true, temp->shadow_root->serializable, temp->shadow_root->delegatesFocus, temp->shadow_root->slotAssignment, shadowRootRegistry);
    //     temp2->shadow_root->declarative = temp->shadow_root->declarative;
    //     for (auto child: temp->shadow_root->childNodes){
    //         clone_node(child, document, subtree, temp2->shadow_root);
    //     }
    // }
    return copy;
}


Node* clone_a_single_node(Node* node, Document* document, CustomElementRegistry* fallbackRegistry){
    Node* copy = nullptr;
    // Element* temp = dynamic_cast<Element*>(node);
    Element* temp = nullptr;
    if (temp){
        // CustomElementRegistry* registry = temp->customElementRegistry;
        // if (!registry){ registry = fallbackRegistry; }
        // copy = create_element(document, temp->localName, temp->namespaceURI, temp->prefix, false, registry);
        // for (auto attr: temp->attributes.attribute_list){
        //     Node* copyAttribute = clone_a_single_node(attr, document, nullptr);
        //     append_attribute_to_element(copyAttribute, dynamic_cast<Element*>(copy));
        // }
    }
    else{
        // Document* temp = dynamic_cast<Document*>(node);
        // if (temp){
        //     Document* temp2 = new Document();
        //     temp2->encoding = temp->encoding;
        //     temp2->contentType = temp->contentType;
        //     temp2->URL = temp->URL;
        //     temp2->origin = temp->origin;
        //     temp2->type = temp->type;
        //     temp2->mode = temp->mode;
        //     temp2->allow_declarative_shodow_roots = temp->allow_declarative_shodow_roots;
        //     // step for custom element registry is scoped
        //     temp2->custom_element_registry = temp->custom_element_registry;
        //     copy = dynamic_cast<Node*>(temp2);
        // }
        // else{
        //     DocumentType* temp = dynamic_cast<DocumentType*>(node);
        //     if (temp){
        //         DocumentType* temp2 = new DocumentType();
        //         temp2->name = temp->name;
        //         temp2->publicId = temp->publicId;
        //         temp2->systemId = temp->systemId;
        //         copy = dynamic_cast<Node*>(temp2);
        //     }
        //     else{
        //         Attr* temp = dynamic_cast<Attr*>(node);
        //         if (temp){
        //             Attr* temp2 = new Attr("something");
        //             temp2->namespaceURI = temp->namespaceURI;
        //             temp2->prefix = temp->prefix;
        //             temp2->localName = temp->localName;
        //             temp2->value = temp->value;
        //             copy = dynamic_cast<Node*>(temp2);
        //         }
        //         else{
        //             Text* temp = dynamic_cast<Text*>(node);
        //             if (temp){}
        //             else{
        //                 Comment* temp = dynamic_cast<Comment*>(node);
        //                 if (temp){
        //                     Comment* temp2 = new Comment();
        //                     temp2->data = temp->data;
        //                     copy = dynamic_cast<Node*>(temp2);
        //                 }
        //                 else{
        //                     ProcessingInstruction* temp = dynamic_cast<ProcessingInstruction*>(node);
        //                     if (temp){
        //                         ProcessingInstruction* temp2 = new ProcessingInstruction();
        //                         temp2->target = temp->target;
        //                         temp2->data = temp->data;
        //                     }
        //                 }
        //             }
        //         }
        //     }
        // }
    }
    assert(dynamic_cast<Node*>(copy));
    // if (dynamic_cast<Document*>(node)){ document = dynamic_cast<Document*>(copy); }
    copy->ownerDocument = document;
    return copy;
}

bool nodequals(Node* first, Node* second){
    if (typeid(first) != typeid(second)){
        return false;
    }
    Document* temp = nullptr;
    if (temp){
        // DocumentType* temp2 = dynamic_cast<DocumentType*>(second);
        // if (temp->getname()!=temp2->getname() || temp->getpublicId()!=temp2->getpublicId() || temp->getsystemId()!=temp2->getsystemId()){
        //     return false;
        // }
    }
    else{
        // Element* temp = dynamic_cast<Element*>(first);
        // if (temp){
        //     Element* temp2 = dynamic_cast<Element*>(second);
        //     if (temp->namespaceURI!=temp2->namespaceURI || temp->prefix!=temp2->prefix || temp->localName!=temp2->localName){
        //         return false;
        //     }
        // }
        // else{
        //     Attr* temp = dynamic_cast<Attr*>(first);
        //     if (temp){
        //         Attr* temp2 = dynamic_cast<Attr*>(second);
        //         if (temp->namespaceURI!=temp2->namespaceURI || temp->localName!=temp2->localName || temp->value!=temp2->value){
        //             return false;
        //         }
        //     }
        //     else{
        //         ProcessingInstruction* temp = dynamic_cast<ProcessingInstruction*>(first);
        //         if (temp){
        //             ProcessingInstruction* temp2 = dynamic_cast<ProcessingInstruction*>(second);
        //             if (temp->target!=temp2->target || temp->data!=temp2->data){
        //                 return false;
        //             }
        //         }
        //         else{
        //             Comment* temp = dynamic_cast<Comment*>(first);
        //             if (temp){
        //                 Comment* temp2 = dynamic_cast<Comment*>(second);
        //                 if (temp->data!=temp2->data){
        //                     return false;
        //                 }
        //             }
        //         }
        //     }
        // }
    }
    // Element* temp = dynamic_cast<Element*>(first);
    // if (temp){
    //     Element* temp2 = dynamic_cast<Element*>(second);
    //     int i = 0;
    //     for (auto attribute: temp->attributes.attribute_list){
    //         if (attribute != temp2->attributes.attribute_list.at(i)){
    //             return false;
    //         }
    //         i++;
    //     }
    // }
    if (first->childNodes.length() != second->childNodes.length()){
        return false;
    }
    int i = 0;
    for (auto a: first->childNodes.node_list){
        if (!nodequals(a, second->childNodes[i])){
            return false;
        }
        i++;
    }
    return true;
}

void string_replace_all(std::string &str, Node* parent){
    // Node* node = nullptr;
    // if (str!=""){
    //     node = new Text(str);
    //     node->ownerDocument = parent->ownerDocument;
    // }
    // replace_all(node, parent);
}


std::optional<DOMString> locate_a_namespace(Node* node, std::optional<DOMString> prefix){
    Element* temp = nullptr;
    if (temp){
        // if (prefix=="xml"){
        //     return"http://www.w3.org/XML/1998/namespace";
        // }
        // if (prefix=="xmlns"){
        //     return "http://www.w3.org/2000/xmlns/";
        // }
        // if (temp->namespaceURI.has_value() && temp->prefix==prefix){
        //     return temp->namespaceURI;
        // }
        // for (auto attr: temp->attributes.attribute_list){
        //     if ((attr->namespaceURI=="http://www.w3.org/2000/xmlns/" && attr->prefix=="xmlns" && attr->localName==prefix) || (!prefix.has_value() && attr->namespaceURI=="http://www.w3.org/2000/xmlns/" && !attr->prefix.has_value() && attr->localName=="xmlns")){
        //         if (atr->value==""){ return std::nullopt; }
        //         return attr->value;
        //     }
        // }
        // if (temp->parentElement==nullptr){ return std::nullopt; }
        // return locate_a_namespace(temp->parentElement, prefix);
    }
    else{
        Document* temp = nullptr;
        if (temp){
            // if (temp->documentElement()){ return locate_a_namespace(temp->documentElement(), prefix); }
            // return std::nullopt;
        }
        // else{
        //     DocumentType* temp = dynamic_cast<DocumentType*>(node);
        //     if (temp){}
        //     else{
        //         DocumentFragment* temp = dynamic_cast<DocumentFragment*>(node);
        //         if (temp){
        //             return std::nullopt;
        //         }
        //         else{
        //             Attr* temp = dynamic_cast<Attr*>(node);
        //             if (temp){
        //                 if (temp->ownerElement==nullptr){ return nullptr; }
        //                 return locate_a_namespace(temp->ownerElement, prefix);
        //             }
        //             else{
        //                 if (node->parentElement==nullptr){ return std::nullopt; }
        //                 return locate_a_namespace(node->parentElement, prefix);
        //             }
        //         }
        //     }
        // }
    }
    return std::nullopt;
}

std::optional<DOMString> locate_a_namespace_prefix(Element* element, std::optional<DOMString> namesp){
    // if (element->namespaceURI==namespace && element->prefix.has_value()){
    //     return element->prefix;
    // }
    // for (auto attr: element->attributes.attribute_list){
    //     // if (attr->prefix=="xmlns" && attr->value==namesp){
    //     //     return attr->localName;
    //     // }
    // }
    // if (element->parentElement!=nullptr){
    //     return locate_a_namespace_prefix(element, namesp);
    // }
    return std::nullopt;
}

// HTMLCollection* list_of_elements(DOMString qualifiedName, Node* root){
//     // if (qualifiedName=="*"){}
//     // if (root->ownerDocument->type!="xml"){}
//     return new HTMLCollection();
// }

// HTMLCollection* list_of_elements(std::optional<DOMString> namesp, DOMString localName, Node* root){
//     // if (namesp==""){ namesp = std::nullopt; }
//     // if (namesp=="*" && localName=="*"){}
//     // if (namesp=="*"){}
//     // if (localName=="*"){}
//     return new HTMLCollection();
// }

// HTMLCollection* list_of_elements(std::vector<DOMString> &classNames, Node* root){
//     // std::vector<DOMString> classes;
//     // for (auto class: classes){
//     //     auto something = ParseOrderedSet(class);
//     // }
//     return new HTMLCollection();
// }


int main(){}


#endif