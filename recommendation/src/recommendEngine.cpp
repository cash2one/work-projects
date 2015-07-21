/*************************************************************************
    @ File Name: recommendEngine.cpp
    @ Method: recommend engine,query recommendation,correction,etc.
    @ Author: Jerry Shi
    @ Mail: jerryshi0110@gmail.com 
    @ Created Time: 2015年07月17日 星期五 15时52分57秒
 ************************************************************************/
#include "recommendEngine.h"

bool Is_subset(vector<std::size_t> v1,vector<std::size_t> v2,std::size_t& cnt);


//construct,and initialize
recommendEngine::recommendEngine(const std::string& token_dir,const std::string& dict_pth)
	:token_dir_(token_dir)
	,dict_pth_(dict_pth)
	,timestamp_(0)
	,indexer_(NULL)
	,jsonResult("")
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
   jsonResult = userQuery;
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
	bool subset_flag = false;
	float bigScore1 = 0.0;
	float bigScore2 = 0.0;
	std::string res1 = "";
	std::string res2 = "";
	std::string big_term = "";
	std::size_t cnt = 0;

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
		
			if(Is_subset(termsID,qTermsID,cnt))
			{
				subset_flag = true;
				float score = (float) weight * qTermsID.size();
				if(bigScore1 < score)
				{
					bigScore1 = score;  //score
					res1 = queryIdata_[termsIdIter->second[i]].text; // query
					std::cout << "contain terms NM:" << cnt
						<< "\tsubset score:" << bigScore1 << "\t query:" << res1 << std::endl;
				}
			}
			else
			{
				subset_flag = false;
				float tscore = (float) weight * qTermsID.size();
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
	if(subset_flag)
	{
		ss = res1;
		b_score = bigScore1;
	}
	else
	{
		ss = res2;
		b_score = bigScore2;
	}
	//check the suggestion
	if(ss.length() <= 3 && b_score !=0)
		ss = big_term;
	std::cout << "input query:" << jsonResult << std::endl;
	if(jsonResult == ss)
		ss = "";
	jsonResult = "{\"recommendation\":{\"";
	jsonResult = "noresults\":\"";
	jsonResult += ss;
	jsonResult += "\",\"";
	jsonResult += "recommend\":";
	jsonResult += "\"}";
	
	std::cout << "the most similar query is :" << jsonResult << "\t biggest score:" << b_score << std::endl;
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
	//caculate score
	for(termsIdIter = terms2qIDs_.begin(); termsIdIter != terms2qIDs_.end(); ++termsIdIter)
	{
		for(std::size_t j = 0; j < termsIdIter->second.size(); ++j)
		{
			qTermsID = queryIdata_[termsIdIter->second[j]].tid;
			Is_subset(termsID,qTermsID,cnt);

			float weight = (float) cnt / (qTermsID.size() + 0.1) ;
			queryScore = (float) weight * queryIdata_[termsIdIter->second[j]].hits;
			queryText = queryIdata_[termsIdIter->second[j]].text;
			queryScoreMap.insert(make_pair(queryText,queryScore));
			std::cout << "query:" << queryText << "\tscore:" << queryScore << std::endl;
		}
	}

	//get TopK 
    vector<PAIR> queryScoreVector(queryScoreMap.begin(),queryScoreMap.end());
	sort(queryScoreVector.begin(),queryScoreVector.end(),cmpByValue());
	std::size_t upperBound;
	if(TopK < queryScoreVector.size())
		upperBound = TopK;
	else
		upperBound = queryScoreVector.size();
	for(std::size_t i = 0; i < upperBound; ++i)
		jsonResult += "," + queryScoreVector[i].first;
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
	//recommendNoResults();
	recommend();
	res = jsonResult;
}

void recommendEngine::buildEngine()
{
	if(isNeedBuild())
		indexer_->indexing("query.txt");
}


bool Is_subset(vector<std::size_t> v1,vector<std::size_t> v2,std::size_t& cnt)
{
	boost::unordered_map<std::size_t,std::size_t> sets;
	boost::unordered_map<std::size_t,std::size_t>::iterator setIter;
	sets.clear();
	cnt = 0;
	bool flag = true;
	for(std::size_t i = 0; i < v1.size(); ++i)
	{
		sets.insert(make_pair(v1[i],1));
	}
	
	for(std::size_t j = 0; j < v2.size(); ++j)
	{
		setIter = sets.find(v2[j]);
		if(sets.end() != setIter)
			cnt += 1;
		else
			flag = false;
	}
	return flag;
}
