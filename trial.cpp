#include <iostream>
#include <memory>
#include <functional>

void go(bool goko){
    std::cout<<"A gya tu launde !\n"<<goko;
}

int main(){
    std::function<void()> printer;
    printer = std::bind(go,true);
    printer();
}