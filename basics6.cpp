/*
面向对象的程序设计（C++）习题6 
Deadline: 12：00 (中午)，2014.04.18 
作业提交时请注意命名格式，例子：姓名_学号_ex6。   
 
 
 
设计一个几何图形类及其派生类。几何图形类 GeometricShape 是一个抽象类，它有三个派
生类，分别是矩形类 Rectangle、圆形类 Circle 和三角形类 Triangle。 
 
一、设计类的成员变量和成员函数。在你认为适当的类中设计成员变量和成员函数，达到如
下要求： 
1） 成员变量包括矩形的长和宽、圆的半径、三角形的三个边长。 
2） 成员函数包括 
(1) who_am_I()，返回图形名称（矩形、圆形、三角形）； 
(2) checkIntegrity()，判断输入的有效性，是否为 0 到 1024 之间的整数或小数，返回 true
或 false； 
(3) getCircumference()，返回图形周长； 
(4) getArea()，返回图形面积； 
(5) IsTriangle()，根据三条线段的长度判断这三条线段能否组成三角形，返回 true 或
false； 
(6) print()，返回形如“长为 3宽为 2 的长方形，周长为 10，面积为 6”的字符串。 
 
二、使用构造函数对类的成员变量进行初始化，矩形类 Rectangle 的构造函数参数为矩形的
长和宽，圆形类 Circle的构造函数参数为圆的半径，三角形类 Triangle 的构造函数参数为三
角形的三个边长。 
 
三、撰写 main()函数，验证类中的成员函数。 
*/

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

class GeometricShape
{
public:
	virtual std::string who_am_I() = 0;
	bool checkIntegrity(std::string str){
		double tmp = std::atof(str.c_str());
		return (tmp > 0 and tmp < 1024);
	}
	virtual double getCircumference() = 0;
	virtual double getArea() = 0;
	bool IsTriangle(double a, double b, double c){
		return (a + b > c and b + c > a and a + c > b);
	}
	std::string print(){
		std::stringstream s;
		s << who_am_I() << "\n" <<
			"getCircumference: " << getCircumference() << "\n" <<
			"getArea: " << getArea() << "\n";
		return s.str();
	}
};

class Rectangle:public GeometricShape
{
public:
	double a,b;
	Rectangle(double _a, double _b){
		a = _a;
		b = _b;
	}
	std::string who_am_I(){
		std::stringstream ss;
		ss << "Rectangle(" << a << ", " << b << ")";
		return ss.str();
	}
	double getCircumference(){
		return 2*(a + b);
	}
	double getArea(){
		return a*b;
	}
};

class Circle:public GeometricShape
{
public:
	double r;
	double pi = 3.1415926;
	Circle(double _r){
		r = _r;
	}
	std::string who_am_I(){
		std::stringstream ss;
		ss << "Circle(" << r << ")";
		return ss.str();
	}
	double getCircumference(){
		return 2*pi*r;
	}
	double getArea(){
		return pi*r*r;
	}
};

class Triangle:public GeometricShape
{
public:
	double a, b, c;
	Triangle(double _a, double _b, double _c){
		a = _a;
		b = _b;
		c = _c;
	}
	std::string who_am_I(){
		std::stringstream ss;
		ss << "Triangle(" << a << ", " << b << ", " << c <<")";
		return ss.str();
	}
	double getCircumference(){
		return a*b*c;
	}
	double getArea(){
		double p = (a + b + c) / 2;
		return std::sqrt(p*(p - a)*(p - b)*(p - c));
	}

};

int main(int argc, char const *argv[])
{
	Rectangle rect(3, 4);
	std::cout << rect.print() << std::endl;

	Circle circle(6);
	std::cout << circle.print() << std::endl;
	
	Triangle tri(5, 6, 7);
	std::cout << tri.print() << std::endl;

	return 0;
}