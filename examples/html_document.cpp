#include "../src/Webelo.cpp"
#include <iostream>

// Just to print
void print_kiddos(Node* temp, int level = 0){
    for (int b=0;b<level;b++){
        std::cout<<"\t";
    }
    std::cout<<temp->nodeName<<" {"<<temp->nodeType<<"}"<<std::endl;
    level++;
    for (auto a: temp->childNodes.node_list){
        print_kiddos(a,level);
    }
}

int main(){
    // Creates a basic HTML Document

    DOMImplementation* docs = new DOMImplementation();
    // HEHE, Savage
    Document* temp = docs->createHTMLDocument("My Savage Library");
    std::cout<<temp->type<<std::endl;
    std::cout<<temp->contentType<<std::endl;
    print_kiddos(temp);
}