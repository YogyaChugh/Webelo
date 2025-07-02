#include <iostream>

bool go(){
    return (bool)(5==5 && 6==3);
}

int main(){
    std::cout<<go();
}