#define _CRT_SECURE_NO_WARNINGS
//IO流
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
struct info
{
	string name;
	int age;
	int score;
};
int main()
{
	//int a = 0;
	//// C++ cout和cin能自动识别对象类型，因为本质他是一个函数重载区分识别
	//scanf("%d", &a);
	//printf("%d", a);

	//cin >> a; // cin是标准库中定义的istream类型的全局对象
	//cout << a;// cout是标准库中定义的ostream类型的全局对象

	//cin.operator>>(a);
	//cout.operator<<(a);

	//ofstream ofs("test.txt");//fopen();
	//ofs.put('x');            //fputc
	//ofs.write("1111111", 3); //fwrite
	//ofs.close();

	//ifstream ifs("test.txt"); //fopen(R);
	//cout << (char)ifs.get() << endl;
	////ifs.read               // fread

	//读写一个结构体
	//info in  { "小明",18 };//写
	//ofstream ofs("test.txt"); //fopen("w")
	//ofs << in.name << endl;
	//ofs << in.age << endl;
	//ofs.close();

	//info rin;//读
	//ifstream ifs("test.txt");
	//ifs >> rin.name;
	//ifs >> rin.age;


	info in{ "小明",18,99};
	ostringstream ost;
	ost << in.name << endl;
	ost << in.age << endl;
	ost << in.score << endl;

	string str1 = ost.str();
	cout << str1 << endl;
	// 网络中就可以把这个strl发送给另一端。
	// 网络另一端接收到以后就可以解析数据
	istringstream ist;
	ist.str(str1);
	info rin;
	ist >> rin.name;
	ist >> rin.age;
	ist >> rin.score;
	return 0;
}