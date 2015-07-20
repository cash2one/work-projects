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
	indexEngine mIndex(pth,"../");
	QueryData mdat;
	mdat.text = "ILOVE YOU";
	mdat.hits = 12;
	mdat.counts = 2400;
	string corpus = "query.txt";
	//string corpus = "/home/lscm/mproj/workproj/kuaipan/dictionary/corpus/query.txt";
	mIndex.indexing(corpus);
	mIndex.insert(mdat);
	Terms2QidMap termsMap;
	QueryIdataMap queryMap;
	mIndex.open();
	String2IntMap v;
    v = mIndex.search(mdat.text,termsMap,queryMap);
	mIndex.flush();
	mIndex.close();

	cout << "test termsMap.size:" << termsMap.size() << "\tqueryMap.size:" << queryMap.size() << endl;
	cout <<"v.size" <<v.size() <<"\nEnd process!" << endl;

	return 0;
}


