#include <iostream>

class B;

class A{
	public:
	void virtual g() = 0;
	void go();
};
class B: public A{
	public:
	void g(){
		std::cout<<"pasta";
	}
	void nogo(){
		std::cout<<typeid(this).name();
	}
};
void A::go(){
	std::cout<<typeid(this).name();
	if (dynamic_cast<B*>(this)){
		std::cout<<"\ny";
	}
	else{
		std::cout<<'n';
	}
}

int main(){

	B b;
	b.go();
}