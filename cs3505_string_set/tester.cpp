#include <iostream> 
#include <time.h> 
#include "string_set.h"

using namespace cs3505;

int main()
{
	// Set random seed
	srand(time(NULL));

	std::cout << "Test adding to set and indirectly test get_elements" << std::endl;
	string_set set = string_set(5);
	set.add("apple");
	set.add("apple");
	set.add("zebra");
	set.add("horse");
	set.add("apple");
	std::cout << "expected: apple, horse, zebra, " << std::endl;
	std::cout << "actual: ";
	std::vector<std::string> values = set.get_elements();
	 for (int i = 0; i < values.size(); i++)
	{
		std::cout << values.at(i) << ", ";
	}
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Test contains" << std::endl;
	std::cout << "expected: 1, 1, 1, 0" << std::endl;
	std::cout << "actual: ";
	std::cout << set.contains("apple") << ", ";
	std::cout << set.contains("horse") << ", ";;
	std::cout << set.contains("zebra") << ", ";;
	std::cout << set.contains("unicorn");
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Test remove" << std::endl;
	set.remove("zebra");
	set.remove("zebra");
	set.remove("unicorn");
	set.remove("apple");
	std::cout << "expected: horse, " << std::endl;
	std::cout << "actual: ";
	values = set.get_elements();
	for (int i = 0; i < values.size(); i++)
	{
		std::cout << values.at(i) << ", " ;
	}
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Test equals" << std::endl;
	string_set set2 = set;
	std::cout << "expected: horse, " << std::endl;
	std::cout << "actual: ";
 	values = set2.get_elements();
	for (int i = 0; i < values.size(); i++)
	{
		std::cout << values.at(i) << ", " ;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Test copy constructor" << std::endl;
	string_set set3 = string_set(set);
	std::cout << "expected: horse, " << std::endl;
	std::cout << "actual: ";
 	values = set2.get_elements();
	for (int i = 0; i < values.size(); i++)
	{
		std::cout << values.at(i) << ", " ;
	}
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Test size" << std::endl;
	std::cout << "expected: 1, 1, 1" << std::endl;
	std::cout << "actual: " << set.get_size() << ", " << set2.get_size() << ", " << set3.get_size() << std::endl;
	std::cout << std::endl;


	std::cout << "Test add and remove" << std::endl;

	set.remove("horse");
	set.add("fish");
	set.add("whale");
	set.add("walrus");
	set.add("bull");
	set.remove("whale");
	set.add("apple");
	set.remove("zebra");
	set.remove("unicorn");

	std::cout << "expected: apple, bull, fish, walrus, 4" << std::endl;
	std::cout << "actual: ";
	values = set.get_elements();
	for (int i = 0; i < values.size(); i++)
	{
		std::cout << values.at(i) << ", " ;
	}
	std::cout << set.get_size();
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	return 0;
}
