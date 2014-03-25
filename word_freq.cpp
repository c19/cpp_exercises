/*
count words frequent in a string
*/

#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <iterator>
#include <vector>
#include <utility>    // std::pair
#include <algorithm>  // std::sort

typedef std::map<std::string, unsigned int> WORDS_MAP;
typedef std::pair<std::string, unsigned int> PAIR;

struct CmpByValue {  
  bool operator()(const PAIR &lhs, const PAIR &rhs) {  
    return lhs.second > rhs.second;
  }
};

std::ostream& operator<< (std::ostream& out, const std::vector<PAIR>& vect) {
	for (std::vector<PAIR>::const_iterator iter=vect.begin(); iter != vect.end(); iter++)
	{
    	out << iter->first << ": " << iter->second << '\n';
	}
    return out;
} 

inline void display(const WORDS_MAP &words, std::ostream &out=std::cout){
	for(WORDS_MAP::const_iterator iter=words.begin(); iter !=words.end(); ++iter){
		out << iter->first << ":  " << iter->second << '\n';
	}
}

void parse_line(WORDS_MAP &words, std::string &line){
	static std::set<char> letters({'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y','A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y'});
	std::string::const_iterator iter=line.begin();
	std::set<char>::const_iterator result;
	std::string tmp;
	for (; iter != line.end(); ++iter)
	{
		result = letters.find(*iter);
		if (result != letters.end()){
			tmp += *result;
		}else{
			if (tmp.size()){
				words[tmp]++;
				tmp = "";
			}
		}
	}

}

int main(int argc, char const *argv[])
{
	WORDS_MAP words;
	std::ifstream infile("1984.txt");
	std::string line;
	while (std::getline(infile, line)){
		parse_line(words, line);
	}
	infile.close();
	std::vector<PAIR> words_vec(words.begin(), words.end());
	std::sort(words_vec.begin(), words_vec.end(), CmpByValue());

	std::ofstream outfile("1984.txt.count");
	outfile << words_vec;
	outfile.close();
	return 0;
}