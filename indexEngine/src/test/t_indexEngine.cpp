/*************************************************************************
    @ File Name: t_indexEngine.cpp
    @ Method:
    @ Author: Jerry Shi
    @ Mail: jerryshi0110@gmail.com 
    @ Created Time: 2015年07月15日 星期三 17时48分54秒
 ************************************************************************/
#include "../indexEngine.h"

using namespace std;

int main()
{
	string pth = "/home/lscm/mproj/workproj/kuaipan/query_recomm_http/q_similar/dict";

	cout << "Start indexing..." << endl;
	indexEngine mIndex(pth);

	string corpus = "query.txt";
	//string corpus = "/home/lscm/mproj/workproj/kuaipan/dictionary/corpus/query.txt";
	mIndex.indexing(corpus);
	mIndex.flush();
	mIndex.close();

	cout << "End process!" << endl;

	return 0;
}


