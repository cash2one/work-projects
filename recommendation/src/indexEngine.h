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
#include "normalize.h"

//using in tokenize ,and assign hash value for terms
typedef boost::unordered_map<std::string,std::size_t> String2IntMap;
typedef boost::unordered_map<std::string,std::size_t>::iterator String2IntMapIter;

//
typedef boost::unordered_map<std::size_t,vector<std::size_t> > Terms2QidMap;
typedef boost::unordered_map<std::size_t,vector<std::size_t> >::iterator Terms2QidMapIter;
//structure in corpus
//query text \t hits \t count \t terms id
struct QueryData
{
	std::string text; //qurey text
	std::size_t hits; //searching times
	std::size_t counts; //searching results
	
	vector<std::size_t> tid; //terms hash value
};

typedef boost::unordered_map<std::size_t,QueryData> QueryIdataMap;
typedef boost::unordered_map<std::size_t,QueryData>::iterator QueryIdataIter;

class indexEngine
{

	public:

		indexEngine(const std::string& dir,const std::string& dict_pth);
		~indexEngine();

	public:
		void clear();
		void insert(QueryData& userQuery); //insert an userQuery
		String2IntMap search(const std::string& userQuery,Terms2QidMap& candicateQids
				,QueryIdataMap& candicateQuery);//search query
		void indexing(const std::string& corpus_pth);
		void tokenTerms(const std::string&, String2IntMap&);
		void flush();
		bool open(); //open disk file
		bool isUpdate();


	private:
		Terms2QidMap terms2qIDs_; //terms id ,and it's query id vector
		QueryIdataMap queryIdata_; //query id ,query data
		std::string dir_; //tokenize dictionary path
		std::string dict_pth_;
		ilplib::knlp::HorseTokenize *tok_;

		bool isNeedflush;
};








#endif //indexEngine.h
