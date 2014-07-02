/*
面向对象的程序设计（C++）习题5 
Deadline: 12：00 (中午)，2014.04.11 
作业提交时请注意命名格式，例子：姓名_学号_ex5。 
 
 
写一个三维空间的“顶点”类 class vertex，达到如下要求： 
一、构造函数 
a) 一个无参数的构造函数，将三个坐标值初始化为 0。   
b) 一个含有三个参数的构造函数，能够指定三个坐标值。 
c) 一个拷贝构造函数。 
 
 
二、运算符重载 
a) 重载加号运算符，使得其运算结果是一个“顶点”，其坐标值分别是两个顶点相应
坐标值之和，效果类似于向量加法。 
b) 重载减号运算符，效果类似于向量减法。 
c) 重载  ==  运算符，如果两个顶点的三个坐标分别相等才返回 true。 
d) 重载  !=  运算符，如果两个顶点的三个坐标分别相等才返回 false。 
 
 
 
三、成员函数 
a) 写一个成员函数 abs()，返回该顶点的模长。（模的定义请自行查阅） 

*/
#include <iostream>
#include <cmath>

class Vertex
{
public:
	int x,y,z;
	Vertex(){
		x = 0;
		y = 0;
		z = 0;
	};
	Vertex(int _x, int _y, int _z){
		x = _x;
		y = _y;
		z = _z;
	};
	Vertex(const Vertex& origin){
		x = origin.x;
		y = origin.y;
		z = origin.z;
	};
	double abs(){
		return std::sqrt(x*x + y*y + z*z);
	}
};

std::ostream& operator<< (std::ostream& out, const Vertex& vertex){
	out << "(" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")\n";
	return out;
}

Vertex& operator+ (const Vertex& vertex1, const Vertex& vertex2){
	Vertex *result = new Vertex(vertex1.x + vertex2.x, vertex1.y + vertex2.y, vertex1.z + vertex2.z);
	return *result;
}

Vertex& operator- (const Vertex& vertex1, const Vertex& vertex2){
	Vertex *result = new Vertex(vertex1.x - vertex2.x, vertex1.y - vertex2.y, vertex1.z - vertex2.z);
	return *result;
}

bool operator== (const Vertex& vertex1, const Vertex& vertex2){
	return vertex1.x == vertex2.x and vertex1.y == vertex2.y and vertex1.z == vertex2.z;
}

bool operator!= (const Vertex& vertex1, const Vertex& vertex2){
	return not (vertex1==vertex2);
}

int main(int argc, char const *argv[])
{
	Vertex a;
	std::cout << a;
	Vertex b(2,3,4);
	std::cout << b;
	Vertex c;
	c = b;
	std::cout << c;

	std::cout << (c == b) << std::endl;
	std::cout << (a != b) << std::endl;

	std::cout << b.abs() << std::endl;
	return 0;
}