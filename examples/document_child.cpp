#include "../src/Webelo.cpp"
#include <iostream>


int main(){
    // Creating document
    Document* doc = new Document();

    //Creating and appending child
    Element* html = new Element("http://www.w3.org/1999/xhtml","","html",nullptr, UNDEFINED, doc, doc);
    doc->appendChild(html);

    std::cout<<"Child Nodes:\n\t";
    for (auto a: doc->childNodes.node_list){
        std::cout<<*a<<std::endl<<"\t"; //Checking paji
    }
}