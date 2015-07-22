/*************************************************************************
    @ File Name: t_json.cpp
    @ Method:
    @ Author: Jerry Shi
    @ Mail: jerryshi0110@gmail.com 
    @ Created Time: 2015年07月21日 星期二 15时15分03秒
 ************************************************************************/
#include <iostream>
#include "json/json.h"

using namespace std;

int main()
{
	Json::Value jsonResult;
	Json::Value correction;
	Json::Value recommend;


	correction.append("co1");
	correction.append("co2");
	correction.append("co3");
	correction.append("co4");
	
	recommend.append("keyword1");
	recommend.append("keyword2");
	recommend.append("keyword3");
	recommend.append("keyword4");
	recommend.append("keyword5");

	jsonResult["noresults"] = "keyword";
	jsonResult["recommendation"] = recommend;
	jsonResult["correction"] = correction;

	string out = jsonResult.toStyledString();

	cout << out << endl;


	return 0;


}



