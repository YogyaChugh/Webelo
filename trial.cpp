#include <any>
#include <iostream>

int main(){
    std::any a = nullptr;
    std::cout<< a.has_value();
    std::cout<< std::any_cast<std::nullptr_t>(a);
}