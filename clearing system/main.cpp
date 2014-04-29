#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <exception>
#include <map>
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

std::ostream & operator<<(std::ostream&, const class Item&);

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
		try{
			if (attrs.size() != 4){
				throw "UCCU,你看看这嘛玩意:\n";   // 果断扔出错误，嘲讽用户。
			}
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
			throw e;
		}catch (std::exception& e){
			std::cerr << "ERROR:" << e.what() << std::endl;
			std::cerr << "data:" << line << std::endl;
			throw e;   //【继续throw给外部。】【继续throw给外部。】
		}       // 使用try catch throw显得更加专业。
		// std::cout << *this;
	}
};
std::ostream& operator<<(std::ostream& outstream, const Item& item){
	outstream << "id:" << item.id << " name:" << item.name << " origin:" << item.origin << " base_price:" << item.base_price << "\n";
	return outstream;
}

std::ostream& operator<<(std::ostream&, const class Items&);
typedef std::map<unsigned long, Item*> ItemsMAP;
class Items{
public:
	ItemsMAP map;
	Items(std::string filename){
		std::ifstream infile(filename);
		for (std::string line; std::getline(infile, line);)
		{
			try{
				auto new_item = new Item(line);
				map[new_item->id] = new_item;
			}catch(char const* e){

			}catch(std::exception& e){

			} // 捕获错误以免不良数据录入
		}
	}
};
std::ostream & operator<<( std::ostream &outstream, const Items &items ){
	for (ItemsMAP::const_iterator iter=items.map.begin(); iter != items.map.end(); ++iter)
	{
		outstream << *(iter->second);
	}
	return outstream;
}

std::ostream& operator<<(std::ostream&, const class Customer&);
class Customer
{
public:
	unsigned long id;
	std::string name;
	std::string gender;
	std::string phone;   // 以便兼容+86之类的格式。也省的转换
	int level;
	unsigned long points;
	Customer(std::string line){
		/*  id,姓名、性别、联系电话、会员级别、积分
			id,王尼玛,男,18888888888,1,89214
		*/ 
		auto attrs = split(line, ',');
		try{
			if (attrs.size() != 6)
				throw "bad Customer data:";
			long result = std::stoul(attrs[0]);
			if (result < 0)
				throw "UCCU! id can't be negative\n";
			id = result;
			name = attrs[1];
			gender = attrs[2];
			phone = attrs[3];
			level = std::stoi(attrs[4]);
			points = std::stoul(attrs[5]);
		}catch(char const* e){
			std::cerr << e;
			std::cerr << "data:" << line << std::endl;
			throw e;
		}catch(std::exception& e){
			std::cerr << "ERROR:" << e.what() << std::endl;
			std::cerr << "data:" << line << std::endl;
			throw e;
		}
		std::cout << *this;
	}
};
std::ostream& operator<<(std::ostream& outstream, const Customer& customer){
	outstream << "id:" << customer.id << "\tname:" << customer.name << "\tgender:" << customer.gender << "\tphone:" << customer.phone << "\tlevel:" << customer.level << "\tpoints:" << customer.points << "\n";
	return outstream;
}

typedef std::map<unsigned long, Customer*> Customers_MAP;
std::ostream& operator<<(std::ostream&, const class Customers&);
class Customers
{
public:
	Customers_MAP map;
	Customers(std::string filename){
		std::ifstream infile(filename);
		for (std::string line; std::getline(infile, line);)
		{
			try{
				auto new_customer = new Customer(line);
				map[new_customer->id] = new_customer;
			}catch(char const* e){

			}catch(std::exception& e){

			} // 捕获错误以免不良数据录入
		}
	}
};
std::ostream& operator<<(std::ostream& outstream, const class Customers& customers){
	for (Customers_MAP::const_iterator iter=customers.map.begin(); iter != customers.map.end(); ++iter)
	{
		outstream << *(iter->second);
	}
	return outstream;
}

int main(int argc, char const *argv[])
{
	// auto one = Item("0,大饼卷大葱,山东,998.89");
	auto products = Items("db_goods.csv");
	std::cout << "\n\n";
	// std::cout << products.map.end()->second;
	// std::cout << products;
	// auto customer = Customer("0,王尼玛,男,18888888888,1,89214");
	auto customers = Customers("db_users.csv");
	return 0;
}