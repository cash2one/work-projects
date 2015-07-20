/*************************************************************************
    @ File Name: t_main.cpp
    @ Method:
    @ Author: Jerry Shi
    @ Mail: jerryshi0110@gmail.com 
    @ Created Time: 2015年07月14日 星期二 14时16分35秒
 ************************************************************************/
#include <iostream>
#include <stdio.h>
#include "../StringUtil.h"
#include "../StringUtil.cpp"

using namespace std;

int main(void)
{
	cout << "-----Unit test case 1: construct2\n";
	FreqString fstr1;
	cout << "\tDefault string:" << fstr1.getString() << "\tDefault freq:"
		 << fstr1.getFreq() << "\t Defalut freq:" << fstr1.getPosition() << endl;

	cout << "----->Unit test case 2: Default construct2\n";
	FreqString fstr2("abcdef",11.22);
	cout << "\tStr_:" << fstr2.getString() << "\tFreq_:"
		 << fstr2.getFreq() << "\tPos_:" << fstr2.getPosition() << endl;

	cout << "----->Unit test case 3: Default construct3\n";
	FreqString fstr3("abcdef",11.22,112233);
	cout << "\tStr_:" << fstr3.getString() << "\tFreq_:"
		 << fstr3.getFreq() << "\tPos_:" << fstr3.getPosition() << endl;

	cout << "----->Unit test case 4: Default construct4\n";
	FreqString fstr4(fstr3);
	cout << "\tStr_:" << fstr4.getString() << "\tFreq_:"
		 << fstr4.getFreq() << "\tPos_:" << fstr4.getPosition() << endl;



	cout << "----->Unit test case 5: Edit Distance\n";
	std::string sstr = "abcdef";
	std::string tstr = "abcmef";
	int distance;
	distance = editDistance(sstr,tstr);
	printf("\tThe levenshtein distance of %s and %s is %d\n",sstr.c_str(),tstr.c_str(),distance);
	sstr = "连衣裙";
	tstr = "女装连衣裙";
	distance = editDistance(sstr,tstr);
	printf("\tThe levenshtein distance of %s and %s is %d\n",sstr.c_str(),tstr.c_str(),distance);
	

	//cout << "----->Unit test case 4: Default construct4\n";
	//cout << "----->Unit test case 4: Default construct4\n";
	//cout << "----->Unit test case 4: Default construct4\n";

	return 0;
}

