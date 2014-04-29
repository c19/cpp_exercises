#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <exception>
// #include "main.h"
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
// 无耻复制stackoverflow的代码，我们不生产代码。我们只是stackoverflow github 的搬运工。
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

std::ostream & operator <<( std::ostream &outstream, const class Item &item );

/*
  Item()
*/
class Item
{
public:       // Trust programmer that these won't be set inappropriately
	unsigned long id;
	std::string name;
	std::string origin = "unset";
	float base_price;

	Item(std::string line){
		/*  id,name,origin,price
			0,大饼卷大葱,山东,998
		 */
		auto attrs = split(line, ',');     // 编译器会知道这里auto应该是std::vector<std::string>的
		// std::cout << "parsed args: " << attrs << "\n";
		if (attrs.size() != 4){
			throw "UCCU,你看看这嘛玩意:";   // 果断扔出错误，嘲讽用户。
		}
		try{
			long result = std::stoul(attrs[0]);
			if (result < 0)
				throw "UCCU! id can't be negative\n";
			id = result;
			name = attrs[1];
			origin = attrs[2];
			base_price = std::stof(attrs[3]);
			if (base_price < 0)
				throw "price can't be negative.\n";
		}catch(char const* e){
			std::cerr << e;
			std::cerr << "data:" << line << std::endl;
		}catch (std::exception& e){
			std::cerr << "ERROR:" << e.what() << std::endl;
			std::cerr << "data:" << line << std::endl;
		}       // 使用try catch throw显得更加专业。【应该扩展为外部处理错误。】
		std::cout << *this;
	}
	~Item(){
		std::cout << "Item deleted.\n";
	}
};

std::ostream& operator<<(std::ostream& outstream, const Item& item){
	outstream << "id:" << item.id << " name:" << item.name << " origin:" << item.origin << " base_price:" << item.base_price << "\n";
	return outstream;
}

// std::vector<Item>& init_items

class Customer
{
public:
	Customer();
	~Customer();
	
};

int main(int argc, char const *argv[])
{
	auto one = Item("0,大饼卷大葱,山东,998.89");
	std::cout << one;
	return 0;
}