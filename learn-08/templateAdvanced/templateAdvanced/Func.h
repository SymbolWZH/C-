#pragma once
#include <iostream>
using namespace std;


void F1()
{
	cout << " F1" << endl;
}
//同样是分离编译，普通函数可以，函数模板/类模板为什么不行?
// 预处理-> 展开头文件 替换宏 条件编译 删除注释 .i
// 编译 检查语法 生成汇编代码  .s
// 汇编 将汇编代码转成二进制的机器码 .o
// 链接 将目标文件合到一起，编译时函数有声明，链接时去找函数的地址  a.out
template<class T>
void F2(const T& x)
{
	cout << "void f2 const T"<<x << endl;
}
// 1 显式实例化  不常用 因为不方便
// 2 不要分离编译
//template
//void F2<int>(const int& x);