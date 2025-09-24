#ifndef ALGOS_BASE_DOM
#define ALGOS_BASE_DOM

#include "nodes/node.hpp"
#include "nodes/document.hpp"
#include "base.cpp"
#include "exceptions.cpp"
#include <set>
#include <string>
#include <vector>
#include "utf8.h"

// Returns a set of strings. It separates all the substrings based on ASCII whitespace in the input !!
std::set<DOMString> parse_ordered_set(DOMString input){
    std::vector<int> asciiWhitespace = {9,10,12,13,32};
    std::vector<DOMString> inputTokens = split_text_multiple(input, asciiWhitespace);
    std::set<DOMString> tokens;
    for (DOMString a: inputTokens){
        tokens.insert(a);
    }
    return tokens;
}

// Concatenates all the strings in the set provided with U+0020 (SPACE)
DOMString serialize_ordered_set(std::set<DOMString> input){
    DOMString str = "";
    int i=0;
    for (auto a: input){
        str.append(a);
        if (i!=(input.size()-1)){
            str.append(" ");
        }
        i++;
    }
    return str;
}

/*
Validates Namespace Prefix !
These characters aren't allowed:
- ASCII WHITESPACE (U+0009 TAB, U+000A LF, U+000C FF, U+000D CR, or U+0020 SPACE)
- U+0000 NULL
- U+002F (/)
- U+003E (>)
*/
bool valid_namespace_prefix(DOMString input){
    if (input.size()==0){ return false; }
    unsigned int temp;
    for (auto it=input.begin(); it!=input.end();){
        try{
            temp = utf8::next(it, input.end());
        }
        catch (utf8::not_enough_room){
            break;
        }
        if (temp==9 || temp==10 || temp==12 || temp==13 || temp==32 || temp==0 || temp==47 || temp==62){
            return false;
        }
    }
    return true;
}


/*
Validates Attribute Names !
These characters aren't allowed:
- ASCII WHITESPACE (U+0009 TAB, U+000A LF, U+000C FF, U+000D CR, or U+0020 SPACE)
- U+0000 NULL
- U+002F (/)
- U+003D (=)
- U+003E (>)
*/
bool valid_attribute_local_name(DOMString input){
    if (input.size()==0){ return false; }
    int temp;
    for (auto it=input.begin(); it!=input.end();){
        if (temp==9 || temp==10 || temp==12 || temp==13 || temp==32 || temp==0 || temp==47 || temp==61 || temp==62){
            return false;
        }
    }
    return true;
}



//Validates Element Names !
bool valid_element_local_name(DOMString input){
    if (input.size()==0){ return false; }
    auto it = input.begin();
    unsigned int first = utf8::next(it, input.end());
    unsigned int temp;
    if ((first>=65 && first<=90) || (first>=97 && first<=122)){
        for (;it<input.end();){
            try{
                temp = utf8::next(it, input.end());
            }
            catch (utf8::not_enough_room){
                break;
            }
            if (temp==9 || temp==10 || temp==12 || temp==13 || temp==32 || temp==0 || temp==47 || temp==62){
                return false;
            }
        }
        return true;
    }
    if (first!=58 && first!=95 && (first<128 || first>1114111)){
        return false;
    }
    for (it=input.begin();it<input.end();){
        try{
            temp = utf8::next(it, input.end());
        }
        catch (utf8::not_enough_room){
            break;
        }
        if ((temp<65 || temp>90) && (temp<97 || temp>122) && (temp<48 || temp>57) && temp!=45 && temp!=46 && temp!=58 && temp!=95 && (temp<128 || temp>1114111)){
            return false;
        }
    }
    return true;
}


/*
Validates DocType Names !
These characters aren't allowed:
- ASCII WHITESPACE (U+0009 TAB, U+000A LF, U+000C FF, U+000D CR, or U+0020 SPACE)
- U+0000 NULL
- U+003E (>)
*/
bool valid_doctype_name(DOMString input){
    unsigned int temp;
    for (auto it=input.begin(); it<input.end();){
        temp = utf8::next(it, input.end());
        if (temp==9 || temp==10 || temp==12 || temp==13 || temp==32 || temp==0 || temp==62){
            return false;
        }
    }
    return true;
}



// From the HTML Specification
bool valid_custom_element_name(DOMString name){
    if (!valid_element_local_name(name)){ return false; }
    int a = name.at(0);
    if (a<97 && a>122){ return false; }
    bool containsHyphen = false;
    for (auto ch: name){
        if (ch=='-'){ containsHyphen = true; }
        int c = ch;
        if (c>=65 && c<=90){ return false; }
    }
    if (!containsHyphen){ return false; }
    if (name=="annotation-xml" || name=="color-profile" || name=="font-face" || name=="font-face-src" || name=="font-face-uri" || name=="font-face-format" || name=="font-face-name" || name=="missing-glyph"){
        return false;
    }
    return true;
}

bool valid_shadow_host_name(DOMString name){
    if (!valid_custom_element_name(name)){ return false; }
    if (name!="article" && name!="aside" && name!="blockquote" && name!="body" && name!="div" && name!="footer" && name!="h1" && name!="h2" && name!="h3" && name!="h4" && name!="h5" && name!="h6" && name!="header" && name!="main" && name!="nav" && name!="p" && name!="section" && name!="span"){
        return false;
    }
    return true;
}



/*
It validates and extracts namespace `prefix` and `localName` based on other args.
If the `qualifiedName` contains a (:) it cuts it in half to feed `prefix` and `localName`. Else, `localName` gets `qualifiedName` and `prefix` is null
`prefix` is validated and matched with it's corresponding namespace (1st arg) whereas
the `localName` is being validated to be an `attribute` or an `element` based on the value of `context`
*/
void validate_and_extract(std::optional<DOMString> &namesp,DOMString qualifiedName, DOMString context,std::optional<DOMString> &prefix,DOMString &localName){
    if (namesp.has_value() && namesp.value()==""){ namesp = std::nullopt; }
    prefix = std::nullopt;
    localName = qualifiedName;
    if (qualifiedName.find(":")!=std::string::npos){
        std::vector<DOMString> splitResult = split_text(qualifiedName, ":");
        prefix = splitResult[0];
        localName = splitResult[1];
        if (!valid_namespace_prefix(prefix.value())){ throw InvalidCharacterError("The prefix aka 'text before colon (:)' in the qualifiedName (2nd arg) should be a valid namespace prefix !"); }
    }
    assert(!prefix.has_value() || valid_namespace_prefix(prefix.value()));
    if (context=="attribute" && !valid_attribute_local_name(localName)){ throw InvalidCharacterError("qualified name (sometimes, text after colon (:)) isn't a valid attribute name !"); }
    if (context=="element" && !valid_element_local_name(localName)){ throw InvalidCharacterError("qualified name (sometimes, text after colon (:)) isn't a valid element name !"); }
    if (!prefix.has_value() && !namesp.has_value()){ throw NamespaceError("Namespace error !! Namespace &  Namespace Prefix are both null !"); }
    if (prefix.has_value() && prefix.value()=="xml" && namesp.has_value() && namesp.value()!="http://www.w3.org/XML/1998/namespace"){ throw NamespaceError("Namespace error !! Namespace & namespace prefix don't match !"); }
    if ((qualifiedName=="xmlns" ||(prefix.has_value() && prefix.value()=="xmlns")) && (!namesp.has_value() || namesp.value()!="http://www.w3.org/2000/xmlns/")){ throw NamespaceError("Namespace error !! Namespace & namespace prefix don't match !"); }
    if (namesp.has_value() && namesp.value()=="http://www.w3.org/2000/xmlns/" && (qualifiedName!="xmlns" && (!prefix.has_value() ||(prefix.has_value() && prefix.value()!="xmlns")))){ throw NamespaceError("Namespace error !! Namespace & namespace prefix don't match !"); }
}


#endif