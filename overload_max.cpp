/*
1. 实现不同（重载）的 max() 函数，其输入参数为： 
- int 型的 vector 
- float 型的vector 
- string型的vector 
- int 型的数组，数组大小 
- float 型的数组，数组大小 
- string型的数组，数组大小 
然后，用模板来重新实现max() 函数。用 main()函数来测试这些函数。 
*/

#include <vector>
#include <iostream>
#include <exception>
#include <iterator>

class EmptyContainerException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "The container is empty thus can't return the max item.";
  }
} EmptyContainer;

int &max(std::vector<int> &vect){
	int tmp;
	size_t index = 0;
	if (vect.size()){
		tmp = vect[0];
	}else{
		throw EmptyContainer;
	}
	for (size_t i = 0; i < vect.size(); ++i)
	{
		if (vect[i] > tmp){
			tmp = vect[i];
			index = i;
		}
	}
	return vect[index];
}

float &max(std::vector<float> &vect){
	float tmp;
	size_t index = 0;
	if (vect.size()){
		tmp = vect[0];
	}else{
		throw EmptyContainer;
	}
	for (size_t i = 0; i < vect.size(); ++i)
	{
		if (vect[i] > tmp){
			tmp = vect[i];
			index = i;
		}
	}
	return vect[index];
}

std::string &max(std::vector<std::string> &vect){
	std::string tmp;
	size_t index = 0;
	if (vect.size()){
		tmp = vect[0];
	}else{
		throw EmptyContainer;
	}
	for (size_t i = 0; i < vect.size(); ++i)
	{
		if (vect[i] > tmp){
			tmp = vect[i];
			index = i;
		}
	}
	return vect[index];
}

int &max(int ints[], size_t size){
	if (!size)
		throw EmptyContainer;
	int tmp=ints[0];
	int *pointer = &ints[0];
	for (size_t i = 0; i < size; ++i){
		if (tmp < ints[i]){
			tmp = ints[i];
			pointer = &ints[i];
		}
	}
	return *pointer;
}

float &max(float ints[], size_t size){
	if (!size)
		throw EmptyContainer;
	float tmp=ints[0];
	float *pointer = &ints[0];
	for (size_t i = 0; i < size; ++i){
		if (tmp < ints[i]){
			tmp = ints[i];
			pointer = &ints[i];
		}
	}
	return *pointer;
}

std::string &max(std::string ints[], size_t size){
	if (!size)
		throw EmptyContainer;
	std::string tmp=ints[0];
	std::string *pointer = &ints[0];
	for (size_t i = 0; i < size; ++i){
		if (tmp < ints[i]){
			tmp = ints[i];
			pointer = &ints[i];
		}
	}
	return *pointer;
}

template <typename T>
auto GetMax(T &container) -> decltype(container[0]){
	// note that decltype(container[0] is int&
	// and this function returns the reference of the max item
	if (container.size()){
		auto tmp = container[0];
		typename T::iterator iter = container.begin();
		auto *pointer = &(*iter);
		for (; iter != container.end(); ++iter)
		{
			if (*iter > tmp){
				tmp = *iter;
				pointer = &(*iter);
			}
		}
		return *pointer;
	}else{
		throw EmptyContainer;
	}
}

int main(int argc, char const *argv[])
{
	std::vector<int> ints({1,9,3,4,5,57,8,10});
	std::vector<int> v;
	std::vector<float> floats({1.2,9.5,3.6,4,5.6,57.111,8,10});

	int array_ints[] = {9,4,1,3,8};
	float array_floats[] = {88.8, 7.7, 9.9};
	std::string array_strings[] = {"A", "X", "AGHE", "ZZZ"};
	// std::vector<float> v;
	std::vector<std::string> strings({"a","b","3","c","5","AA","HEW","10"});
	// std::vector<std::string> v;
	std::cout << max(ints) << '\n';
	std::cout << max(floats) << '\n';
	std::cout << max(strings) << "\n\n";

	std::cout << max(array_ints, sizeof(array_ints)/sizeof(int)) << '\n';
	std::cout << max(array_floats, sizeof(array_floats)/sizeof(int)) << '\n';
	std::cout << max(array_strings, sizeof(array_strings)/sizeof(char *)) << '\n';


	std::cout << GetMax(ints) << " @" << &GetMax(ints) << '\n';
	std::cout << "ints[5]=" << ints[5] << " @" << &ints[5] << "\n\n";

	std::cout << GetMax(floats) << " @" << &GetMax(floats) << '\n';
	std::cout << "floats[5]=" << floats[5] << " @" << &floats[5] << "\n\n";

	std::cout << GetMax(strings) << " @" << &GetMax(strings) << '\n';
	std::cout << "strings[3]=" << strings[3] << " @" << &strings[5] << "\n\n";
	return 0;
}