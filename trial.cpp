#include <iostream>
#include <vector>
#include <variant>
#include <string>
#include <optional>


int main(){
    std::optional<int> a = 10;
    std::optional<int> b = std::nullopt;
    if (a==10){
        std::cout<<"hi";
    }
    else{
        std::cout<<"hello";
    }
    std::cout<< b.has_value();
}