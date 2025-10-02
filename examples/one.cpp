#include "../src/Webelo.cpp"
#include <iostream>


int main(){
    Element* html = new Element("custom","some_prefix","html");
    html->id = "the_id_we_set_in_css";

    void hello(){
        std::cout<<"hi";
    }

    DOMString typestring = "mouse";
    // Creating an event like in javascript
    Event* some_event = new MouseEvent(typestring);
    html->addEventListener(typestring,&hello,some_event);

    // Now html listens for a mouse event
}