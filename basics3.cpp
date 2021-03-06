/*
Exercises
Coding:
3.Create two functions, one that takes a string* and one that takes a string&. Each of these functions should modify the outside string object in its own unique way. In main(), create and initialize a string object, print it, then pass it to each of the two functions, printing the results.
*/

#include <string>
#include <algorithm>
#include <iostream>

void reverse(std::string &string){
	std::reverse(string.begin(), string.end());
}

void reverse2(std::string *string){
	std::reverse(string->begin(), string->end());
}

int main(int argc, char const *argv[])
{
	std::string string ("3.Create two functions, one that takes a string* and one that takes a string&. Each of these functions should modify the outside string object in its own unique way. In main(), create and initialize a string object, print it, then pass it to each of the two functions, printing the results.");
	reverse(string);
	std::cout << "\nreverse function 1,take reference.\n\n" << std::endl;
	std::cout << string << std::endl;
	
	reverse2(&string);
	std::cout << "\nreverse function 2,take pointer.\n\n" << std::endl;
	std::cout << string << std::endl;
	return 0;
}