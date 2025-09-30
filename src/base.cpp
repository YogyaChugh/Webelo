#ifndef BASE_DOM
#define BASE_DOM

#include <string>
#include <optional>
#include <cstdarg>
#include <vector>
#include <ctime>
#include "utf8.h"


typedef std::string DOMString;
typedef std::string USVString;
typedef time_t DOMHighResTimeStamp;
class Realm{};

class EventHandler{};
class CustomElementRegistry{};



std::vector<DOMString> split_text(DOMString input, DOMString del){
    std::vector<DOMString> temp = {};
    int end = 0; int start = 0;
    while (end!=-1){
        end = input.find(del, start);
        temp.push_back(input.substr(start, end-start));
        start = end + del.size();
    }
    return temp;
}

// From the INFRA Standard
std::vector<DOMString> split_text_multiple(DOMString input, std::vector<int> del){
    std::vector<DOMString> temp = {};
    unsigned int i = 0;
    DOMString tempText = "";
    bool notFound = true;
    auto previt = input.begin();
    for (auto it = input.begin();it!=input.end();){
        notFound = true;
        previt = it;
        i = utf8::next(it, input.end());
        for (int j: del){
            if (i==j){
                notFound = false;
                temp.push_back(tempText);
                tempText = "";
                break;
            }
        }
        if (notFound){
            tempText.append(previt, it);
        }
    }
    temp.push_back(tempText);
    return temp;
}


int main(){}


#endif