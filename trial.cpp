#include <iostream>
#include <vector>
#include <variant>
#include <string>

class A{};

class B: public A{};

int main(){
    A* temp = new B();
    if (typeid(*temp) == typeid(B)){
        std::cout<<"hi1";
    }
    if (typeid(*temp) == typeid(A)){
        std::cout<<"hi2";
    }
}