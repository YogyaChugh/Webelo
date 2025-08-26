#ifndef BASE_DOM
#define BASE_DOM

#include <string>
#include <optional>
#include <cstdarg>
#include <vector>


typedef std::string DOMString;
typedef std::string USVString;
class Realm{};

class EventHandler{};
class CustomElementRegistry{};

class DOMTokenList{
    public:
        std::optional<DOMString> item(unsigned long index);
        bool contains(DOMString token);

        //CEReactions
        void add(...);
        void remove(...);
        bool toggle(DOMString token, DOMString newToken);
        DOMString value; //TODO: Implement stringifier
        
        bool supports(DOMString token);
        std::vector<DOMString> list;
};



std::vector<DOMString> SplitText(DOMString input, DOMString del){
    std::vector<DOMString> temp = {};
    int end = 0; int start = 0;
    while (end!=-1){
        end = input.find(del, start);
        temp.push_back(input.substr(start, end-start));
        start = end + del.size();
    }
    return temp;
}

void StrictSplitText(DOMString input, DOMString);


#endif