#include "../src/Webelo.cpp"
#include <iostream>


int main(){
    // Creating an element
    Element* html = new Element("custom","some_prefix","html");

    // Setting id
    html->id = std::string("the_id_we_set_in_css");


    // Adding event listener with MouseEvent
    DOMString typestring = "mouse";
    EventListener* el = new EventListener();
    std::variant<AddEventListenerOptions,bool> options = false;
    html->addEventListener(typestring,el,options);

    // Now it listens to it
    Event* some_event = new MouseEvent(typestring);

    // Now, it will detect it :)
    html->dispatchEvent(some_event);
}