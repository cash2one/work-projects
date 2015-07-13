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
		//default construct
		FreqString()
			:str()


	private:
		std::string str_;
	    float freq_;
		std::size_t pos_;	

};



#endif //StringUtil.h

