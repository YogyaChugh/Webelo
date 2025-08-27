#include "include/nodes/node.hpp"
#include "include/nodes/document.hpp"
#include "include/base.hpp" //
#include <set> //
#include <string> //
#include <vector> //


std::set<DOMString> ParseOrderedSet(DOMString input){
    std::vector<DOMString> inputTokens = SplitText(input, " ");
    std::set<DOMString> tokens;
    for (DOMString a: inputTokens){
        tokens.insert(a);
    }
    return tokens;
}

DOMString SerializeOrderedSet(std::set<DOMString> input){
    DOMString str = L"";
    for (size_t i=0;i<input.size();i++){
        str+=input[i];
        if (i!=(input.size()-1)){
            str+=" ";
        }
    }
    return str;
}

bool ValidNamespacePrefix(DOMString input){
    if (input.size()==0){ return false; }
    int temp;
    for (char a: input){
        temp = (int)a;
        if (temp==9 || temp==10 || temp==12 || temp==13 || temp==32 || temp==0 || temp==47 || temp==62){
            return false;
        }
    }
    return true;
}

bool ValidAttributeLocalName(DOMString input){
    if (input.size()==0){ return false; }
    int temp;
    for (char32_t a: input){
        temp = (int)a;
        if (temp==9 || temp==10 || temp==12 || temp==13 || temp==32 || temp==0 || temp==47 || temp==61 || temp==62){
            return false;
        }
    }
    return true;
}

bool validElementLocalName(DOMString input){
    if (input.size()==0){ return false; }
    std::string first = (int)input[0];
    int temp;
    if ((first>=65 && first<=90) || (first>=97 && first<=122)){
        for (auto a: input){
            temp = (int)a;
            if (temp==9 || temp==10 || temp==12 || temp==13 || temp==32 || temp==0 || temp==47 || temp==62){
                return false;
            }
        }
        return true;
    }
    if (first!=58 && first!=95 && (first<128 || first>1114111)){
        return false;
    }
    for (auto a: input){
        temp = (int)a;
        if ((temp<65 || temp>90) && (temp<97 || temp>122) && (temp<48 || temp>57) && temp!=45 && temp!=46 && temp!=58 && temp!=95 && (temp<128 || temp>1114111)){
            return false;
        }
    }
    return true;
}

bool validDocTypeName(DOMString input){
    int temp;
    for (char32_t a: input){
        temp = (int)a;
        if (temp==9 || temp==10 || temp==12 || temp==13 || temp==32 || temp==0 || temp==62){
            return false;
        }
    }
    return true;
}

ValidateAndExtract(std::optional<DOMString> namesp,DOMString qualifiedName,std::optional<DOMString> &prefix,DOMString &localName){
    if (namesp.value==""){ namesp = std::nullopt; }
    prefix = std::nullopt;
    localName = qualifiedName;
    if (qualifiedName.find(":")!=std::string::npos){
        
    }
}