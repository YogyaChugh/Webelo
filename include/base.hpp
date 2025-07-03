#pragma once

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