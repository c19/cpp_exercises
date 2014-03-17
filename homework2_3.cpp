/*
3. 请撰写一个可以统计英语文章中出现字母（a~ z）频率的程序。它从一个用户指定的文本文件 
(“article1.txt”，请从网页上下载此文件) 中读取字符，并统计每个字符出现的次数。将统
计的字母及其频率结果输出到一个文件“letter_freq.txt”。 
*/

#include <string>
#include <iostream>
#include <iterator>
#include <map>
#include <fstream>

typedef std::map<char, unsigned int> WORDS_MAP;

inline void display(const WORDS_MAP &words, std::ostream &out=std::cout){
	for(WORDS_MAP::const_iterator iter=words.begin(); iter !=words.end(); ++iter){
		out << iter->first << ":  " << iter->second << '\n';
	}
}

int main()
{	
	WORDS_MAP words;
	std::ifstream infile("article1.txt");
	char ch;
	while (infile >> ch){
		words[ch]++;
		std::cout << ch << '|';
	}
	std::cout << "\n\n";
	display(words);
	std::ofstream outfile("letter_freq.txt");
	display(words, outfile);
}