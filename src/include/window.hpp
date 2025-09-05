#ifndef "WINDOW_DOM"
#define "WINDOW_DOM"

#include "events/events.hpp"

class Window{
    //TODO: LATER DO IT FULL !
    protected:
        Event* event = nullptr; //Replaceable
    public:
        Event* getEvent(){
            return this->event;
        }
};

#endif