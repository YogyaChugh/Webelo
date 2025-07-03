#include <iostream>
#include <memory>

class A{
    public:
        int num;
};

class B: public A{
    public:
        int num2;
};

void go(std::unique_ptr<A> goko){
    goko->num = 7;
    std::cout<<"A gya tu launde !\n"<<goko->num;
}

int main(){
    go(std::make_unique<B>());
}