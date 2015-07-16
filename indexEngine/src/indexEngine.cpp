/*************************************************************************
    @ File Name: indexEngine.cpp
    @ Method:
    @ Author: Jerry Shi
    @ Mail: jerryshi0110@gmail.com 
    @ Created Time: 2015年07月13日 星期一 13时51分14秒
 ************************************************************************/
#include "indexEngine.h"

//construct
indexEngine::indexEngine(const std::string& dir)
	:dir_(dir)
{
	if(!boost::filesystem::exists(dir_))
	{
		std::cerr << "Tokenize dictionary path not exits!" << std::endl;
	}

	//tokenizer
	tok_ = new ilplib::knlp::HorseTokenize(dir_);

	std::string termId_pth =  "../termId.v";
	std::string queryDat_pth = "../queryDat.v";

	ofTermsId_.open(termId_pth.c_str(),ios::app);
	if(!ofTermsId_.is_open())
		std::cerr << "Open termId dictionary failed!" << std::endl;
	ofQueryDat_.open(queryDat_pth.c_str(),ios::app);
	if(!ofQueryDat_.is_open())
		std::cerr << "Open queryDat dictionary failed!" << std::endl;
}

indexEngine::~indexEngine()
{
	if(tok_)
		delete tok_;
}

void indexEngine::insert(const QueryData& userQuery)
{
}

void indexEngine::search(const std::string& userQuery,uint32_t Topk)
{
}

void indexEngine::indexing(const std::string& corpus_pth)
{
	ifstream ifOrigin_data; //file stream to load data from corpus
	ifOrigin_data.open(corpus_pth.c_str());
	if(!ifOrigin_data.is_open())
		std::cerr << "Open corpus files failed!" << std::endl;

	std::string sLine = "";
	std::string sData = "";
	vector<string> splitDat;
	

	while(getline(ifOrigin_data,sLine))
	{
		splitDat.clear();

		//get detail data from original corpus
		for(unsigned int i = 0; i < 3; ++i)
		{
			std::size_t pos = sLine.find('\t');
			if(std::string::npos != pos)
			{
				sData = sLine.substr(0,pos);
				sLine.assign(sLine,pos+1,sLine.length()-1);
				splitDat.push_back(sData);
			}
		}
		splitDat.push_back(sLine);

		//check data
		if(4 != splitDat.size())
			continue;
		QueryData qDat;
		qDat.text = splitDat[0]; //query text
		qDat.hits = atoi(splitDat[2].c_str()); //query times
		qDat.counts = atoi(splitDat[3].c_str());//results numbers

		//get term id
		vector<pair<string,float> > segTerms;
		segTerms.clear();
		try
		{
			tok_->tokenize(qDat.text,segTerms);
		}
		catch(...)
		{
			segTerms.clear();
		}

		std::size_t queryID = izenelib::util::izene_hashing(qDat.text);
		boost::unordered_map<std::string,unsigned int> termsVector;
		boost::unordered_map<std::string,unsigned int>::iterator termsIter;
		//dedup terms
		for(std::size_t i = 0; i < segTerms.size(); ++i)
		{
			termsIter = termsVector.find(segTerms[i].first);
			if(termsVector.end() == termsIter) //not found
			{
				termsVector.insert(make_pair(segTerms[i].first,queryID)); //insert terms ,it's query ID
				std::cout << "Terms:" << segTerms[i].first << "\tquery ID:" << queryID << std::endl;
			}
		}

		vector<uint32_t> queryIdVector;
		boost::unordered_map<uint32_t,vector<uint32_t> >::iterator termsQueryIter;
		//assign hash id for every terms
		for(termsIter = termsVector.begin(); termsIter != termsVector.end(); ++termsIter)
		{
			queryIdVector.clear();
			std::size_t termsID = izenelib::util::izene_hashing(termsIter->first);
			//termsIdVector.push_back(termsID);
			queryIdVector.push_back(queryID);
			//find terms in dictornary,termsID.v
			termsQueryIter = terms2qIDs_.find(termsID);
			if(termsQueryIter != terms2qIDs_.end())
			{
				termsQueryIter->second.push_back(termsIter->second); 
			}
			else
			{
				//queryIdVector.push_back(termsIter->second); //query id
				terms2qIDs_.insert(make_pair(termsID,queryIdVector));
			}
		}

		//complete data for one query
		qDat.tid = queryIdVector;
		/*
		 //flush to disk file
		 ofQueryDat_ << queryID << "\t" << qDat.hits << "\t" << qDat.counts;
		 for(unsigned int i = 0; i < qDat.tid.size(); ++i)
		 {
			ofQueryDat_ << "\t" << qDat.tid[i];
			//cout << "terms id :" << qDat.tid[i] << ",";
		 }
		 ofQueryDat_ << std::endl;
		*/ 
		queryIdata_.insert(make_pair(queryID,qDat));
	}
	ifOrigin_data.close();//file stream close
}

void indexEngine::open()
{
}

void indexEngine::flush()
{
	//flush query data to disk,queryDat.v
	boost::unordered_map<uint32_t,QueryData>::iterator queryIter;
	for(queryIter = queryIdata_.begin(); queryIter != queryIdata_.end(); ++queryIter)
	{
		ofQueryDat_ << queryIter->first << "\t" << queryIter->second.text << "\t"
			        << queryIter->second.hits << "\t" << queryIter->second.counts;
		for(unsigned int i = 0; i < queryIter->second.tid.size(); ++i)
		{
			ofQueryDat_ << "\t" << queryIter->second.tid[i];
		}
		ofQueryDat_ << std::endl;
	}


	//flush terms id,candicate query id to disk,termsId.v
	boost::unordered_map<uint32_t,vector<uint32_t> >::iterator termsQueryIter;
	for(termsQueryIter = terms2qIDs_.begin(); termsQueryIter != terms2qIDs_.end(); ++termsQueryIter)
	{
		std::cout << "Terms:" << termsQueryIter->first << std::endl;
		std::cout << "\tQuery id:" << std::endl;
		ofTermsId_ << termsQueryIter->first << "\t";
		for(unsigned int i = 0; i < termsQueryIter->second.size(); ++i)
		{
			std::cout << termsQueryIter->second[i] << ",";
			ofTermsId_ << termsQueryIter->second[i] << "\t";
		}
		std::cout << std::endl;
		ofTermsId_ << std::endl;
	}
}

void indexEngine::close()
{
	tok_ = NULL;

	ofQueryDat_.close();
	ofTermsId_.close();
}

bool indexEngine::isUpdate()
{
}

