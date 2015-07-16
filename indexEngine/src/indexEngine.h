/*************************************************************************
    @ File Name: indexEngine.h
    @ Method:
	@ Author: Jerry Shi
    @ Mail: jerryshi0110@gmail.com 
    @ Created Time: 2015年07月13日 星期一 10时12分35秒
 ************************************************************************/
#ifndef INDEXENGINE_H
#define INDEXENGINE_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include <boost/unordered_map.hpp>
#include <boost/filesystem.hpp>
#include <util/hashFunction.h>

#include "knlp/horse_tokenize.h"
#include "StringUtil.h"


//structure in corpus
//query text \t hits \t count \t terms id
struct QueryData
{
	std::string text; //qurey text
	std::size_t hits; //searching times
	std::size_t counts; //searching results
	
	vector<uint32_t> tid; //terms hash value
};

class indexEngine
{

	public:

		indexEngine(const std::string& dir);
		~indexEngine();

	public:
		void close();
		void insert(const QueryData& userQuery); //insert an userQuery
		void search(const std::string& userQuery,uint32_t TopK);//search query
		void indexing(const std::string& corpus_pth);
		void flush();
		void open(); //open disk file
		bool isUpdate();


	private:
		boost::unordered_map<uint32_t,vector<uint32_t> > terms2qIDs_;// terms and query id contain thisterm
		boost::unordered_map<uint32_t,QueryData> queryIdata_; //query id ,complete data
		std::string dir_; //tokenize dictionary path
		ilplib::knlp::HorseTokenize *tok_;

		//flush to disk file stream
		ofstream ofTermsId_;
		ofstream ofQueryDat_;
};








#endif //indexEngine.h
