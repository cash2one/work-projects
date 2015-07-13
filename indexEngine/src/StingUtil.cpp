/*************************************************************************
    @ File Name: StingUtil.cpp
    @ Method:
    @ Author: Jerry Shi
    @ Mail: jerryshi0110@gmail.com 
    @ Created Time: 2015年07月13日 星期一 13时51分25秒
 ************************************************************************/
#include <iostream>
#include "StringUtil.h"

std::string& normalize(std::string& str)
{
	boost::trim(str);
	const char* pos = str.c_str();
	std::size_t size = str.size();
	std::size_t lastPos = 0;
	std::string nstr = "";
	for(std::size_t i = 0;i < size ; ++i)
	{
		if(' ' == pos[i])
		{
			nstr += std::string(pos + lastPos,i - lastPos);
			nstr += " ";
			for(;i < size;++i)
			{
				if((i +1 < size) && (pos[i+1] != ' ') )
					break;
			}
			lastPos = i +1;
		}
	}
	nstr += std::string(pos + lastPos);
   str = nstr;
   boost::trim(str);
   boost::to_lower(str);

   return str;   
}

//remove dedup string in strs-vector
void removeDuplicate(StringVector& strs)
{
	if(1 >= strs.size())
		return;
	StringVector sstrs = strs; //dedup by sort
	std::sort(sstrs.begin(),sstrs.end());
	std::string rstr = ""; //result of temp
	bool isReplicate = false; //flag 
	for(std::size_t i = 0;i < sstrs.size() - 1;++i)
	{
		if(sstrs[i] == sstrs[i+1])
		{
			rstr = sstrs[i];
			isPeplicate = true;
		}
		else
		{
			bool isFirst = true;
			for(std::size_t ii = 0;ii< strs.size();++ii)
			{
				if(rstr == strs[i])
				{
					if(isFirst)
					{
						isFirst = false;
					}
					else
					{
						strs.erase(strs.begin() + ii);
						ii--;
					}
				}
			}
			isReplicate = false;
		}
	}
}

void removeDuplicate(FreqStringVector& fstrs,bool keepOrder)
{
	if(1 >= fstrs.size())
		return;
	if(!keepOrder)
	{
		std::sort(fstrs.begin(),fstrs.end(),FreqString::nameComparator);
		//find dedup,
		for(std::size_t i = 1; i < fstrs; ++i)
		{
			if(fstrs[i-1].getString() == fstrs[i].getString())
			{
				//fstrs[i-1].setFreq(fstrs[i-1].getFreq() + fstrs[i].getFreq());
				fstrs[i].remove();
			}
		}

		//remove dedup
		std::size_t j = 0;
		for(std::size_t i = 0; i < fstrs.size();++i)
		{
			if(!fstrs[i].isRemoved())
			{
				if (i == j)
					j++;
				else
				{
					fstrs[j] = fstrs[i];
					j++;
					fstrs[i].remove();
				}
			}
		}
		fstrs.resize(j);
		return;
	}
    
	//keep order dedup
	for(std::size_t i = 0;i < fstrs.size(); ++i)
	{
		//not delete
		if(!fstrs[i].isRemoved())
			continue;
		for(std::size_t j = 0;j < fstrs.size(); ++j)
		{
			if(!fstrs[j].isRemoved())
				continue;
			if(fstrs[i].getString() == fstrs[j].getString())
			{
				//fstrs[i].setFreq(fstrs[i].getFreq() + fstrs[j].getFreq());
				//fstrs[j].remove();
				//choose the string with bigger frequency
				if(fstrs[i].getFreq() >= fstrs[j].getFreq())
					fstrs[j].remove();
				else
					fstrs[i].remove();
			}
		}
	}
	resize(fstrs);
}


void removeItem(FreqStringVector& strs,const std::string& str)
{
	for(std::size_t i = 0; i < strs.size(); ++i)
	{
		std::string pstr = strs[i].getString();
		bool remove = true;
		for(std::size_t j = 0; j < pstr.size();++j)
		{
			//check space
			if(isspace(pstr[j]))
				continue;
			else
			{
				if(std::string::npos == str.find(pstr[j]))
				{
					remove = false;
					break;
				}
			}
		}
		if(remove)
			strs[i].remove();
	}
	resize(strs);
}

void resize(FreqStringVector& strs)
{
	std::size_t j = 0;
	for(std::size_t i = 0;i < strs.size(); ++i)
	{
		if(!strs.isRemoved())
		{
			if( i == j)
				j++;
			else
			{
				strs[j] = strs[i];
				j++;
				strs[i].remove();
			}
		}
	}
	strs.resize(j);
}

int nBlank(const std::string& str)
{
}

int strToInt(const std::string& str,boost::bimap<int,std::string>& bm)
{
}

std::string intToStr(int n, boost::bimap<int,std::string>& bm)
{
}

bool isEnglish(const std::string& usrQuery)
{
}

void removeSpace(const std::string& src,const std::string& tar)
{
}

FreqString max(FreqStringVector& v)
{
}

int editDistance(const std::string& sstr,const std::string& tstr)
{
}

void tuneByEditDistance(FreqStringVector& vector,const std::string& str)
{
}
