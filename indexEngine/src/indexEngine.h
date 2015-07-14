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

#include <boost/unoreder_map.hpp>
#include <util/hashFunction.h>

#include "knlp/horse_tokenize.h"

//structure in corpus
//query text \t hits \t count \t terms id
struct QueryData
{
	std::string text; //qurey text
	std::size_t hits; //searching times
	std::size_t counts: //searching results
	
	std::vector<uint32_t> tid; //terms hash value
};

class indexEngine
{

	public:

		indexEngine(const std::string& dir);
		~indexEngine();

	public:
		void init(); //initial index engine,open 
		void insert(const QueryData& userQuery); //insert an userQuery
		void search();//search query
		void indexing();
		void flush();
		void open(); //open disk file
		bool isUpdate();


	private:
		boost::unorder_map<unsigned int,vector<unsigned int> > Terms2Qid_;// terms and query id contain thisterm
		boost::unorder_map<unsigned int,QueryData> flush2Disk_;
		std::string dir_; //tokenize dictionary path
		ilplib::knlp::HorseTokenize *tok_;

}；








#endif //indexEngine.h
