#include<iostream>
#include<vector>
#include<set>
#include "src/base.cpp"

using namespace std;


int main(){
	vector<int> temp = {97};
	for (auto a: split_text_multiple("maggi is love",temp)){
		cout<< a <<endl;
	}
}