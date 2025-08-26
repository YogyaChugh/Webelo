#include "include/nodes/node.hpp"
#include "include/nodes/document.hpp"
#include "include/base.hpp"
#include <set>
#include <string>
#include <vector>


std::set<DOMString> ParseOrderedSet(DOMString input){
    std::vector<DOMString> inputTokens = SplitText(input, " ");
    std::set<DOMString> tokens;
    for (auto a: inputTokens){
        tokens.insert(a);
    }
    return tokens;
}

DOMString SerializeOrderedSet(std::set<DOMString> input){
    DOMString str = "";
    for (auto a: input){
        str += a;
    }
    return str;
}

bool ValidNamespacePrefix(DOMString input){
    if (input.size()==0){ return false; }
    for (auto a: input){
        if ((int)a ==9 || (int)a ==10 || (int)a ==12 || (int)a == 13 || (int)a ==32 || (int)a ==0 || (int)a ==47 || (int)a ==62){
            return false;
        }
    }
    return true;
}

bool ValidAttributeLocalName(DOMString input){
    if (input.size()==0){ return false; }
    for (auto a: input){
        if ((int)a ==9 || (int)a ==10 || (int)a ==12 || (int)a == 13 || (int)a ==32 || (int)a ==0 || (int)a ==47 || (int)a ==62 || (int)a ==61){
            return false;
        }
    }
    return true;
}

bool validElementLocalName(DOMString input){
    if (input.size()==0){ return false; }
    if ((input.at(0)>=65 && input.at(0)<=90) || (input.at(0)>=97 && input.at(0)<=122)){
        for (auto a: input){
            if ((int)a ==9 || (int)a ==10 || (int)a ==12 || (int)a == 13 || (int)a ==32 || (int)a ==0 || (int)a ==47 || (int)a ==62){
                return false;
            }
        }
        return true;
    }
    if ((int)a!=58 && (int)a!=95)
    return true;
}

bool validDocTypeName(DOMString input){
    for (auto a: input){
        if ((int)a ==9 || (int)a ==10 || (int)a ==12 || (int)a == 13 || (int)a ==32 || (int)a ==0 || (int)a ==62){
            return false;
        }
    }
    return true;
}

ValidateAndExtract(std::optional<DOMString> namesp,DOMString qualifiedName,std::optional<DOMString> &prefix,DOMString &localName){
    if (namesp.value==""){ namesp = std::nullopt; }
    prefix = std::nullopt;
    localName = qualifiedName;
    if (qualifiedName.find(":")!=-1){
        StrictSplitText
    }
}