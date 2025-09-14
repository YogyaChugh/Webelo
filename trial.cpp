#include <iostream>
#include <vector>
#include <variant>
#include <string>

class A{
    public:
        int fingo = 102;
        A(int fingp){
            this->fingo = fingp;
        }
};

class B: public A{
    public:
        B(int gg): A(gg){};
};

int main(){
    std::vector<std::variant<A*, std::string>> a = {"maggi","pasta",new B(5)};
    for (auto b: a){
        if (std::holds_alternative<A*>(b)){
            std::cout<<std::get<A*>(b)->fingo<<std::endl;
        }
        else{
            std::cout<<std::get<std::string>(b)<<std::endl;
        }
    }
}