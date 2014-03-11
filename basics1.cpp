/*
Exercises
Coding:
1.Create a program that counts the occurrence of the word 'that' in a file (use the string class operator == to find the word)
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

void openfile(const char *filename, std::ifstream &infile){
    infile.open(filename);
    if (! infile.is_open()) {
        std::cout << "Error opening file:" << filename << std::endl;
        exit(1);
    }
}

int main (int argc, char const *argv[]) {
    std::string line;
    std::ifstream infile;
    int counts;
    if (argc > 1) {
        openfile(argv[1], infile);
    } else {
        openfile("sample.txt", infile);
    }
    while (infile >> line){
        if (line == "that")
            counts++;
    }
    infile.close();
    std::cout << "found " << counts << " 'that'." << std::endl;
    return 0;
}
