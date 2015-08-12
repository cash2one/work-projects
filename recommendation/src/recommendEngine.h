/*************************************************************************
    @ File Name: recommendEngine.h
    @ Method:
    @ Author: Jerry Shi
    @ Mail: jerryshi0110@gmail.com 
    @ Created Time: 2015年07月17日 星期五 15时52分32秒
 ************************************************************************/
#ifndef RECOMMENDENGINE_H
#define RECOMMENDENGINE_H

#include <iostream>
#include <map>

#include "json/json.h"
#include "indexEngine.h"
#include "time.h"
#include "math.h"

typedef pair<std::string,float> PAIR;

// sort  ascending
struct cmpByValue
{
	bool operator()(const PAIR& lhs, const PAIR& rhs)
	{
		return lhs.second > rhs.second;
	}
};

class recommendEngine
{
	public:
		recommendEngine(const std::string& token_dir,const std::string& dict_pth);
		~recommendEngine();

	public:
			void getCandicate(const std::string& userQuery); //get candicate
			void recommendNoResults(); //
			void recommendCorrection();
			void recommend(const std::size_t TopK = 5);
			bool isNeedBuild();
			bool isNeedAdd();
			void jsonResults(const std::string& userQuery,std::string& res);
			void buildEngine();

	private:
			std::string token_dir_;
			std::string workdir_;
			std::size_t timestamp_;

			indexEngine* indexer_;
			Terms2QidMap terms2qIDs_;
			QueryIdataMap queryIdata_;

			bool isNeedIndex;
			String2IntMap termsIdMap; //terms ,it's hash value
			Json::Value jsonResult;
			std::string inputQuery;

			void clear();
};



#endif //recommendEngine.h
