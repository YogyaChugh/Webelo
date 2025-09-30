#include "src/Webelo.cpp"
#include <variant>


class ElementInternals;
class HTMLElement;
class HTMLFormElement;
class CustomStateSet{
    std::vector<DOMString> states;
};
class HTMLUnknownElement;
class DOMStringMap;
class HTMLOrSVGElement;

struct ShowPopoverOptions{
    HTMLElement source;
};

struct TogglePopoverOptions: public ShowPopoverOptions{
    bool force;
};

struct ValidityStateFlags {
    bool valueMissing = false;
    bool typeMismatch = false;
    bool patternMismatch = false;
    bool tooLong = false;
    bool tooShort = false;
    bool rangeUnderflow = false;
    bool rangeOverflow = false;
    bool stepMismatch = false;
    bool badInput = false;
    bool customError = false;
};

struct ValidityState {
  bool valueMissing;
  bool typeMismatch;
  bool patternMismatch;
  bool tooLong;
  bool tooShort;
  bool rangeUnderflow;
  bool rangeOverflow;
  bool stepMismatch;
  bool badInput;
  bool customError;
  bool valid;
};

struct FocusOptions{
    bool preventScroll = false;
    bool focusVisible;
};

class ElementInternals{
    public:
        ShadowRoot* shadowRoot;
        void setFormValue(USVString value, USVString state);
        HTMLFormElement* form;

        void setValidity(ValidityStateFlags flags = {}, DOMString message, HTMLElement* anchor);
        bool willValidate;
        ValidityState validity;
        DOMString validationMessage;
        bool checkValidity();
        bool reportValidity();

        NodeList labels;

        CustomStateSet states;
};

class DOMStringMap{
    public:
        DOMString get(DOMString name);
        void set(DOMString name, DOMString value);
        void del(DOMString name);
};

class HTMLElement: public Element{
    public:
        HTMLElement(): Element(DOMString(""), DOMString(""), DOMString("")){}

        DOMString title;
        DOMString lang;
        bool translate;
        DOMString dir;
        std::variant<bool, double, DOMString> hidden;
        bool inert;

        void click();

        DOMString accessKey;

        DOMString accessKeyLabel;
        bool draggable;
        bool spellcheck;
        DOMString writingSuggestions;
        DOMString autocapitalize;
        bool autocorrect;

        DOMString innerText;
        DOMString outerText;

        ElementInternals attachInternals();

        void showPopover(ShowPopoverOptions options = {});
        void hidePopover();
        bool togglePopover(std::variant<TogglePopoverOptions, bool> optinos = {});
        DOMString popover;

        unsigned long headingOffset;
        bool headingReset;


        DOMStringMap dataset;
        DOMString nonce;
        bool autofocus;
        long tabIndex;
        void focus(FocusOptions options = {});
        void blur();

};


class HTMLUnknownElement: public HTMLElement{};








class HTMLHtmlElement: HTMLElement{
    public:
        HTMLHtmlElement();
};

class HTMLHeadElement: HTMLElement{
    public:
        HTMLHeadElement();
};

class HTMLTitleElement: HTMLElement{
    public:
        HTMLTitleElement();
        DOMString text;
};

class HTMLBaseElement: HTMLElement{
    public:
        HTMLBaseElement();
        USVString href;
        DOMString target;
};


class HTMLLinkElement: HTMLElement{
    public:
        HTMLLinkElement();
};