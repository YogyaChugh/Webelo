#include<iostream>

int* ok(){
    int* a = new int[100];
    a[0] = 100;
    return a;
}

int main(){
    int* a = ok();
    std::cout << a[0] <<std::flush;
}