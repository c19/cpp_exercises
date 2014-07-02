/*
Exercises
Coding:
4.Create a struct that holds two string objects and one int. Use a typedef for the struct name. 
5.Create an instance of the struct, initialize all three values in your instance, and print them out. Take the address of your instance and assign it to a pointer to your struct type. Change the three values in your instance and print them out, all using the pointer.
*/

#include <iostream>
#include <string>

typedef struct Human
{
    unsigned int id;
    std::string first_name;
    std::string last_name;
} Human;

int main(int argc, char const *argv[])
{
    Human one;
    one.id = 0;
    one.first_name = "Dumb";
    one.last_name  = "head";
    std::cout << "\none.id=" << one.id <<
                 "\none.first_name=" << one.first_name <<
                 "\none.last_name="  << one.last_name << std::endl;
    return 0;
}