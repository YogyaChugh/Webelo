# DOM

A `Document Object Model` for storing and working of tree for HTML and XML documents.
It defines a tree with preorder depth first traversal order.

## What exactly is it ??
Basically, it is a tree implementation strictly abiding to the rules of the [DOM STANDARD](https://dom.spec.whatwg.org/) defined by an organization named [WhatWG](https://whatwg.org/).

It is the `intermediate` which is created when `HTML` is parsed.

So let's understand this clearly ! In broader sense:-

When we load a website, its HTML, CSS and JS is fetched and every component is parsed.
<br>
- First `HTML` is parsed and `DOM` ( Document Object Model ) tree is created !
- Then `CSS` is parsed and `CSSOM` ( CSS Object Model ) is created !
- Both the `DOM` and `CSSOM` are combined to create the `Render Tree` !
- Finally using the `Render Tree`, we see the website on the screen after<br> some processes of layout, painting , compositing, etc..

> This repository implements the `DOM tree` for the HTML parsing !

## Interesting Fact
There are so many browsers in the world like Google Chrome, Brave, Microsoft Edge, Firefox,etc.. but how is it that a website looks the same on all of them ???<br><br>
`Reason`
<br>
This is possible because of the `standards` that all browsers or specifically rendering engines follow !<br> And that's what we are doing here, following the [DOM Standard](https://dom.spec.whatwg.org/) by [WhatWG](https://whatwg.org/) !

## Running
Currently, the base classes are being defined so running it won't do anything ! Implementation for API coming soon...

## Contributing
Yup ! Anyone can contribute, just know c++ and dive into the documentation ! But don't get bored, there's HTML Parser and browser coming up after that ! It's a chain !

## Bindings
Bindings for Python, Rust and JS will be available after initial release.

<p>
  <img src="https://hackatime-badge.hackclub.com/U09218J0E94/DOM" alt="Typing animation">
</p>