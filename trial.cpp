#include<iostream>    
#include<vector> 
using namespace std;
int main()
{  
	vector<int> vec {1,2,3,4,5};
	
	cout<<"Intially vector: ";
	for(auto i=vec.begin(); i<vec.end(); i++)
	{
		cout<<" "<<*i;
	}
	
	vec.insert(vec.begin(),10);//Inserting 10 to the vector
	
	cout<<"\n\nThe modified vector is: ";
	for(auto i=vec.begin(); i<vec.end(); i++)
	{
		cout<<" "<<*i;
	}
	return 0;
}