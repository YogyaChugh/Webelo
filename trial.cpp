#include <string>
#include <vector>
#include <cassert>
#include <iostream>

using namespace std;

class HTMLElement
{
public:
  string tagName;
  vector<struct HTMLElement *> children;
  struct HTMLElement *parentElement;
  string textContent;

  void printit(int level = 0){
	int level2 = level+1;
	for (auto a: this->children){
		string space = "";
		for(int i=0; i<level; i++){ space+=" "; }
		cout<<space<<a->tagName<<endl;
		a->printit(level2);
	}
  }
};

enum State
{
  STATE_INIT,
  STATE_START_TAG,
  STATE_READING_TAG,
  STATE_READING_ATTRIBUTES,
  STATE_END_TAG,
  STATE_BEGIN_CLOSING_TAG
};

bool isWhitespace(char c)
{
  return c == ' ';
}

HTMLElement *HTMLParser(string input)
{
  HTMLElement *root = new HTMLElement();

  State state = STATE_INIT;
  HTMLElement *lastParent = root;
  string tagName = "";

  for (auto c : input) {
    if (c == '<') {
      state = STATE_START_TAG;
    } else if (state == STATE_START_TAG) {
      if (c == '/') {
        state = STATE_BEGIN_CLOSING_TAG;
      } else if (!isWhitespace(c)) {
        state = STATE_READING_TAG;
        tagName = c;
      }
    } else if (state == STATE_READING_TAG) {
      if (isWhitespace(c)) {
        state = STATE_READING_ATTRIBUTES;
      } else if(c == '>') {
        state = STATE_END_TAG;

        auto parent = new HTMLElement(); 
        parent->tagName = tagName;
        parent->parentElement = lastParent;

        lastParent->children.push_back(parent);
        lastParent = parent;
      } else {
        tagName += c;
      }
    } else if(state == STATE_READING_ATTRIBUTES) {
      if (c == '>') {
        state = STATE_END_TAG;

        auto parent = new HTMLElement(); 
        parent->tagName = tagName;
        parent->parentElement = lastParent;

        lastParent->children.push_back(parent);
        lastParent = parent;
      }
    } else if (state == STATE_END_TAG) {
      lastParent->textContent += c;
    } else if (state == STATE_BEGIN_CLOSING_TAG) {
      if (c == '>') {
        lastParent = lastParent->parentElement;
      }
    }
  }

  return root;
}

int main()
{
  string html = R"(<!DOCTYPE html>
	<!-- saved from url=(0020)https://example.com/ -->
	<html><head><meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
	    <title>Example Domain</title>
	
	
	
	    <meta name="viewport" content="width=device-width, initial-scale=1">
	    <style type="text/css">
	    body {
	        background-color: #f0f0f2;
	        margin: 0;
	        padding: 0;
	        font-family: -apple-system, system-ui, BlinkMacSystemFont, "Segoe UI", "Open Sans", "Helvetica Neue", Helvetica, Arial, sans-serif;
	
	    }
	    div {
	        width: 600px;
	        margin: 5em auto;
	        padding: 2em;
	        background-color: #fdfdff;
	        border-radius: 0.5em;
	        box-shadow: 2px 3px 7px 2px rgba(0,0,0,0.02);
	    }
	    a:link, a:visited {
	        color: #38488f;
	        text-decoration: none;
	    }
	    @media (max-width: 700px) {
	        div {
	            margin: 0 auto;
	            width: auto;
	        }
	    }
	    </style>    
	</head>
	
	<body>
	<div>
	    <h1>Example Domain</h1>
	    <p>This domain is for use in illustrative examples in documents. You may use this
	    domain in literature without prior coordination or asking for permission.</p>
	    <p><a href="https://www.iana.org/domains/example">More information...</a></p>
	</div>
	
	
	</body></html>)";
  HTMLElement *el = HTMLParser(html);

  assert(el->children.size() == 1);

  el->printit();

  return 0;
}