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
	//string corpus = "query.txt";
	string corpus = "/home/lscm/mproj/workproj/kuaipan/dictionary/querylog/201504-05_search_corpus_results.corp";
	//string corpus = "/home/lscm/mproj/workproj/kuaipan/dictionary/querylog/keyword_20141201_20150131_corpus_results.corp";
//string corpus = "/home/lscm/mproj/workproj/kuaipan/dictionary/querylog/keyword_20150201_20150331_corpus_results.corp";
	mIndex.open();
	mIndex.indexing(corpus);
	mIndex.insert(mdat);
	Terms2QidMap termsMap;
	QueryIdataMap queryMap;
	
	String2IntMap v;
    v = mIndex.search(mdat.text,termsMap,queryMap);
	mIndex.flush();
	mIndex.close();

	cout << "test termsMap.size:" << termsMap.size() << "\tqueryMap.size:" << queryMap.size() << endl;
	cout <<"v.size" <<v.size() <<"\nEnd process!" << endl;

	return 0;
}


