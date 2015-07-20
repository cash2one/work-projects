/*************************************************************************
    @ File Name: t_delete.cpp
    @ Method:
    @ Author: Jerry Shi
    @ Mail: jerryshi0110@gmail.com 
    @ Created Time: 2015年07月17日 星期五 10时57分18秒
 ************************************************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include "time.h"
#include "stdio.h"
using namespace std;

int main()
{
	vector<string> v;
	string s = "491401	2015夏季搭配套装	8	531	648091	291810	462165	503062";
	int count = 0;
	size_t start = clock();
	char model = '\t';
	count = std::count(s.begin(),s.end(),model);
	while(count--)
	{
		size_t pos = s.find('\t');
		if(pos != string::npos)
		{
			string ss = s.substr(0,pos);
			v.push_back(ss);
			s.assign(s,pos+1,s.length()-1);
		}
	}
	v.push_back(s);

	cout << "string:" << s << endl;
	cout << "v.size:" << v.size() << endl;
	for(int i = 0;i < v.size();++i)
		cout << "elements:" << v[i] <<endl;
cout << "test---\n";
vector<string>::iterator it;
it = v.begin();
v.erase(it);
cout << "after delete 0: size is" << v.size() << "first element:"  << v[0] << endl;

it = v.begin();
v.erase(it);
cout << "after delete 1: size is" << v.size() << "first element:"  << v[0] << endl;
it = v.begin();
v.erase(it);
cout << "after delete 2: size is" << v.size() << "first element:"  << v[0] << endl;
it = v.begin();
v.erase(it);
cout << "after delete 3: size is" << v.size() << "first element:"  << v[0] << endl;
cout << "after delete : size is" << v.size() << "first element:"  << v[0] << endl;


printf("time const:%f\n",(double)(clock()-start)/CLOCKS_PER_SEC);
}
