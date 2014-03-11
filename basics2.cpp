/*
Exercises
Coding:
2.Create a vector<float> and put 25 numbers into it. Then square each number and put the result back into the same location in the vector. Display the vector before and after the multiplications. 
3.Create two functions, one that takes a string* and one that takes a string&. Each of these functions should modify the outside string object in its own unique way. In main(), create and initialize a string object, print it, then pass it to each of the two functions, printing the results.
4.Create a struct that holds two string objects and one int. Use a typedef for the struct name. 5.Create an instance of the struct, initialize all three values in your instance, and print them out. Take the address of your instance and assign it to a pointer to your struct type. Change the three values in your instance and print them out, all using the pointer.
*/

#include <iostream>
#include <vector>
#include <algorithm>    // std::for_each

void square(float &num){
	num *= num;
}

void display(const std::vector<float> &vect){
	for(std::vector<float>::const_iterator item = vect.begin(); item != vect.end(); ++item)
		std::cout << *item << ' ';
	std::cout << '\n' << std::endl;
}

int main(int argc, char const *argv[])
{
	std::vector<float> numbers = {3, 3.1, 3.14, 3.141, 3.1415, 3.14159, 3.141592};
	std::for_each(numbers.begin(), numbers.end(), square);
	display(numbers);
	return 0;
}
