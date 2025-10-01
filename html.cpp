#include "src/Webelo.cpp"
#include <variant>
#include "src/base.cpp"
#include "src/exceptions.cpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <iostream>
namespace py = pybind11;


class HTMLUnknownElement;
class HTMLElement;
class DOMStringMap;
class ElementInternals;
class HTMLModElement;
class HTMLBRElement;
class HTMLSpanElement;
class HTMLTimeElement;
class HTMLDataElement;
class HTMLAnchorElement;
class HTMLDivElement;
class HTMLDListElement;
class HTMLLIElement;
class HTMLMenuElement;
class HTMLOListElement;
class HTMLQuoteElement;
class HTMLPreElement;
class HTMLHRElement;
class HTMLParagraphElement;
class HTMLHeadingElement;
class HTMLBodyElement;
class HTMLStyleElement;
class HTMLMetaElement;
class HTMLLinkElement;
class HTMLBaseElement;
class HTMLTitleElement;
class HTMLHeadElement;
class HTMLHtmlElement;
class HTMLPictureElement;
class HTMLSourceElement;
class HTMLImageElement;
class HTMLIFrameElement;
class HTMLEmbedElement;
class HTMLObjectElement;
class MediaError;
class TimeRanges;
class AudioTrackList;
class AudioTrack;
class VideoTrackList;
class VideoTrack;
class TextTrackCue;
class TextTrackCueList;
class TextTrackList;
class TextTrack;
class HTMLMediaElement;
class HTMLVideoElement;
class HTMLAudioElement;
class HTMLTrackElement;
class HTMLMapElement;
class HTMLAreaElement;
class HTMLTableCaptionElement;
class HTMLTableCellElement;
class HTMLTableRowElement;
class HTMLTableColElement;
class HTMLTableSectionElement;
class HTMLTableElement;
class RadioNodeList;
class HTMLFormControlsCollection;
class HTMLFormElement;
class HTMLLabelElement;
class HTMLInputElement;
class HTMLButtonElement;
class HTMLOptionElement;
class HTMLOptionsCollection;
class HTMLSelectElement;
class HTMLDataListElement;
class HTMLOptGroupElement;
class HTMLTextAreaElement;
class HTMLOutputElement;
class HTMLProgressElement;
class HTMLMeterElement;
class HTMLFieldSetElement;
class HTMLLegendElement;
class HTMLSelectedContentElement;
class SubmitEvent;
class FormDataEvent;
class HTMLDetailsElement;
class HTMLDialogElement;


enum CanPlayTypeResult{
    empty,
    maybe,
    probably
};

enum TextTrackMode{
    disabled,
    hidden,
    showing
};

enum TextTrackKind{
    subtitles,
    captions,
    descriptions,
    chapters,
    metadata
};


enum SelectionMode{
    select,
    start,
    end,
    preserve
};


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
    HTMLElement* source;
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

        void setValidity(ValidityStateFlags flags, DOMString message, HTMLElement* anchor);
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
        DOMString lang = "en";
        bool translate;
        DOMString dir;
        std::variant<bool, double, DOMString> hidden;
        bool inert;

        DOMString classname;
        DOMString id;

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

        void showPopover(ShowPopoverOptions options);
        void hidePopover();
        bool togglePopover(std::variant<TogglePopoverOptions, bool> options = {});
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








class HTMLHtmlElement: public HTMLElement{
    public:
        HTMLHtmlElement(){};
};

class HTMLHeadElement: public HTMLElement{
    public:
        HTMLHeadElement(){};
};

class HTMLTitleElement: public HTMLElement{
    public:
        HTMLTitleElement(){};
        DOMString text;
};

class HTMLBaseElement: public HTMLElement{
    public:
        HTMLBaseElement(){};
        USVString href;
        DOMString target;
};


class HTMLLinkElement: public HTMLElement{
    public:
        HTMLLinkElement(){};

        USVString href;
        DOMString crossOrigin;
        DOMString rel;
        DOMString as;
        DOMTokenList relList;
        DOMString media;
        DOMString integrity;
        DOMString hreflang;
        DOMString type;
        DOMTokenList sizes;
        USVString imageSrcset;
        DOMString imageSizes;
        DOMString referrerPolicy;
        DOMTokenList blocking;
        bool disabled;
        DOMString fetchPriority;
};


class HTMLMetaElement: public HTMLElement{
    public:
        HTMLMetaElement(){};

        DOMString name;
        DOMString httpEquiv;
        DOMString content;
        DOMString media;
};


class HTMLStyleElement: public HTMLElement{
    public:
        HTMLStyleElement(){};

        bool disabled;
        DOMString media;
        DOMTokenList blocking;
};




/* already
aside
nav
section
article
hgroup
header
footer
address
dt
dd
figure
figcaption
main
search
em
strong
small
s
cite
q
dfn
abbr
ruby
rt
rp
code
var
samp
kbd
sub
sup
i
b
u
mark
bdi
bdo
wbr
ins
del
col
thead
tfoot
th
*/


class HTMLBodyElement: public HTMLElement{
    public:
        HTMLBodyElement(){};
};

class HTMLHeadingElement: public HTMLElement{
    public:
        HTMLHeadingElement(){};
};

class HTMLParagraphElement: public HTMLElement{
    public:
        HTMLParagraphElement(){};
};

class HTMLHRElement: public HTMLElement{
    public:
        HTMLHRElement(){};
};

class HTMLPreElement: public HTMLElement{
    public:
        HTMLPreElement(){};
};

class HTMLQuoteElement: public HTMLElement{
    public:
        HTMLQuoteElement(){};
        USVString cite;
};

class HTMLOListElement: public HTMLElement{
    public:
        HTMLOListElement(){};
        bool reversed;
        long start;
        DOMString type;
};

class HTMLUListElement: public HTMLElement{
    public:
        HTMLUListElement(){};
};

class HTMLMenuElement: public HTMLElement{
    public:
        HTMLMenuElement(){};
};

class HTMLLIElement: public HTMLElement{
    public:
        HTMLLIElement(){};
        long value;
};

class HTMLDListElement: public HTMLElement{
    public:
        HTMLDListElement(){};
};

class HTMLDivElement: public HTMLElement{
    public:
        HTMLDivElement(){};
};

class HTMLAnchorElement: public HTMLElement{
    public:
        HTMLAnchorElement(){};

        DOMString target;
        DOMString download;
        USVString ping;
        DOMString rel;
        DOMTokenList relList;
        DOMString hreflang;
        DOMString type;
        DOMString text;
        DOMString referrerPolicy;


        USVString href;
        USVString origin;
        USVString protocol;
        USVString username;
        USVString password;
        USVString host;
        USVString hostname;
        USVString port;
        USVString pathname;
        USVString search;
        USVString hash;
};

class HTMLDataElement: public HTMLElement{
    public:
        HTMLDataElement(){};

        DOMString value;
};

class HTMLTimeElement: public HTMLElement{
    public:
        HTMLTimeElement(){};

        DOMString dateTime;
};

class HTMLSpanElement: public HTMLElement{
    public:
        HTMLSpanElement(){};
};

class HTMLBRElement: public HTMLElement{
    public:
        HTMLBRElement(){};
};

class HTMLModElement: public HTMLElement{
    public:
        HTMLModElement(){};

        USVString cite;
        DOMString dateTime;
};

class HTMLPictureElement: public HTMLElement{
    public:
        HTMLPictureElement(){};
};

class HTMLSourceElement: public HTMLElement{
    public:
        HTMLSourceElement(){};

        USVString src;
        DOMString type;
        USVString srcset;
        DOMString sizes;
        DOMString media;
        unsigned long width;
        unsigned long height;
};

class HTMLImageElement: public HTMLElement{
    public:
        HTMLImageElement(){};

        DOMString alt;
        USVString src;
        USVString srcset;
        DOMString sizes;
        DOMString crossOrigin;
        DOMString useMap;
        bool isMap;
        unsigned long width;
        unsigned long height;
        unsigned long naturalHeight;
        unsigned long naturalWidth;
        bool complete;
        USVString currentSrc;
        DOMString referrerPolicy;
        DOMString decoding;
        DOMString loading;
        DOMString fetchPriority;

        void decode();
};

class HTMLIFrameElement: public HTMLElement{
    public:
        HTMLIFrameElement(){};

        USVString src;
        DOMString srcdoc;
        DOMString name;
        DOMTokenList sandbox;
        DOMString allow;
        bool allowFullscreen;
        DOMString width;
        DOMString height;
        DOMString referrerPolicy;
        DOMString loading;
        Document* contentDocument;
        Document* getSVGDocument();
};


class HTMLEmbedElement: public HTMLElement{
    public:
        HTMLEmbedElement(){};

        USVString src;
        DOMString type;
        DOMString width;
        DOMString height;
        Document* getSVGDocument();
};

class HTMLObjectElement: public HTMLElement{
    public:
        HTMLObjectElement(){};

        USVString data;
        DOMString type;
        DOMString name;
        HTMLFormElement* form;
        DOMString width;
        DOMString height;
        Document* contentDocument;
        Document* getSVGDocument();

        bool willValidate;
        ValidityState validity;
        DOMString validationMessage;
        bool checkValidity();
        bool reportValidity();
        void setCustomValidity(DOMString error);
};

class MediaError{
    public:
        const unsigned short MEDIA_ERR_ABORTED = 1;
        const unsigned short MEDIA_ERR_NETWORK = 2;
        const unsigned short MEDIA_ERR_DECODE = 3;
        const unsigned short MEDIA_ERR_SRC_NOT_SUPPORTED = 4;

        unsigned short code;
        DOMString message;
};

class TimeRanges{
    public:
        unsigned long length;
        double start(unsigned long index);
        double end(unsigned long index);
};

class AudioTrackList: public EventTarget{
    public:
        unsigned long length;
        AudioTrack get(unsigned long index);
        AudioTrack* getTrackById(DOMString id);

        EventHandler onchange;
        EventHandler onaddtrack;
        EventHandler onremovetrack;
};

class AudioTrack{
    public:
        DOMString id;
        DOMString kind;
        DOMString label;
        DOMString language;
        bool enabled;
};

class VideoTrackList: public EventTarget{
    public:
        unsigned long length;
        VideoTrack get(unsigned long index);
        VideoTrack* getTrackById(DOMString id);
        long selectedIndex;

        EventHandler onchange;
        EventHandler onaddtrack;
        EventHandler onremovetrack;
};

class VideoTrack{
    public:
        DOMString id;
        DOMString kind;
        DOMString label;
        DOMString language;
        bool selected;
};



class TextTrackCue: public EventTarget{
    public:
        TextTrack* track;

        DOMString id;
        double startTime;
        double endTime;
        bool pauseOnExit;

        EventHandler onenter;
        EventHandler onexit;
};

class TextTrackCueList{
    public:
        unsigned long length;
        TextTrackCue get(unsigned long index);
        TextTrackCue* getCueById(DOMString id);
};


class TextTrack: public EventTarget{
    public:
        TextTrackKind kind;
        DOMString label;
        DOMString language;
        DOMString id;
        DOMString inBandMetadataTrackDispatchType;

        TextTrackMode mode;
        TextTrackCueList* cues;
        TextTrackCueList* activeCues;

        void addCue(TextTrackCue cue);
        void removeCue(TextTrackCue cue);

        EventHandler oncuechange;
};

class TextTrackList: public EventTarget{
    public:
        unsigned long length;
        TextTrack get(unsigned long index);
        TextTrack* getTrackById(DOMString id);

        EventHandler onchange;
        EventHandler onaddtrack;
        EventHandler onremovetrack;
};


class HTMLMediaElement: public HTMLElement{
    public:

        HTMLMediaElement(){};
        MediaError* error;

        USVString src;
        USVString currentSrc;
        DOMString crossOrigin;
        const unsigned short NETWORK_EMPTY = 0;
        const unsigned short NETWORK_IDLE = 1;
        const unsigned short NETWORK_LOADING = 2;
        const unsigned short NETWORK_NO_SOURCE = 3;

        unsigned short networkState;
        DOMString preload;
        TimeRanges buffered;
        void load();
        CanPlayTypeResult canPlayType(DOMString type);

        const unsigned short HAVE_NOTHING = 0;
        const unsigned short HAVE_METADATA = 1;
        const unsigned short HAVE_CURRENT_DATA = 2;
        const unsigned short HAVE_FUTURE_DATA = 3;
        const unsigned short HAVE_ENOUGH_DATA = 4;

        unsigned short readyState;
        bool seeking;



        double currentTime;
        void fastSeek(double time);
        double duration;
        void getStartDate();
        bool paused;
        double defaultPlaybackRate;
        double playbackRate;
        bool preservesPitch;
        TimeRanges played;
        TimeRanges seekable;
        bool ended;
        bool autoplay;
        bool loop;
        void play();
        void pause();

        bool controls;
        double volume;
        bool muted;
        bool defaultMuted;

        AudioTrackList audioTracks;
        VideoTrackList videoTracks;
        TextTrackList textTracks;

        TextTrack addTextTrack(TextTrackKind kind, DOMString label = std::string(""), DOMString language = std::string(""));
};


class HTMLVideoElement: public HTMLMediaElement{
    public:
        HTMLVideoElement(){};

        unsigned long width;
        unsigned long height;
        unsigned long videoWidth;
        unsigned long videoHeight;
        USVString poster;
        bool playsInline;
};

class HTMLAudioElement: public HTMLMediaElement{
    public:
        HTMLAudioElement(){};
};

class HTMLTrackElement: public HTMLElement{
    public:
        HTMLTrackElement(){};

        DOMString kind;
        USVString src;
        DOMString srclang;
        DOMString label;
        bool defaul;

        const unsigned short NONE = 0;
        const unsigned short LOADING = 1;
        const unsigned short LOADED = 2;
        const unsigned short ERROR = 3;
        unsigned short readyState;

        TextTrack track;
};

class HTMLMapElement: public HTMLElement{
    public:
        HTMLMapElement(){};

        DOMString name;
        HTMLCollection areas;
};


class HTMLAreaElement: public HTMLElement{
    public:
        HTMLAreaElement(){};

        DOMString alt;
        DOMString coords;
        DOMString shape;
        DOMString target;
        DOMString download;
        USVString ping;
        DOMString rel;
        DOMTokenList relList;
        DOMString referrerPolicy;

        USVString href;
        USVString origin;
        USVString protocol;
        USVString username;
        USVString password;
        USVString host;
        USVString hostname;
        USVString port;
        USVString pathname;
        USVString search;
        USVString hash;
};

class HTMLTableCaptionElement: public HTMLElement{
    public:
        HTMLTableCaptionElement(){};
};

class HTMLTableCellElement: public HTMLElement{
    public:
        unsigned long colSpan;
        unsigned long rowSpan;
        DOMString headers;
        long cellIndex;
        DOMString scope;
        DOMString abbr;
};

class HTMLTableRowElement: public HTMLElement{
    public:
        HTMLTableRowElement(){};

        long rowIndex;
        long sectionRowIndex;
        HTMLCollection cells;
        HTMLTableCellElement insertCell(long index=-1);
        void deleteCell(long index);
};

class HTMLTableColElement: public HTMLElement{
    public:
        HTMLTableColElement(){};
        unsigned long span;
};

class HTMLTableSectionElement: public HTMLElement{
    public:
        HTMLTableSectionElement(){};

        HTMLCollection rows;
        HTMLTableRowElement insertRow(long index=-1);
        void deleteRow(long index);
};

class HTMLTableElement: public HTMLElement{
    public:
        HTMLTableElement(){};
        
        HTMLTableCaptionElement* caption;
        HTMLTableCaptionElement createCaption();
        void deleteCaption();

        HTMLTableSectionElement* tHead;
        HTMLTableSectionElement createTHead();
        void deleteTHead();

        HTMLTableSectionElement* tFoot;
        HTMLTableSectionElement createTFoot();
        void deleteTFoot();

        HTMLCollection tBodies;
        HTMLTableSectionElement createTBody();

        HTMLCollection rows;
        HTMLTableRowElement insertRow(long index=-1);
        void deleteRow(long index);
};

class RadioNodeList: public NodeList{
    public:
        DOMString value;
};

class HTMLFormControlsCollection: public HTMLCollection{
    public:
        std::variant<RadioNodeList*, Element*> namedItem(DOMString name);
};

class HTMLFormElement: public HTMLElement{
    public:
        HTMLFormElement(){};

        DOMString acceptCharset;
        USVString action;
        DOMString autocomplete;
        DOMString enctype;
        DOMString encoding;
        DOMString method;
        DOMString name;
        bool noValidate;
        DOMString target;
        DOMString rel;
        DOMTokenList relList;

        HTMLFormControlsCollection elements;
        unsigned long index;
        Element* get(unsigned long index);
        std::variant<RadioNodeList*,Element*> get(DOMString name);

        void submit();
        void requestSubmit(HTMLElement* submitter = nullptr);
        void reset();
        bool checkValidity();
        bool reportValidity();
};

class HTMLLabelElement: public HTMLElement{
    public:
        HTMLLabelElement(){};

        HTMLFormElement* form;
        DOMString htmlFor;
        HTMLElement* control;
};


class HTMLInputElement: public HTMLElement{
    public:
        HTMLInputElement(){};

        DOMString accept;
        bool alpha;
        DOMString alt;
        DOMString autocomplete;
        bool defaultChecked;
        bool checked;
        DOMString colorSpace;
        DOMString dirname;
        bool disabled;
        HTMLFormElement* form;
        // FileList* files;
        USVString formAction;
        DOMString formEnctype;
        DOMString formMethod;
        bool formNoValidate;
        DOMString formTarget;
        unsigned long height;
        bool indeterminate;
        HTMLDataListElement* list;
        DOMString max;
        long maxLength;
        DOMString min;
        long minLength;
        bool multiple;
        DOMString name;
        DOMString pattern;
        DOMString placeholder;
        bool readOnly;
        bool required;
        unsigned long size;
        USVString src;
        DOMString step;
        DOMString type;
        DOMString defaultValue;
        DOMString value;

        std::any valueAsData;
        double valueAsNumber;
        unsigned long width;
        void stepUp(long n = 1);
        void stepDown(long n = 1);

        bool willValidate;
        ValidityState validity;
        DOMString validationMessage;
        bool checkValidity();
        bool reportValidity();
        void setCustomValidity(DOMString error);

        NodeList* labels;

        void select();
        unsigned long selectionStart;
        unsigned long selectionEnd;
        DOMString selectionDirection;
        void setRangeText(DOMString replacement);
        void setRangeText(DOMString replacement, unsigned long start, unsigned long end, SelectionMode selectionMode = preserve);
        void setSelectionRange(unsigned long start, unsigned long end, DOMString direction);

        void showPicker();

        Element* popoverTargetElement;
        DOMString popoverTargetAction;
};


class HTMLButtonElement: public HTMLElement{
    public:
        HTMLButtonElement(){};

        DOMString command;
        Element* commandForElement;
        bool disabled;
        HTMLFormElement* form;
        USVString formAction;
        DOMString formEnctype;
        DOMString formMethod;
        bool formNoValidate;
        DOMString formTarget;
        DOMString name;
        DOMString type;
        DOMString value;

        bool willValidate;
        ValidityState validity;
        DOMString validationMessage;
        bool checkValidity();
        bool reportValidity();
        void setCustomValidity(DOMString error);

        NodeList labels;

        Element* popoverTargetElement;
        DOMString popoverTargetAction;
};

class HTMLOptionElement: public HTMLElement{
    public:
        HTMLOptionElement(){};

        bool disabled;
        HTMLFormElement*  form;
        DOMString label;
        bool defaultSelected;
        bool selected;
        DOMString value;

        DOMString text;
        long index;
};

class HTMLOptionsCollection: public HTMLCollection{
    public:
        unsigned long length;
        void set(unsigned long index, HTMLOptionElement* option);
        void add(std::variant<HTMLOptionElement, HTMLOptGroupElement> element, std::variant<HTMLElement*, long> before = nullptr);
        void remove(long index);

        long selectedIndex;
};

class HTMLSelectElement: public HTMLElement{
    public:
        HTMLSelectElement(){};
        DOMString autocomplete;
        bool disabled;
        HTMLFormElement* form;
        bool multiple;
        DOMString name;
        bool required;
        unsigned long size;

        DOMString type;
        HTMLOptionsCollection options;
        unsigned long length;
        HTMLOptionElement* item(unsigned long index);
        HTMLOptionElement* namedItem(DOMString name);
        void add(std::variant<HTMLOptionElement*, HTMLOptGroupElement*> element, std::variant<HTMLElement*, bool> before = nullptr);
        void remove();
        void remove(long index);

        void set(unsigned long index, HTMLOptionElement* option);

        HTMLCollection selectedOptions;
        long selectedIndex;
        DOMString value;

        bool willValidate;
        ValidityState validity;
        DOMString validationMessage;
        bool checkValidity();
        bool reportValidity();
        void setCustomValidity(DOMString error);

        void showPicker();

        NodeList labels;
};


class HTMLDataListElement: public HTMLElement{
    public:
        HTMLDataListElement(){};

        HTMLCollection options;
};


class HTMLOptGroupElement: public HTMLElement{
    public:
        HTMLOptGroupElement(){};

        bool disabled;
        DOMString label;
};


class HTMLTextAreaElement: public HTMLElement{
    public:
        HTMLTextAreaElement(){};

        DOMString autocomplete;
        unsigned long cols;
        DOMString dirname;
        bool disabled;
        HTMLFormElement* form;
        long maxLength;
        long minLength;
        DOMString name;
        DOMString placeholder;
        bool readOnly;
        bool required;
        unsigned long rows;
        DOMString wrap;
        DOMString type;
        DOMString defaultValue;
        DOMString value;
        unsigned long textLength;

        bool willValidate;
        ValidityState validity;
        DOMString validationMessage;
        bool checkValidity();
        bool reportValidity();
        void setCustomValidity(DOMString error);

        NodeList labels;

        void select();
        unsigned long selectionStart;
        unsigned long selectionEnd;
        DOMString selectionDirection;
        void setRangeText(DOMString replacement);
        void setRangeText(DOMString replacement, unsigned long start, unsigned long end, SelectionMode selectionMode = preserve);
        void setSelectionRange(unsigned long start, unsigned long end, DOMString direction);
};


class HTMLOutputElement: public HTMLElement{
    public:
        HTMLOutputElement(){};
        DOMTokenList htmlFor;
        HTMLFormElement* form;
        DOMString name;
        DOMString type;
        DOMString defaultValue;
        DOMString value;

        bool willValidate;
        ValidityState validity;
        DOMString validationMessage;
        bool checkValidity();
        bool reportValidity();
        void setCustomValidity(DOMString error);

        NodeList labels;
};

class HTMLProgressElement: public HTMLElement{
    public:
        HTMLProgressElement(){};
        double value;
        double max;
        double position;
        NodeList labels;
};

class HTMLMeterElement: public HTMLElement{
    public:
        HTMLMeterElement(){};

        double value;
        double min;
        double max;
        double low;
        double high;
        double optimum;
        NodeList labels;
};

class HTMLFieldSetElement: public HTMLElement{
    public:
        HTMLFieldSetElement(){};

        bool disabled;
        HTMLFormElement* form;
        DOMString name;
        DOMString type;
        HTMLCollection elements;

        bool willValidate;
        ValidityState validity;
        DOMString validationMessage;
        bool checkValidity();
        bool reportValidity();
        void setCustomValidity(DOMString error);
};

class HTMLLegendElement: public HTMLElement{
    public:
        HTMLLegendElement(){};
        HTMLFormElement* form;
};

class HTMLSelectedContentElement: public HTMLElement{
    public:
        HTMLSelectedContentElement(){};
};


class SubmitEvent: public Event{
    public:
        SubmitEvent(DOMString type, bool bubbles = false, bool cancelable = false, bool composed = false, HTMLElement* submitter = nullptr): Event(type, bubbles, cancelable, composed){};

        HTMLElement* submitter;
};


class FormDataEvent: public Event{
    public:
        FormDataEvent(DOMString type, bool bubbles = false, bool cancelable = false, bool composed = false): Event(type, bubbles, cancelable, composed){};
};

class HTMLDetailsElement: public HTMLElement{
    public:
        HTMLDetailsElement(){};

        DOMString name;
        bool open;
};


class HTMLDialogElement: public HTMLElement{
    public:
        HTMLDialogElement(){};

        bool open;
        DOMString returnValue;
        DOMString closedBy;
        void show();
        void showModal();
        void close(DOMString returnValue = "");
        void requestClose(DOMString returnValue);
};


HTMLElement* create_an_element(DOMString name, Document* doc, Node* parent, py::dict attributes, py::str content){
    if (name=="html"){
        HTMLHtmlElement* temp = new HTMLHtmlElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        // left: contenteditable, data, enterkeyhint, inputmode, style
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="meta"){
        HTMLMetaElement* temp = new HTMLMetaElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="name"){
                temp->name = attribute.second.cast<std::string>();
            }
            else if (nam=="httpEquiv"){
                temp->httpEquiv = attribute.second.cast<std::string>();
            }
            else if (nam=="content"){
                temp->content = attribute.second.cast<std::string>();
            }
            else if (nam=="media"){
                temp->media = attribute.second.cast<std::string>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="style"){
        HTMLStyleElement* temp = new HTMLStyleElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="disabled"){
                temp->disabled= attribute.second.cast<bool>();
            }
            else if (nam=="media"){
                temp->media = attribute.second.cast<std::string>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="div"){
        HTMLDivElement* temp = new HTMLDivElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="p"){
        HTMLParagraphElement* temp = new HTMLParagraphElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="a"){
        HTMLAnchorElement* temp = new HTMLAnchorElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="href"){
                temp->href = attribute.second.cast<std::string>();
            }
            else if (nam=="rel"){
                temp->rel = attribute.second.cast<std::string>();
            }
            else if (nam=="hreflang"){
                temp->hreflang = attribute.second.cast<std::string>();
            }
            else if (nam=="type"){
                temp->type = attribute.second.cast<std::string>();
            }
            else if (nam=="referrerPolicy"){
                temp->referrerPolicy = attribute.second.cast<std::string>();
            }
            else if (nam=="target"){
                temp->target = attribute.second.cast<std::string>();
            }
            else if (nam=="download"){
                temp->download = attribute.second.cast<std::string>();
            }
            else if (nam=="ping"){
                temp->ping = attribute.second.cast<std::string>();
            }
            else if (nam=="text"){
                temp->text = attribute.second.cast<std::string>();
            }
            else if (nam=="origin"){
                temp->origin = attribute.second.cast<std::string>();
            }
            else if (nam=="protocol"){
                temp->protocol = attribute.second.cast<std::string>();
            }
            else if (nam=="username"){
                temp->username = attribute.second.cast<std::string>();
            }
            else if (nam=="password"){
                temp->password = attribute.second.cast<std::string>();
            }
            else if (nam=="host"){
                temp->host = attribute.second.cast<std::string>();
            }
            else if (nam=="hostname"){
                temp->hostname = attribute.second.cast<std::string>();
            }
            else if (nam=="port"){
                temp->port = attribute.second.cast<std::string>();
            }
            else if (nam=="pathname"){
                temp->pathname = attribute.second.cast<std::string>();
            }
            else if (nam=="search"){
                temp->search = attribute.second.cast<std::string>();
            }
            else if (nam=="hash"){
                temp->hash = attribute.second.cast<std::string>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="br"){
        HTMLBRElement* temp = new HTMLBRElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="span"){
        HTMLSpanElement* temp = new HTMLSpanElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="time"){
        HTMLTimeElement* temp = new HTMLTimeElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="datetime"){
                temp->dateTime = attribute.second.cast<std::string>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="dl" || name=="dt" || name=="dd"){
        HTMLDListElement* temp = new HTMLDListElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="li"){
        HTMLLIElement* temp = new HTMLLIElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="value"){
                temp->value = attribute.second.cast<int>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="menu"){
        HTMLMenuElement* temp = new HTMLMenuElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="ol"){
        HTMLOListElement* temp = new HTMLOListElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="reversed"){
                temp->reversed = attribute.second.cast<bool>();
            }
            else if (nam=="start"){
                temp->start = attribute.second.cast<int>();
            }
            else if (nam=="type"){
                temp->type = attribute.second.cast<std::string>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="ul"){
        HTMLUListElement* temp = new HTMLUListElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="quote"){
        HTMLQuoteElement* temp = new HTMLQuoteElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="cite"){
                temp->cite = attribute.second.cast<std::string>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="pre"){
        HTMLPreElement* temp = new HTMLPreElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="hr"){
        HTMLHRElement* temp = new HTMLHRElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="h1" || name=="h2" || name=="h3" || name=="h4" || name=="h5" || name=="h6"){
        HTMLHeadingElement* temp = new HTMLHeadingElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="body"){
        HTMLBodyElement* temp = new HTMLBodyElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="link"){
        HTMLLinkElement* temp = new HTMLLinkElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="href"){
                temp->href = attribute.second.cast<std::string>();
            }
            else if (nam=="crossOrigin"){
                temp->crossOrigin = attribute.second.cast<std::string>();
            }
            else if (nam=="rel"){
                temp->rel = attribute.second.cast<std::string>();
            }
            else if (nam=="as"){
                temp->as = attribute.second.cast<std::string>();
            }
            else if (nam=="media"){
                temp->media = attribute.second.cast<std::string>();
            }
            else if (nam=="integrity"){
                temp->integrity = attribute.second.cast<std::string>();
            }
            else if (nam=="hreflang"){
                temp->hreflang = attribute.second.cast<std::string>();
            }
            else if (nam=="type"){
                temp->type = attribute.second.cast<std::string>();
            }
            else if (nam=="imageSrcset"){
                temp->imageSrcset = attribute.second.cast<std::string>();
            }
            else if (nam=="imageSizes"){
                temp->imageSizes = attribute.second.cast<std::string>();
            }
            else if (nam=="referrerPolicy"){
                temp->referrerPolicy = attribute.second.cast<std::string>();
            }
            else if (nam=="disabled"){
                temp->disabled = attribute.second.cast<bool>();
            }
            else if (nam=="fetchPriority"){
                temp->fetchPriority= attribute.second.cast<std::string>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="base"){
        HTMLBaseElement* temp = new HTMLBaseElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="href"){
                temp->href = attribute.second.cast<std::string>();
            }
            else if (nam=="target"){
                temp->target = attribute.second.cast<std::string>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="title"){
        HTMLTitleElement* temp = new HTMLTitleElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        temp->text = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="head"){
        HTMLHeadElement* temp = new HTMLHeadElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="picture"){
        HTMLPictureElement* temp = new HTMLPictureElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="source"){
        HTMLSourceElement* temp = new HTMLSourceElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="src"){
                temp->src = attribute.second.cast<std::string>();
            }
            else if (nam=="type"){
                temp->type = attribute.second.cast<std::string>();
            }
            else if (nam=="srcset"){
                temp->srcset = attribute.second.cast<std::string>();
            }
            else if (nam=="sizes"){
                temp->sizes = attribute.second.cast<std::string>();
            }
            else if (nam=="media"){
                temp->media = attribute.second.cast<std::string>();
            }
            else if (nam=="width"){
                temp->width = attribute.second.cast<int>();
            }
            else if (nam=="height"){
                temp->height = attribute.second.cast<int>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="image"){
        HTMLImageElement* temp = new HTMLImageElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="alt"){
                temp->alt = attribute.second.cast<std::string>();
            }
            else if (nam=="src"){
                temp->src = attribute.second.cast<std::string>();
            }
            else if (nam=="srcset"){
                temp->srcset = attribute.second.cast<std::string>();
            }
            else if (nam=="crossorigin"){
                temp->crossOrigin = attribute.second.cast<std::string>();
            }
            else if (nam=="usemap"){
                temp->useMap = attribute.second.cast<std::string>();
            }
            else if (nam=="width"){
                temp->width = attribute.second.cast<int>();
            }
            else if (nam=="height"){
                temp->height = attribute.second.cast<int>();
            }
            else if (nam=="naturalwidth"){
                temp->naturalWidth = attribute.second.cast<int>();
            }
            else if (nam=="naturalheight"){
                temp->naturalHeight = attribute.second.cast<int>();
            }
            else if (nam=="currentsrc"){
                temp->currentSrc = attribute.second.cast<std::string>();
            }
            else if (nam=="referrerpolicy"){
                temp->referrerPolicy = attribute.second.cast<std::string>();
            }
            else if (nam=="decoding"){
                temp->decoding = attribute.second.cast<std::string>();
            }
            else if (nam=="loading"){
                temp->loading = attribute.second.cast<std::string>();
            }
            else if (nam=="fetchpriority"){
                temp->fetchPriority = attribute.second.cast<std::string>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="iframe"){
        HTMLIFrameElement* temp = new HTMLIFrameElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="src"){
                temp->src = attribute.second.cast<std::string>();
            }
            else if (nam=="srcdoc"){
                temp->srcdoc = attribute.second.cast<std::string>();
            }
            else if (nam=="name"){
                temp->name = attribute.second.cast<std::string>();
            }
            else if (nam=="allow"){
                temp->allow = attribute.second.cast<std::string>();
            }
            else if (nam=="allowFullscreen"){
                temp->allowFullscreen = attribute.second.cast<bool>();
            }
            else if (nam=="width"){
                temp->width = attribute.second.cast<std::string>();
            }
            else if (nam=="height"){
                temp->height = attribute.second.cast<std::string>();
            }
            else if (nam=="referrerpolicy"){
                temp->referrerPolicy = attribute.second.cast<std::string>();
            }
            else if (nam=="loading"){
                temp->loading = attribute.second.cast<std::string>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="embed"){
        HTMLEmbedElement* temp = new HTMLEmbedElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="src"){
                temp->src = attribute.second.cast<std::string>();
            }
            else if (nam=="type"){
                temp->type = attribute.second.cast<std::string>();
            }
            else if (nam=="width"){
                temp->width = attribute.second.cast<std::string>();
            }
            else if (nam=="height"){
                temp->height = attribute.second.cast<std::string>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="object"){
        HTMLObjectElement* temp = new HTMLObjectElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="data"){
                temp->data = attribute.second.cast<std::string>();
            }
            else if (nam=="type"){
                temp->type = attribute.second.cast<std::string>();
            }
            else if (nam=="name"){
                temp->name = attribute.second.cast<std::string>();
            }
            else if (nam=="width"){
                temp->width = attribute.second.cast<std::string>();
            }
            else if (nam=="height"){
                temp->height = attribute.second.cast<std::string>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="media"){
        HTMLMediaElement* temp = new HTMLMediaElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="src"){
                temp->src = attribute.second.cast<std::string>();
            }
            else if (nam=="currentsrc"){
                temp->currentSrc = attribute.second.cast<std::string>();
            }
            else if (nam=="crossorigin"){
                temp->crossOrigin = attribute.second.cast<std::string>();
            }
            else if (nam=="preload"){
                temp->preload = attribute.second.cast<std::string>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="audio"){
        HTMLAudioElement* temp = new HTMLAudioElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="video"){
        HTMLVideoElement* temp = new HTMLVideoElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="width"){
                temp->width = attribute.second.cast<int>();
            }
            else if (nam=="height"){
                temp->height = attribute.second.cast<int>();
            }
            else if (nam=="src"){
                temp->src = attribute.second.cast<std::string>();
            }
            else if (nam=="currentsrc"){
                temp->currentSrc = attribute.second.cast<std::string>();
            }
            else if (nam=="crossorigin"){
                temp->crossOrigin = attribute.second.cast<std::string>();
            }
            else if (nam=="preload"){
                temp->preload = attribute.second.cast<std::string>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="track"){
        HTMLTrackElement* temp = new HTMLTrackElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="kind"){
                temp->kind = attribute.second.cast<std::string>();
            }
            else if (nam=="src"){
                temp->src = attribute.second.cast<std::string>();
            }
            else if (nam=="srclang"){
                temp->srclang = attribute.second.cast<std::string>();
            }
            else if (nam=="label"){
                temp->label = attribute.second.cast<std::string>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="map"){
        HTMLMapElement* temp = new HTMLMapElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="name"){
                temp->name = attribute.second.cast<std::string>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="area"){
        HTMLAreaElement* temp = new HTMLAreaElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="alt"){
                temp->alt = attribute.second.cast<std::string>();
            }
            else if (nam=="coords"){
                temp->coords = attribute.second.cast<std::string>();
            }
            else if (nam=="shape"){
                temp->shape = attribute.second.cast<std::string>();
            }
            else if (nam=="target"){
                temp->target = attribute.second.cast<std::string>();
            }
            else if (nam=="download"){
                temp->download = attribute.second.cast<std::string>();
            }
            else if (nam=="ping"){
                temp->ping = attribute.second.cast<std::string>();
            }
            else if (nam=="rel"){
                temp->rel = attribute.second.cast<std::string>();
            }
            else if (nam=="referrerpolicy"){
                temp->referrerPolicy = attribute.second.cast<std::string>();
            }
            else if (nam=="href"){
                temp->href = attribute.second.cast<std::string>();
            }
            else if (nam=="origin"){
                temp->origin = attribute.second.cast<std::string>();
            }
            else if (nam=="protocol"){
                temp->protocol = attribute.second.cast<std::string>();
            }
            else if (nam=="username"){
                temp->username = attribute.second.cast<std::string>();
            }
            else if (nam=="password"){
                temp->password = attribute.second.cast<std::string>();
            }
            else if (nam=="host"){
                temp->host = attribute.second.cast<std::string>();
            }
            else if (nam=="hostname"){
                temp->hostname = attribute.second.cast<std::string>();
            }
            else if (nam=="port"){
                temp->port = attribute.second.cast<std::string>();
            }
            else if (nam=="pathname"){
                temp->pathname = attribute.second.cast<std::string>();
            }
            else if (nam=="search"){
                temp->search = attribute.second.cast<std::string>();
            }
            else if (nam=="hash"){
                temp->hash = attribute.second.cast<std::string>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="table"){
        HTMLTableElement* temp = new HTMLTableElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="caption"){
        HTMLTableCaptionElement* temp = new HTMLTableCaptionElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="td" || name=="th"){
        HTMLTableCellElement* temp = new HTMLTableCellElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="colspan"){
                temp->colSpan = attribute.second.cast<int>();
            }
            else if (nam=="rowspan"){
                temp->rowSpan = attribute.second.cast<int>();
            }
            else if (nam=="headers"){
                temp->headers = attribute.second.cast<std::string>();
            }
            else if (nam=="cellindex"){
                temp->cellIndex = attribute.second.cast<int>();
            }
            else if (nam=="scope"){
                temp->scope = attribute.second.cast<std::string>();
            }
            else if (nam=="abbr"){
                temp->abbr = attribute.second.cast<std::string>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="tr"){
        HTMLTableRowElement* temp = new HTMLTableRowElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="rowindex"){
                temp->rowIndex = attribute.second.cast<int>();
            }
            else if (nam=="sectionrowindex"){
                temp->sectionRowIndex = attribute.second.cast<int>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="col" || name=="colgroup"){
        HTMLTableColElement* temp = new HTMLTableColElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="span"){
                temp->span = attribute.second.cast<int>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="section"){
        HTMLTableSectionElement* temp = new HTMLTableSectionElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="form"){
        HTMLFormElement* temp = new HTMLFormElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="label"){
        HTMLLabelElement* temp = new HTMLLabelElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="for"){
                temp->htmlFor = attribute.second.cast<std::string>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="input"){
        HTMLInputElement* temp = new HTMLInputElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="accept"){
                temp->accept = attribute.second.cast<std::string>();
            }
            else if (nam=="alpha"){
                temp->alpha = attribute.second.cast<bool>();
            }
            else if (nam=="alt"){
                temp->alt = attribute.second.cast<std::string>();
            }
            else if (nam=="autocomplete"){
                temp->autocomplete = attribute.second.cast<std::string>();
            }
            else if (nam=="defaultchecked"){
                temp->defaultChecked= attribute.second.cast<bool>();
            }
            else if (nam=="checked"){
                temp->checked = attribute.second.cast<bool>();
            }
            else if (nam=="colorspace"){
                temp->colorSpace = attribute.second.cast<std::string>();
            }
            else if (nam=="dirname"){
                temp->dirname = attribute.second.cast<std::string>();
            }
            else if (nam=="disabled"){
                temp->disabled = attribute.second.cast<bool>();
            }
            else if (nam=="max"){
                temp->max = attribute.second.cast<std::string>();
            }
            else if (nam=="maxlength"){
                temp->maxLength = attribute.second.cast<int>();
            }
            else if (nam=="min"){
                temp->min = attribute.second.cast<std::string>();
            }
            else if (nam=="minlength"){
                temp->minLength = attribute.second.cast<int>();
            }
            else if (nam=="multiple"){
                temp->multiple = attribute.second.cast<bool>();
            }
            else if (nam=="name"){
                temp->name = attribute.second.cast<std::string>();
            }
            else if (nam=="pattern"){
                temp->pattern = attribute.second.cast<std::string>();
            }
            else if (nam=="placeholder"){
                temp->placeholder = attribute.second.cast<std::string>();
            }
            else if (nam=="readonly"){
                temp->readOnly = attribute.second.cast<bool>();
            }
            else if (nam=="required"){
                temp->required = attribute.second.cast<bool>();
            }
            else if (nam=="size"){
                temp->size = attribute.second.cast<int>();
            }
            else if (nam=="src"){
                temp->src = attribute.second.cast<std::string>();
            }
            else if (nam=="step"){
                temp->step = attribute.second.cast<std::string>();
            }
            else if (nam=="type"){
                temp->type = attribute.second.cast<std::string>();
            }
            else if (nam=="defaultvalue"){
                temp->defaultValue = attribute.second.cast<std::string>();
            }
            else if (nam=="value"){
                temp->value = attribute.second.cast<std::string>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="button"){
        HTMLButtonElement* temp = new HTMLButtonElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="disabled"){
                temp->disabled = attribute.second.cast<bool>();
            }
            else if (nam=="name"){
                temp->name = attribute.second.cast<std::string>();
            }
            else if (nam=="type"){
                temp->type = attribute.second.cast<std::string>();
            }
            else if (nam=="value"){
                temp->value = attribute.second.cast<std::string>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="option"){
        HTMLOptionElement* temp = new HTMLOptionElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="disabled"){
                temp->disabled = attribute.second.cast<bool>();
            }
            else if (nam=="label"){
                temp->label = attribute.second.cast<std::string>();
            }
            else if (nam=="defaultselected"){
                temp->defaultSelected = attribute.second.cast<bool>();
            }
            else if (nam=="selected"){
                temp->selected = attribute.second.cast<bool>();
            }
            else if (nam=="value"){
                temp->value = attribute.second.cast<std::string>();
            }
            else if (nam=="text"){
                temp->text = attribute.second.cast<std::string>();
            }
            else if (nam=="index"){
                temp->index = attribute.second.cast<int>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="select"){
        HTMLSelectElement* temp = new HTMLSelectElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="autocomplete"){
                temp->autocomplete = attribute.second.cast<std::string>();
            }
            else if (nam=="disabled"){
                temp->disabled = attribute.second.cast<bool>();
            }
            else if (nam=="multiple"){
                temp->multiple = attribute.second.cast<bool>();
            }
            else if (nam=="name"){
                temp->name = attribute.second.cast<std::string>();
            }
            else if (nam=="required"){
                temp->required = attribute.second.cast<bool>();
            }
            else if (nam=="size"){
                temp->size = attribute.second.cast<int>();
            }
            else if (nam=="type"){
                temp->type = attribute.second.cast<std::string>();
            }
            else if (nam=="value"){
                temp->value = attribute.second.cast<std::string>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="datalist"){
        HTMLDataListElement* temp = new HTMLDataListElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="optgroup"){
        HTMLOptGroupElement* temp = new HTMLOptGroupElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="progress"){
        HTMLProgressElement* temp = new HTMLProgressElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="value"){
                temp->value = attribute.second.cast<int>();
            }
            else if (nam=="max"){
                temp->max = attribute.second.cast<int>();
            }
            else if (nam=="position"){
                temp->position = attribute.second.cast<int>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="meter"){
        HTMLMeterElement* temp = new HTMLMeterElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="value"){
                temp->value = attribute.second.cast<int>();
            }
            else if (nam=="min"){
                temp->min = attribute.second.cast<int>();
            }
            else if (nam=="max"){
                temp->max = attribute.second.cast<int>();
            }
            else if (nam=="low"){
                temp->low = attribute.second.cast<int>();
            }
            else if (nam=="high"){
                temp->high = attribute.second.cast<int>();
            }
            else if (nam=="optimum"){
                temp->optimum = attribute.second.cast<int>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="fieldset"){
        HTMLFieldSetElement* temp = new HTMLFieldSetElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="disabled"){
                temp->disabled = attribute.second.cast<bool>();
            }
            else if (nam=="name"){
                temp->name = attribute.second.cast<std::string>();
            }
            else if (nam=="type"){
                temp->type = attribute.second.cast<std::string>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="legend"){
        HTMLLegendElement* temp = new HTMLLegendElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="selectedcontent"){
        HTMLSelectedContentElement* temp = new HTMLSelectedContentElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="details"){
        HTMLDetailsElement* temp = new HTMLDetailsElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="name"){
                temp->name = attribute.second.cast<std::string>();
            }
            else if (nam=="open"){
                temp->open = attribute.second.cast<bool>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="dialog"){
        HTMLDialogElement* temp = new HTMLDialogElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="open"){
                temp->open = attribute.second.cast<bool>();
            }
            else if (nam=="returnvalue"){
                temp->returnValue = attribute.second.cast<std::string>();
            }
            else if (nam=="closedby"){
                temp->closedBy = attribute.second.cast<std::string>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    else if (name=="textarea"){
        HTMLTextAreaElement* temp = new HTMLTextAreaElement();
        temp->ownerDocument = doc;
        temp->parentNode = parent;
        temp->innerText = content;
        if (dynamic_cast<Element*>(parent)){
            temp->parentElement = dynamic_cast<Element*>(parent);
        }
        for (auto attribute: attributes){
            std::string nam = attribute.first.cast<std::string>();
            if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="lang"){
                temp->lang = attribute.second.cast<std::string>();
            }
            else if (nam=="accesskey"){
                temp->accessKey = attribute.second.cast<std::string>();
            }
            else if (nam=="dir"){
                temp->dir = attribute.second.cast<std::string>();
            }
            else if (nam=="draggable"){
                temp->draggable = attribute.second.cast<bool>();
            }
            else if (nam=="hidden"){
                if (py::isinstance<py::bool_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<bool>();
                }
                else if (py::isinstance<py::float_>(attribute.second)) {
                    temp->hidden = attribute.second.cast<double>();
                }
                else if (py::isinstance<py::str>(attribute.second)) {
                    temp->hidden = attribute.second.cast<std::string>();
                }
            }
            else if (nam=="id"){
                temp->id = attribute.second.cast<std::string>();
            }
            else if (nam=="class"){
                temp->classname = attribute.second.cast<std::string>();
            }
            else if (nam=="inert"){
                temp->inert = attribute.second.cast<bool>();
            }
            else if (nam=="popover"){
                temp->popover = attribute.second.cast<std::string>();
            }
            else if (nam=="spellcheck"){
                temp->spellcheck = attribute.second.cast<bool>();
            }
            else if (nam=="tabindex"){
                temp->tabIndex = attribute.second.cast<int>();
            }
            else if (nam=="title"){
                temp->title = attribute.second.cast<std::string>();
            }
            else if (nam=="translate"){
                temp->translate = attribute.second.cast<bool>();
            }
            else if (nam=="writingsuggestions"){
                temp->writingSuggestions = attribute.second.cast<std::string>();
            }
            else if (nam=="autocapitalize"){
                temp->autocapitalize = attribute.second.cast<std::string>();
            }
            else if (nam=="autocorrect"){
                temp->autocorrect = attribute.second.cast<bool>();
            }
            else if (nam=="autofocus"){
                temp->autofocus = attribute.second.cast<bool>();
            }
            else if (nam=="autocomplete"){
                temp->autocomplete = attribute.second.cast<std::string>();
            }
            else if (nam=="cols"){
                temp->cols = attribute.second.cast<int>();
            }
            else if (nam=="disabled"){
                temp->disabled = attribute.second.cast<bool>();
            }
            else if (nam=="maxlength"){
                temp->maxLength = attribute.second.cast<int>();
            }
            else if (nam=="minlength"){
                temp->minLength = attribute.second.cast<int>();
            }
            else if (nam=="name"){
                temp->name = attribute.second.cast<std::string>();
            }
            else if (nam=="placeholder"){
                temp->placeholder = attribute.second.cast<std::string>();
            }
            else if (nam=="readonly"){
                temp->readOnly = attribute.second.cast<bool>();
            }
            else if (nam=="rows"){
                temp->rows = attribute.second.cast<int>();
            }
            else if (nam=="wrap"){
                temp->wrap = attribute.second.cast<std::string>();
            }
            else if (nam=="type"){
                temp->type = attribute.second.cast<std::string>();
            }
            else if (nam=="defaultvalue"){
                temp->defaultValue = attribute.second.cast<std::string>();
            }
            else if (nam=="value"){
                temp->value = attribute.second.cast<std::string>();
            }
            else if (nam=="textlength"){
                temp->textLength = attribute.second.cast<int>();
            }
            else{
                Attr* attri = new Attr(attribute.first.cast<DOMString>());
                attri->name = attribute.first.cast<std::string>();
                attri->value = attribute.second.cast<std::string>();
                attri->ownerElement = dynamic_cast<Element*>(temp);
                attri->ownerDocument = doc;
            }
        }
        return dynamic_cast<HTMLElement*>(temp);
    }
    return nullptr;
}


std::vector<HTMLElement*> els = {};
std::string logs = "";

std::string getlogs(){
    return logs;
}

void delete_all(){
    for (auto a: els){
        try{
            delete a;
        }
        catch(...){}
    }
    logs = "";
}

bool process_html(const py::dict &input_dict, Document* doc=nullptr, Node* parent=nullptr){
    std::string name = "";
    py::dict attributes;
    py::list children;
    std::string content = "";
    Node* parentji = parent;
    HTMLElement* temp;
    Document* docji = doc;
    if (!docji){
        docji = new Document();
    }
    if (parent==nullptr){
        parentji = dynamic_cast<Node*>(doc);
    }
    else{
        parentji = dynamic_cast<Node*>(parent);
    }
    for (auto item: input_dict){
        std::string key = item.first.cast<std::string>();
        if (key=="name"){
            name = item.second.cast<std::string>();
        }
        else if (key=="attrs"){
            attributes = py::cast<py::dict>(item.second);
        }
        else if (key=="content"){
            content = item.second.cast<std::string>();
        }
        else if (key=="children"){
            children = py::cast<py::list>(item.second);
            try{
                temp = create_an_element(name, docji,  dynamic_cast<Node*>(parentji), attributes, content);
            }
            catch(...){
                logs+="There's an error in creating key " + name + "\n";
                std::cout<<"There's an error in creating key "<<name;
            }
            if (temp){
                logs+="Successfully generated: " + name + "\n";
                std::cout<<"Successfully generated: "<<name<<std::endl;
                temp->parentNode = parent;
                els.push_back(temp);
                Element* temp2 = dynamic_cast<Element*>(parentji);
                if (temp2){
                    temp->parentElement = temp2;
                }
                parentji = dynamic_cast<Node*>(temp);
                for (auto child: children){
                    process_html(py::cast<py::dict>(child), doc, parentji);
                }
            }
        }
    }
    return true;
}

PYBIND11_MODULE(Webelo, m){
    m.doc() = "C++ DOM Library";
    py::class_<Document>(m, "Document");
    py::class_<Node>(m, "Node");
    m.def("process_html", &process_html,"Processes the HTML custom dictionary & creates element objects/attributes/text tooooo",
          py::arg("input_dict"),
          py::arg("doc") = nullptr,
          py::arg("parent") = nullptr);
    m.def("delete_all",&delete_all, "Deletes all previously created instances !");
    m.def("getlogs",&getlogs, "Fetch all logs !!");
};