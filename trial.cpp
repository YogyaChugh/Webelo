#include <iostream>
#include <string>
#include <optional>


int main() {
    std::optional<int> a = 7;
    a = 10;
    a = std::nullopt;
    if (a!=std::nullopt && a.value()==2){std::cout<<"ji";}
}