#include "events/events.hpp"

class Window{
    private:
        std::optional<Event> event; //Replaceable
    public:
        Event getevent(){
            return event;
        };
};