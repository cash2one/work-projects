/*************************************************************************
    @ File Name: recommendEngine.cpp
    @ Method: recommend engine,query recommendation,correction,etc.
    @ Author: Jerry Shi
    @ Mail: jerryshi0110@gmail.com 
    @ Created Time: 2015年07月17日 星期五 15时52分57秒
 ************************************************************************/
#include "recommendEngine.h"

bool Is_subset(vector<std::size_t> v1,vector<std::size_t> v2);
void caculateNM(vector<std::size_t> v1,vector<std::size_t> v2,std::size_t& cnt);


//construct,and initialize
recommendEngine::recommendEngine(const std::string& token_dir,const std::string& dict_pth)
	:token_dir_(token_dir)
	,dict_pth_(dict_pth)
	,timestamp_(0)
	,indexer_(NULL)
	,inputQuery("")
	,isNeedIndex(false)
{
	indexer_ = new indexEngine(token_dir_,dict_pth_); //set token path and dictionary path
	isNeedIndex = indexer_->open();//load dictionary to memory
}

recommendEngine::~recommendEngine()
{
	if(NULL != indexer_)
	{
		delete indexer_;
		indexer_ = NULL;
	}
}

void recommendEngine::getCandicate(const std::string& userQuery)
{
	buildEngine();
	if(0 == userQuery.length())
		return;
   termsIdMap = indexer_->search(userQuery,terms2qIDs_,queryIdata_);
   //std::cout <<"tetst--terms2qIDs size:" << terms2qIDs_.size() << "\t queryIdata size:" 
	//   << queryIdata_.size()<< std::endl;
   inputQuery = "";
   jsonResult.clear();
   inputQuery = userQuery;
}

//no results recommendation
void recommendEngine::recommendNoResults()
{
	//no candicate or no terms
	if(0 == terms2qIDs_.size() || 0 == queryIdata_.size() || 0 == termsIdMap.size())
		return;
	std::cout << "tersm id size:" << terms2qIDs_.size() << "\tqueryIdata size:" << queryIdata_.size()
			<< "\t input query terms size:" << termsIdMap.size() << std::endl;
	vector<std::size_t> qTermsID;
	vector<std::size_t> termsID;
	String2IntMapIter termsIter;
	qTermsID.clear();

	//find biggest score
	Terms2QidMapIter termsIdIter;
	bool subset = false;
	bool Not_subset = false;
	float bigScore1 = 0.0;
	float bigScore2 = 0.0;

	std::string res1 = "";
	std::string res2 = "";
	std::string big_term = "";

	for(termsIter = termsIdMap.begin(); termsIter != termsIdMap.end(); ++termsIter)
	{
		if(big_term.length() < termsIter->first.length())
			big_term = termsIter->first;
		termsID.push_back(termsIter->second);
	}

	for(termsIdIter = terms2qIDs_.begin(); termsIdIter != terms2qIDs_.end(); ++termsIdIter)
	{
		//std::cout << "test1-" << termsIdIter->first <<"term query vector size:" << 
		//	termsIdIter->second.size()<<std::endl;
		for(std::size_t i = 0; i < termsIdIter->second.size(); ++i)
		{
			qTermsID = queryIdata_[termsIdIter->second[i]].tid;
			//std::cout << "qTermsID size:" << qTermsID.size() << std::endl;
			float weight = (float) queryIdata_[termsIdIter->second[i]].counts / (
			queryIdata_[termsIdIter->second[i]].hits + (float)0.3*queryIdata_[termsIdIter->second[i]].counts);
			if(Is_subset(termsID,qTermsID))
			{
				subset = true;

				float score = (float) weight * qTermsID.size();
				if(bigScore1 < score)
				{
					bigScore1 = score;  //score
					res1 = queryIdata_[termsIdIter->second[i]].text; // query
					std::cout << "\tsubset score:" << bigScore1 << "\t query:" << res1 << std::endl;
				}
			}
			else
			{
				Not_subset = true;
				std::size_t cnt = 0.0;
				caculateNM(termsID,qTermsID,cnt);
				float tscore = (float) weight * cnt / (qTermsID.size() + 0.1);
				if(bigScore2 < tscore)
				{
					bigScore2 = tscore;
					res2 = queryIdata_[termsIdIter->second[i]].text; //get query 
					std::cout << "Not subset score:" << bigScore2 << "\t query:" << res2 << std::endl;
				}
			}
		}
	}
	
	//get the most similarity query
	std::string ss = "";
	float b_score = 0.0;
	if(subset)
	{
		ss = res1;
		b_score = bigScore1;
	}
	else if(Not_subset)
	{
		ss = res2;
		b_score = bigScore2;
	}
	//check the suggestion
	if(ss.length() <= 3 && b_score !=0)
		ss = big_term;
	std::cout << "input query:" << inputQuery << std::endl;
	if(inputQuery == ss)
		ss = "";
    
	jsonResult["NoResult_Recommend"] = ss;
	std::cout << "the most similar query is :" << ss << "\t biggest score:" << b_score << std::endl;
}

//query correction
void recommendEngine::recommendCorrection()
{
}

//related query recommendation
void recommendEngine::recommend(const std::size_t TopK)
{
	//check
	if(0 == terms2qIDs_.size() || 0 == queryIdata_.size() || 0 == termsIdMap.size())
		return;

	vector<std::size_t> qTermsID;
	vector<std::size_t> termsID;
	map<std::string,float> queryScoreMap;


	qTermsID.clear();
	termsID.clear();
	queryScoreMap.clear();

	Terms2QidMapIter termsIdIter;
	String2IntMapIter termsIter;
	float queryScore = 0.0;
	std::size_t cnt = 0;
	std::string queryText = "";

	for(termsIter = termsIdMap.begin(); termsIter != termsIdMap.end(); ++termsIter)
	{
		termsID.push_back(termsIter->second);
	}
	float weight = 0.0;
	float similar = 0.0;
	//caculate score
	for(termsIdIter = terms2qIDs_.begin(); termsIdIter != terms2qIDs_.end(); ++termsIdIter)
	{
		for(std::size_t j = 0; j < termsIdIter->second.size(); ++j)
		{
			qTermsID = queryIdata_[termsIdIter->second[j]].tid;
			caculateNM(termsID,qTermsID,cnt);

			similar = (float) cnt / (qTermsID.size() + 0.1) ;
			weight = (float)log(queryIdata_[termsIdIter->second[j]].hits + 2.0)/(qTermsID.size() +0.1);
			queryScore = (float) weight * similar;
			queryText = queryIdata_[termsIdIter->second[j]].text;
			queryScoreMap.insert(make_pair(queryText,queryScore));
		//	std::cout << "query:" << queryText <<"\tcontain NM:" << cnt
		//		<<"\tscore:" << queryScore << std::endl;
		}
	}

	//get TopK 
    vector<PAIR> queryScoreVector(queryScoreMap.begin(),queryScoreMap.end());
	sort(queryScoreVector.begin(),queryScoreVector.end(),cmpByValue());
	std::size_t upperBound;
	Json::Value recommend;
	if(TopK < queryScoreVector.size())
		upperBound = TopK;
	else
		upperBound = queryScoreVector.size();
	for(std::size_t i = 0; i < upperBound; ++i)
		recommend.append(queryScoreVector[i].first);
	jsonResult["recommedndation"] = recommend;
}

//build index engine
bool recommendEngine::isNeedBuild()
{
	//check time
	std::time_t mt;
	if(isNeedIndex)
		return true;
	else
	{
		std::cout << "do not need indexing!\n";
		return false;
	}
}

//final recommendation results
void recommendEngine::jsonResults(const std::string& userQuery,std::string& res)
{
	getCandicate(userQuery);
	recommendNoResults();
	recommend();
	res = jsonResult.toStyledString();
}

void recommendEngine::buildEngine()
{
	if(isNeedBuild())
		
	{
		indexer_->indexing("query.txt");
		indexer_->flush();
		isNeedIndex = false;
	}
}


bool Is_subset(vector<std::size_t> v1,vector<std::size_t> v2)
{
	if(0 == v1.size() || 0 == v2.size())
		return false;
	boost::unordered_map<std::size_t,std::size_t> sets;
	sets.clear();
	
	for(std::size_t i = 0; i < v1.size(); ++i)
	{
		sets.insert(make_pair(v1[i],1));
	}
	
	for(std::size_t j = 0; j < v2.size(); ++j)
	{
		if(sets.end() == sets.find(v2[j]))
			return false;
	}
	return true;
}

void caculateNM(vector<std::size_t> v1,vector<std::size_t> v2,std::size_t& cnt)
{
	if(0 == v1.size() || 0 == v2.size())
	{
		cnt = 0;
		return;
	}
	boost::unordered_map<std::size_t,std::size_t> sets;
	sets.clear();
	cnt = 0;
	for(std::size_t i = 0; i < v1.size(); ++i)
		sets.insert(make_pair(v1[i],1));
	for(std::size_t j = 0; j < v2.size(); ++j)
	{
		if(sets.end() != sets.find(v2[j]))
			cnt += 1;
	}
}
