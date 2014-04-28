#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

// =========================================
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
// shamelessly copy code from stackoverflow
// =========================================
//重载<<使代码更简洁
std::ostream& operator<<(std::ostream& outstream, std::vector<std::string>& str_vector) {
	std::vector<std::string>::iterator iter=str_vector.begin();    // 用迭代器(Iterator)更加高大上
	for (; iter != str_vector.end(); ++iter){
		outstream << *iter << " ";
	}
	return outstream;
}
/*
  Item()
*/
class Item
{
private:   // this can be removed for members are default `private`.
	unsigned int id;
	std::string name;
	std::string origin = "unset";
public:
	Item(){
		std::cout << "Empty Item created.\n";
	}
	Item(std::string line){
		auto attrs = split(line, ',');
		std::cout << "parsed args: " << attrs << "\n";
	}
	~Item(){
		std::cout << "Item deleted.\n";
	}
	
};


class Customer
{
public:
	Customer();
	~Customer();
	
};

int main(int argc, char const *argv[])
{
	auto one = Item("0,a,b,c,d");
	return 0;
}