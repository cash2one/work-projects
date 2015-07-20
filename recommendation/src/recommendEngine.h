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

#include "indexEngine.h"
#include "time.h"

class recommendEngine
{
	public:
		recommendEngine(const std::string& token_dir,const std::string& dict_pth);
		~recommendEngine();

	public:
			void getCandicate(const std::string& userQuery); //get candicate
			void recommendNoResults(); //
			void recommendCorrection();
			void recommend();
			bool isNeedBuild();
			void jsonResults(const std::string& userQuery,std::string& res);
			void buildEngine();

	private:
			std::string token_dir_;
			std::string dict_pth_;
			std::size_t timestamp_;

			indexEngine* indexer_;
			Terms2QidMap terms2qIDs_;
			QueryIdataMap queryIdata_;

			bool isNeedIndex;
			String2IntMap termsIdMap; //terms ,it's hash value
			std::string jsonResult;

};



#endif //recommendEngine.h
