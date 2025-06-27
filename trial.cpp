#include <iostream>
#include <string>
#include <vector>

class Animal
{
public:
    virtual std::string name() { return ""; }
};

class Person: public Animal
{
	std::string name_m = "Michael Scott";
public:
    virtual std::string name() { return name_m; }
};

class Bird: public Animal {};

int main() 
{
	auto animal = new Animal;
	auto person = new Person;
	auto bird = new Bird;

	std::vector<Animal*> creatures {animal, person, bird};
	for (auto c: creatures)
	{
		try{
			c->name_m = "gg";
		}
		catch(...){
			std::cout<<"maggi";
		}
		std::cout << c << ' ' << c->name() << '\n';
	}
    
    for (auto c: creatures) delete c;
}