/*************************************************************************
    @ File Name: t_normalize.cpp
    @ Method:
    @ Author: Jerry Shi
    @ Mail: jerryshi0110@gmail.com 
    @ Created Time: 2015年07月23日 星期四 14时55分33秒
 ************************************************************************/
#include <iostream>
#include "../normalize.h"

using namespace std;


int main()
{
	string s = " 123/PolO  ";
	cout << "Original:" << s <<endl;
	try
	{
		Normalize::normalize(s);
	}
	catch(...)
	{
	}

	cout << "After normalize:" << s << endl;
}

