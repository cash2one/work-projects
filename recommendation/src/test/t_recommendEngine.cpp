/*************************************************************************
    @ File Name: t_recommendEngine.cpp
    @ Method:
    @ Author: Jerry Shi
    @ Mail: jerryshi0110@gmail.com 
    @ Created Time: 2015年07月20日 星期一 15时10分54秒
 ************************************************************************/
#include "../recommendEngine.h"

using namespace std;

int main(int argc, char* argv[])
{
	/*
	if(argc < 2)
	
	{
		cout << "Usage: Please input query and  rerun the program!" << endl;
		return -1;
	}*/

	cout << "Start recommend engine ..." << endl;
	string pth = "/home/lscm/mproj/workproj/kuaipan/query_recomm_http/q_similar/dict";
	string dict = "/home/lscm/mproj/workproj/github/dict";
	recommendEngine mRecomm(pth, "../../");
    //string s = "我的POLO裙子";
	//string s = argv[1];
	string s = "";
	string res;
	cout << "please input query:" << endl;
	while(cin >> s)
	{
		res = "";
	mRecomm.jsonResults(s,res);
	cout << "recommend results:" << res << endl;
	cout << "please input query:" << endl;
	}
	cout << "End process!\t";	
	return 0;
}


