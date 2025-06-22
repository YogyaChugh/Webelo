# EVENTS

Events allow signalling something has occured and it can be anything from a simple user interaction to a website page loading !<br>
For defining events, DOM Standard provides an IDL definition at [DOM Standard - Events](https://dom.spec.whatwg.org/#events).

> Reference: https://developer.mozilla.org/en-US/docs/Web/API/Event

## Our C++ Implementation

Definition and meaning for all attributes & methods along with info for JS Binding.

> Almost all attributes are private and can only be accessed by member functions<br> Therefore, getter and setter functions for easier access are being provided for both read-only and full-access attributes !

### Read-only Attributes

`DOMString type`
- Initially, "" (empty string)
- Type of the Event like `click`, `haschange`, `submit`, etc...

`EventTarget target`
- can be null
- The Original Element that triggered the event. It is reference to the object to which the event was originally dispatched.

> **EventTarget srcElement** is legacy support only for `target`. Only 

`Eventtarget relatedTarget`
- can be null
- For reference only, like storing the element the mouse came from or is going to !

`EventTarget currentTarget`
- can be null
- It's value is present only inside an event handler. Outside it, it will be null
- It stores the element to which the event handler is currently pointing to.
- Basically, it's null when `dispatchEvent()` is called from code, else when user interacts, it got an eventHandler and therefore, it's not null.

`unsigned int eventPhase`
- Initially, NONE (0)
- Indicates which phase of the event flow is currently being evaluated.
- Can be NONE, CAPTURING_PHASE, AT_TARGET or BUBBLING_PHASE.
- Implemented using enum

`bool bubbles`
- Indicates whether the event bubbles up the DOM tree or not.

`bool cancelable`
- Indicates whether the event can be canceled, and therefore prevented as if the event never happened.
- If the event is not cancelable, then its cancelable property will be false and the event listener cannot stop the event from occurring.

`bool composed`
- Indicates whether or not the event will propagate across the shadow DOM boundary into the standard DOM.
- In layman terms, whether while creating path, will it go inside the shadow DOM or not !