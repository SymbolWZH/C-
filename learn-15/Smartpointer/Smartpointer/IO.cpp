#define _CRT_SECURE_NO_WARNINGS
//IO��
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
	//// C++ cout��cin���Զ�ʶ��������ͣ���Ϊ��������һ��������������ʶ��
	//scanf("%d", &a);
	//printf("%d", a);

	//cin >> a; // cin�Ǳ�׼���ж����istream���͵�ȫ�ֶ���
	//cout << a;// cout�Ǳ�׼���ж����ostream���͵�ȫ�ֶ���

	//cin.operator>>(a);
	//cout.operator<<(a);

	//ofstream ofs("test.txt");//fopen();
	//ofs.put('x');            //fputc
	//ofs.write("1111111", 3); //fwrite
	//ofs.close();

	//ifstream ifs("test.txt"); //fopen(R);
	//cout << (char)ifs.get() << endl;
	////ifs.read               // fread

	//��дһ���ṹ��
	//info in  { "С��",18 };//д
	//ofstream ofs("test.txt"); //fopen("w")
	//ofs << in.name << endl;
	//ofs << in.age << endl;
	//ofs.close();

	//info rin;//��
	//ifstream ifs("test.txt");
	//ifs >> rin.name;
	//ifs >> rin.age;


	info in{ "С��",18,99};
	ostringstream ost;
	ost << in.name << endl;
	ost << in.age << endl;
	ost << in.score << endl;

	string str1 = ost.str();
	cout << str1 << endl;
	// �����оͿ��԰����strl���͸���һ�ˡ�
	// ������һ�˽��յ��Ժ�Ϳ��Խ�������
	istringstream ist;
	ist.str(str1);
	info rin;
	ist >> rin.name;
	ist >> rin.age;
	ist >> rin.score;
	return 0;
}