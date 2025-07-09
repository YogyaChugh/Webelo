#include <iostream>
#include <vector>
#include <typeinfo>
#include <string>


int main() {
    std::vector<std::string> element = {"goa","maggi"};
    try {
        std::cout<<element.back()<<"\n";
        std::cout<<typeid(element.back()).name();
    }
    catch (std::out_of_range) {
        std::cout<<"out of range";
    }
}