/*
Exercises
Coding:
2.Create a vector<float> and put 25 numbers into it. Then square each number and put the result back into the same location in the vector. Display the vector before and after the multiplications. 
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
	display(numbers);
	std::for_each(numbers.begin(), numbers.end(), square);
	display(numbers);
	return 0;
}
