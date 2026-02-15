# WEBELO

Rendering Engine for Browsers

Currently, An HTML Visualizer & DOM Library but rendering engine's base is DOM and building the pyramid ...

## DOM

A `Document Object Model` for storing and working of tree for HTML and XML documents.

Alongside, it consists of an `HTML Visualizer` to visualize how your html looks to the browser.

It defines a complex tree of classes with preorder depth first traversal order.

### What exactly is it ??
Basically, it is a very complex tree implementation strictly abiding to the rules of the [DOM STANDARD](https://dom.spec.whatwg.org/) defined by an organization named [WhatWG](https://whatwg.org/).

It is the most crucial part of a browser & they basically depend on this.
The functions you use `addEventListener()`, `dipatchEvent()`, `document.write()`, etc.. are all written in this library :)

It is the `intermediate` which is created when `HTML` is parsed.

So let's understand this clearly ! In broader sense:-

When we load a website, its HTML, CSS and JS is fetched and every component is parsed.
<br>
- First `HTML` is parsed and `DOM` ( Document Object Model ) tree is created !
- Then `CSS` is parsed and `CSSOM` ( CSS Object Model ) is created !
- Both the `DOM` and `CSSOM` are combined to create the `Render Tree` !
- Finally using the `Render Tree`, we see the website on the screen after<br> some processes of layout, painting , compositing, etc..

> This repository implements the `DOM tree` for the HTML parsing !

### Interesting Fact
There are so many browsers in the world like Google Chrome, Brave, Microsoft Edge, Firefox,etc.. but how is it that a website looks the same on all of them ???<br><br>
`Reason`
<br>
This is possible because of the `standards` that all browsers or specifically rendering engines follow !<br> And that's what we are doing here, following the [DOM Standard](https://dom.spec.whatwg.org/) by [WhatWG](https://whatwg.org/) !

### Running
There are 2 parts:
1) HTML Visualizer - Running executables from [Releases]("https://github.com/YogyaChugh/Webelo/release/latest") - (It runs the library using bindings too, but mainly written in Python)
2) DOM Library - Just clone this repository and include the `src/Webelo.cpp` in your file and you are set yo go !!

> You can run the examples [here](https://github.com/YogyaChugh/Webelo/tree/master/examples) to test bro/sis !!

### Documentation
Docs are available at https://webelo.onrender.com for DOM Library

### Contributing
Yup ! Anyone can contribute, just know c++ and dive into the documentation ! But don't get bored, there's HTML Parser and browser coming up after that ! It's a chain !

### Bindings
Bindings for Python, Rust and JS will be available after initial release.