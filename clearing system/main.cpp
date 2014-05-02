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

typedef unsigned long Item_ID;
class Item
{
public:       // Trust programmer that these won't be set inappropriately
	Item_ID id;
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
	outstream << "id:" << item.id << "\tname:" << item.name << "\torigin:" << item.origin << "\tbase_price:" << item.base_price; // << "\n";
	return outstream;
}

std::ostream& operator<<(std::ostream&, const class Items&);
typedef std::map<unsigned long, Item*> Items_MAP;
class Items{
public:
	Items_MAP map;
	Items();
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
std::ostream& operator<<(std::ostream &outstream, const Items &items){
	for (Items_MAP::const_iterator iter=items.map.begin(); iter != items.map.end(); ++iter)
	{
		outstream << *(iter->second);
	}
	return outstream;
}

typedef unsigned long Customer_ID;
std::ostream& operator<<(std::ostream&, const class Customer&);
class Customer
{
public:
	Customer_ID id;
	std::string name;
	std::string gender;
	std::string phone;   // 以便兼容+86之类的格式。也省的转换
	int level;
	unsigned long points;
	Customer();
	Customer(std::string line){
		/*  id,姓名、性别、联系电话、会员级别、积分
			0,王尼玛,男,18888888888,1,89214
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
		// std::cout << *this;
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


std::ostream& operator<<(std::ostream&, const class Card&);
class Card
{
public:
	std::string id;
	int balance;
	Card(std::string line){
		auto attrs = split(line, ',');
		try{
			if (attrs.size() != 2)
				throw "Bad Card data";
			id = attrs[0];
			balance = std::stoi(attrs[1]);
		}catch(char const* e){
			std::cerr << e;
			std::cerr << "data:" << line << std::endl;
			throw e;
		}catch(std::exception& e){
			std::cerr << "ERROR:" << e.what() << std::endl;
			std::cerr << "data:" << line << std::endl;
			throw e;
		}
	}
	Card& pay(float amount){
		if (balance < amount){
			std::ostringstream msg;
			msg << "卡内余额不足。余额：" << balance;
			throw msg.str();
		}else{
			balance -= amount;
			return *this;
		}
	}
};
std::ostream& operator<<(std::ostream& outstream, const class Card& card){
	outstream << "id:" << card.id << "\tbalance:" << card.balance << "\n";
	return outstream;
}


typedef std::map<std::string, Card*> Cards_MAP;
std::ostream& operator<<(std::ostream&, const class Cards&);
class Cards
{
public:
	Cards_MAP map;
	Cards(std::string filename){
		std::ifstream infile(filename);
		for (std::string line; std::getline(infile, line);){
			try{
				auto new_card = new Card(line);
				map[new_card->id] = new_card;
			}catch(char const* e){

			}catch(std::exception& e){

			}
		}
	}
	Card* find(std::string id){
		if (map.count(id)){
			return map[id];
		}else{
			throw "card id not found: " + id;
		}
	}
};
std::ostream& operator<<(std::ostream& outstream, const class Cards& cards){
	for (Cards_MAP::const_iterator iter = cards.map.begin(); iter != cards.map.end(); ++iter)
	{
		outstream << *(iter->second);
	}
	return outstream;
}

// 可以写成模板类和模板函数。。嫌烦。

typedef std::map<Item_ID, int> Cart_MAP;
std::ostream& operator<<(std::ostream&, const class Cart&);
class Cart
{
public:
	const Customer& customer;
	const Items& items;
	Cart_MAP map;
	Cart(Customer& customer, Items& items): customer(customer), items(items){
		/* 购物车与顾客及商品列表绑定 */
	}
	Cart& add(Item_ID id, int quantity=1){
		if (this->items.map.count(id)==0)
			throw "product does not exist\n";
		if (map.count(id)>0){
			map[id] += quantity;
		}else{
			map[id] = quantity;
		}
		if (map[id] < 1)
			map.erase(id);
		return *this;
	}
	float total() const{
		float _total = 0;
		for (Cart_MAP::const_iterator iter = map.begin(); iter != map.end(); ++iter)
		{
			auto item = *items.map.find(iter->first)->second;
			_total += item.base_price*iter->second;
		}
		return _total;
	}
};
std::ostream& operator<<(std::ostream& outstream, const class Cart& cart){
	outstream << "Items in Cart:\n";
	for (Cart_MAP::const_iterator iter = cart.map.begin(); iter != cart.map.end(); ++iter)
	{
		auto item = cart.items.map.find(iter->first);
		outstream << *(item->second) << "\tQuantity:" << iter->second << "\n";
	}
	outstream << "\t\t\t total: " << cart.total() << "\n";
	return outstream;
}


Cart& init_cart(Customers& customers, Items& products){
	bool valid_user = false;
	std::string token;
	Customer_ID id;
	while (not valid_user){
		std::cout << customers;
		std::cout << "input a id to choose User:\n";
		std::cin >> token;
		try{
			id = std::stoul(token);
		}catch(std::exception& e){
			std::cerr << "id should be a unsigned long" << std::endl;
			continue;
		}
		auto iter = customers.map.find(id);
		if (iter == customers.map.end()){
			std::cerr << "id:" << id << "not found\n";
		}else{
			auto customer = *iter->second;
			auto cart = new Cart(customer, products);
			return *cart;
		}
	}
	throw "init_cart failed.\n";
}

Cart& input_goods(Cart& cart){
	std::string token;
	Item_ID id;
	int quantity;
	while (true){
		std::cout << "======================================\n"
					 "input goods id and quantity like this:\n"
					 "240,1\n"
					 "or just the id:\n"
					 "240\n"
					 "type exit or ok to exit\n"
					 "======================================\n";
		std::cin >> token;
		try{
			if (token == "exit" or token == "ok")
				break;
			auto attrs = split(token, ',');
			if (attrs.size() == 1){
				id = std::stoul(attrs[0]);
				quantity = 1;
			}else{
				id = std::stoul(attrs[0]);
				quantity = std::stoi(attrs[1]);
			}
			cart.add(id, quantity);
		}catch(char const* e){
			std::cerr << e << std::endl;
		}catch(std::exception& e){
			std::cerr << "UCCU." << std::endl;
		}
	}
	return cart;
}

float input_float(){
	std::string token;
	float pay;
	std::cin >> token;
	pay = std::stof(token);
	if (pay < 0)
		throw "are you kidding !?\n";
	return pay;
}

float pay_cash(float total){
	float give;
	float pay;
	while(true){
		std::cout << "give me some money\n";
		try{
			give = input_float();
			std::cout << "good, and how much would you pay with cash?\n";
			pay = input_float();
			pay = fmin(pay, give);
			pay = fmin(pay, total);
			std::cout << "receive $" << give << "\tpay $" << pay << "\n changes: $" << give - pay << "\n";
			return pay;
		}catch(char const* e){
			std::cerr << e << std::endl;
		}catch(std::exception& e){
			std::cerr << "UCCU. " << e.what() << std::endl;
		}
	}
}

float pay_credit(float total){
	/* 我拒绝做如此愚蠢的步骤。:如以银行卡支付,用户应录入银行卡号、姓名、消费数额等信息。 */
	float pay;
	while (true){
		std::cout << "how much would you pay with your credit card?\n";
		try{
			pay = input_float();
			pay = fmin(pay, total);
			std::cout << "you paid " << pay << "$ with your credit card.\n";
			return pay;
		}catch(std::exception& e){
			std::cerr << "UCCU. " << e.what() << std::endl;
		}
	}
}

float pay_shopping_card(float total, Cards cards){
	std::string token;
	float pay;
	Card* card;
	while (true){
		std::cout << "how much would you pay with shopping card?\n";
		try{
			pay = input_float();
			pay = fmin(pay, total);
			std::cout << "what's the shopping card number?\n";
			std::cin >> token;
			card = cards.find(token);
			std::cout << *card;
			card->pay(pay);
			return pay;
		}catch(std::exception& e){
			std::cerr << "UCCU." << e.what() << std::endl;
		}catch(char const* e){
			std::cerr << e << std::endl;
		}catch(std::string msg){
			std::cerr << msg << std::endl;
		}
	}
}

void pay(Cart& cart, Cards& cards){
	std::string token;
	int choice;
	float total = cart.total();
	while (total > 0){
		std::cout << "=======================================================================\n"
					 "0 for pay with cash\t 1 for credit card \t 2 for shopping card\n"
					 "total: " << total << "\n"
					 "=======================================================================\n";
		std::cin >> token;
		try{
			choice = std::stoi(token);
			switch(choice){
				case 0:
					total -= pay_cash(total);
					break;
				case 1:
					total -= pay_credit(total);
					break;
				case 2:
					total -= pay_shopping_card(total, cards);
					break;
			}
		}catch(std::exception& e){
			std::cerr << "should input a number" << std::endl;
		}
	}
	std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
				 "         You have paid all $" << cart.total() << "\n"
				 "         Thank you. Bye.\n"
				 "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
}

int main(int argc, char const *argv[])
{
	// 测试数据改自施闻轩的。
	auto products = Items("items.csv");
	std::cout << products.map.size() << " itmes imported.\n";
	auto customers = Customers("customers.csv");
	std::cout << customers.map.size() << " customers imported.\n";
	auto cards = Cards("cards.csv");
	std::cout << cards.map.size() << " cards imported.\n";

	auto cart = init_cart(customers, products);
	std::cout << input_goods(cart);
	pay(cart, cards);
	
	return 0;

}