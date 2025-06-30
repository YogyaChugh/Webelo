#include "../base.hpp"
#include "../nodes/node.hpp"
#include "../nodes/document.hpp"

const unsigned short START_TO_START = 0;
const unsigned short START_TO_END = 1;
const unsigned short END_TO_END = 2;
const unsigned short END_TO_START = 3;

//Exposed to window only
class AbstractRange{
    private:
        Node startContainer;
        unsigned long startOffset;
        Node endContainer;
        unsigned long endOffset;
        bool collapsed;
}

struct StaticRangeInit{
    Node startContainer;
    unsigned long startOffset;
    Node endContainer;
    unsigned long endOffset;
    StaticRangeInit(Node sc, unsigned long sos, Node ec, unsigned long eos){
        startContainer = sc;
        startOffset = sos;
        endContainer = ec;
        endOffset = eos;
    }
}

//Exposed to window only
class StaticRange: AbstractRange{
    public:
        StaticRange(StaticRangeInit init);
}


class Range: AbstractRange{
    private:
        Node commonAncestorContainer;
    public:
        Range();

        void setStart(Node node, unsigned long offset);
        void setEnd(Node node, unsigned long offset);
        void setStartBefore(Node node);
        void setStartAfter(Node node);
        void setEndBefore(Node node);
        void setEndAfter(Node node);
        void collapse(bool toStart = false);
        void selectNode(Node node);
        void selectNodeContents(Node node);

        short compareBoundaryPoints(unsigned short how, Range sourceRange);

        //CEReactions
        void deleteContents();
        DocumentFragment extraContents(); //NewObject
        DocumentFragment cloneContents(); //NewObject
        void insertNode(Node node);
        void surroundContents(Node newParent);

        Range cloneRange(); //NewObject
        void detach();
        bool isPointInRange(Node node, unsigned long offset);
        short comparePoint(Node node, unsigned long offset);
        bool intersectsNode(Node node);

        //TODO: stringifier;
}