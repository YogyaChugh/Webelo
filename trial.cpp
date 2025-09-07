#include <optional>
#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

bool sum(std::vector<int> a){
    std::accumulate(
        a.begin(), a.end(), [](int c){
            std::cout<<c;
            if (c==4){
                return false;
            }
            return true;
        }
    );
    return false;
}

int main(){
    std::vector c = {1,2,3,4,5,6};
    std::cout<<sum(c);
}