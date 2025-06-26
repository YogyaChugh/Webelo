#include "events/events.hpp"

class Window{
    private:
        Event event; //Replaceable
    public:
        Event event(){
            return event;
        };
};