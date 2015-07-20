/*************************************************************************
    @ File Name: t_recommendEngine.cpp
    @ Method:
    @ Author: Jerry Shi
    @ Mail: jerryshi0110@gmail.com 
    @ Created Time: 2015年07月20日 星期一 15时10分54秒
 ************************************************************************/
#include "../recommendEngine.h"

using namespace std;

int main()
{
	cout << "Start recommend engine ..." << endl;
	string pth = "/home/lscm/mproj/workproj/kuaipan/query_recomm_http/q_similar/dict";

	cout << "Start indexing..." << endl;
	recommendEngine mRecomm(pth,"../");
    string s = "我的POLO裙子";
	string res;
	mRecomm.jsonResults(s,res);
	cout << "recommend results:" << res << endl;

	cout << "End process!\t";	
	return 0;
}


