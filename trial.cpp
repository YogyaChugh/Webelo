#include<iostream>
#include<vector>
#include<set>

using namespace std;
int main()
{  
	set<int> a = {1,2,3};
	auto b = a.find(2);
	b = 5;
	for (auto c: a){
		cout<<c;
	}
}