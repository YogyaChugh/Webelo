#include "include/nodes/node.hpp"
#include "include/nodes/document.hpp"
#include "include/base.hpp" //
#include "include/exceptions.hpp"
#include <set> //
#include <string> //
#include <vector> //
#include "utf8.h" //

// Returns a set of strings. It separates all the substrings based on ASCII whitespace in the input !!
std::set<DOMString> ParseOrderedSet(DOMString input){
    std::vector<int> ascii_whitespace = {9,10,12,13,32};
    std::vector<DOMString> inputTokens = SplitTextMultiple(input, ascii_whitespace);
    std::set<DOMString> tokens;
    for (DOMString a: inputTokens){
        tokens.insert(a);
    }
    return tokens;
}

// Concatenates all the strings in the set provided with U+0020 (SPACE)
DOMString SerializeOrderedSet(std::set<DOMString> input){
    DOMString str = "";
    for (size_t i=0;i<input.size();i++){
        str+=input[i];
        if (i!=(input.size()-1)){
            str+=" ";
        }
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
bool ValidNamespacePrefix(DOMString input){
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
bool ValidAttributeLocalName(DOMString input){
    if (input.size()==0){ return false; }
    int temp;
    for (auto it=input.begin(); it!=input.end();){
        try{
            temp = utf8::next(it, input.end());
        }
        catch (utf8::not_enough_room){
            break;
        }
        if (temp==9 || temp==10 || temp==12 || temp==13 || temp==32 || temp==0 || temp==47 || temp==61 || temp==62){
            return false;
        }
    }
    return true;
}



//Validates Element Names !
bool validElementLocalName(DOMString input){
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
        temp = utf8::next(it, input.end());
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
bool validDocTypeName(DOMString input){
    unsigned int temp;
    for (auto it=input.begin(); it<input.end()){
        temp = utf8::next(it, input.end());
        if (temp==9 || temp==10 || temp==12 || temp==13 || temp==32 || temp==0 || temp==62){
            return false;
        }
    }
    return true;
}

/*
God knows what this does ! Just followed the documentation: 
https://dom.spec.whatwg.org/#validate-and-extract
*/
void ValidateAndExtract(std::optional<DOMString> &namesp,DOMString qualifiedName, DOMString context,std::optional<DOMString> &prefix,DOMString &localName){
    if (namesp!=std::nullopt && namesp.value()==""){ namesp = std::nullopt; }
    prefix = std::nullopt;
    localName = qualifiedName;
    if (qualifiedName.find(":")!=std::string::npos){
        std::vector<DOMString> splitResult = SplitText(qualifiedName, ":");
        prefix = splitResult[0];
        localName = splitResult[1];
        if (!ValidNamespacePrefix(prefix.value())){ throw InvalidCharacterError("Invalid chars !!"); }
    }`
    assert((prefix==std::nullopt) || ValidNamespacePrefix(prefix));
    if (context=="attribute" && !ValidAttributeLocalName(localName)){ throw InvalidCharacterError("Invalid chars !"); }
    if (context=="element" && !validElementLocalName(localName)){ throw InvalidCharacterError("Invalid chars !!"); }
    if (prefix != std::nullopt && namesp==std::nullopt){ throw NamespaceError("Namespace error !!"); }
    if (prefix != std::nullopt && prefix.value()=="xml" && namesp!="http://www.w3.org/XML/1998/namespace"){ throw NamespaceError("Namespace error !!"); }
    if ((qualifiedName=="xmlns" ||(prefix!=std::nullopt && prefix.value()=="xmlns")) && namesp!="http://www.w3.org/2000/xmlns/"){ throw NamespaceError("Namespace error !!"); }
    if (namesp!="http://www.w3.org/2000/xmlns/" && (qualifiedName!="xmlns" && (prefix==std::nullopt ||(prefix!=std::nullopt && prefix.value()!="xmlns")))){ throw NamespaceError("Namespace error !!"); }
}