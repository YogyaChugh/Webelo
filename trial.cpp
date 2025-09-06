#include <ctime>
#include <iostream>
#include <windows.h>


int main(){
    time_t a = time(NULL);
    std::cout<< ctime(&a);
    Sleep(4000);
    std::cout<< ctime(&a);
    std::cout<<a;
}