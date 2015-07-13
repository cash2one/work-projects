/*************************************************************************
    @ File Name: StingUtil.h
	@ Method: normalize the string(query),remove duplicate,catulate edit distance,etc
    @ Author: Jerry Shi
    @ Mail: jerryshi0110@gmail.com 
    @ Created Time: 2015年07月13日 星期一 10时33分54秒
 ************************************************************************/
#ifndef STRINGUTIL_H
#define STRINGUTIL_H


#include <boost/algorithm/string.hpp>
#include <boost/functional/hash.hpp>
#include <vector>
#include <limits>

#include <boost/bimap.hpp>

typedef std::vector<std::sting> StringVector;

//string with frequence
class FreqString
{
	public:
		//construct1
		FreqString()
			:str_(""),freq_(0.0),pos_(0)
		{
		}

		//construct2
		FreqString(const std::string &str,float freq)
			:str_(str),freq_(freq),pos_(0)
		{
		}

		//construct3
		FreqString(const std::string &str,float freq,std::size_t pos)
			:str_(str).freq_(freq),pos_(pos)
		{
		}
		
		//constuct4
		FreqString(const FreqString& fstr)
		{
			str_ = fstr.str_;
			freq_ = fstr.freq_;
			pos_ = fstr.pos_;
		}	

	public:
		//get/set memeber variables
		void setString(const std::string& str)
		{
			str_ = str;
		}

		const std::string& getString() const
		{
			return str_;
		}

		//freq -set
		void setFreq(float freq)
		{
			freq_ = freq;
		}

		//freq -get
		float getFreq() const
		{
			return freq_;
		}

		//pos -set
		void setPosition(std::size_t pos)
		{
			pos_ = pos;
		}

		//pos -get
		std::size_t getPosition() const
		{
			return pos_;
		}

		//overload operator "=,<"
		FreqString& operator=(const FreqString& fstr)
		{
			str_ = fstr.str_;
			freq_ = fstr.freq_;
			pos_ = fstr.pos;

			return *this;
		}

		//remove string by it's npos
		void remove()
		{
			pos_ = std::numeric_limits<std::size_t>::max();
		}

		//set this pos to npos
		bool isRemoved() const
		{
			return pos_ = std::numeric_limits<std::size_t>::max();
		}

		//compare by frequency
		friend bool operator<(const FreqString& lstr,const FreqString& rstr)
		{
			return lstr.freq_ < rstr.freq_;
		}
       
		//compare by string
		static bool nameComparator(const FreqString& lstr,const FreqString& rstr )
		{
			return lstr.str_ > rstr.str_;
		}
	private:
		std::string str_;
	    float freq_;
		std::size_t pos_;	
};//FreqString class

//helpful functions
typedef std::vector<FreqString> FreqStringVector; //string with frequency
typedef boost::hash<const std::string> HashFunc;

std::string& normalize(std::string& str);
void removeDuplicate(StringVector& strs); // vector<string>
void removeDuplicate(FreqStringVector& strs,bool keepOrder = true);
void removeItem(FreqStringVector& strs,const std::string& str);
void resize(FreqStringVector& strs);

int nBlank(const std::string& str); //numbers of blank in string
//s_str: source string,t_str: target string
int editDistance(const std::string& sstr,const std::string& tsrt);

int strToInt(const std::string&str,boost::bimap<int,std::string>& bm);
std::string intToStr(int n,boost::bimap<int,std::string>& bm);

//tune by edit distance(caculate by str between every terms in vector)
void tuneByEditDistance(FreqStringVector& vector,const std::string& str);

bool isEnglish(const std::string& usrQuery);

void removeSpace(const std::string& src,std::string& tar);

FreqString max(FreqStringVector& v);



#endif //StringUtil.h

