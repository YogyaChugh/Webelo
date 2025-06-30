#include "events/events.hpp"

class Window{
    private:
        Event event; //Replaceable
    public:
        Event getevent(){
            return event;
        };
};