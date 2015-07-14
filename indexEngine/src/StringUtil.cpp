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
			isReplicate = true;
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
		for(std::size_t i = 1; i < fstrs.size(); ++i)
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

//resize the string vector
void resize(FreqStringVector& strs)
{
	std::size_t j = 0;
	for(std::size_t i = 0;i < strs.size(); ++i)
	{
		if(!strs[i].isRemoved())
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

//caculate blank number
int nBlank(const std::string& str)
{
	const char* pos = str.c_str();
	std::size_t n = 0;
	for(std::size_t i = 0;i < str.size();++i,pos++)
	{
		if(' ' == *pos)
			n++;
	}
	return n;
}

//give a string find it's id,but haven't been used temporary!!
int strToInt(const std::string& str,boost::bimap<int,std::string>& bm)
{
}

//give an int(id) find it's string,but haven't been used temporary!!
std::string intToStr(int n, boost::bimap<int,std::string>& bm)
{
}

//check the input wheather a english string
bool isEnglish(const std::string& userQuery)
{
	const char* pos = userQuery.c_str();
	bool ret = true;
	for(std::size_t i = 0;i < userQuery.size();++i,pos++)
	{
		if(isblank(*pos) || isalpha(*pos))
			continue;
		else
		{
			ret = false;
			break;
		}
	}
	return ret;
}

//remove space in src
void removeSpace(const std::string& src,std::string& tar)
{
	for(std::size_t i = 0; i < src.size();++i)
	{
		if(!isspace(src[i]))
			tar += src[i];
	}
}

//find the max feqstring class object,
FreqString max(FreqStringVector& v)
{
	FreqString max("",0);
	for(std::size_t i = 0;i < v.size();++i)
	{
		if(max < v[i])
			max = v[i];
	}
	return max;
}

int editDistance(const std::string& sstr,const std::string& tstr)
{
	int n = sstr.length();
	int m = tstr.length();
	
	if(0 == n) return m;
	if(0 == m) return n;

	typedef std::vector<std::vector<int> > Tmatrix;
	Tmatrix matrix(n+1);

	//initial the matrix (n+1)*(m+1)
	for(int i = 0; i <= n; ++i) matrix[i].resize(m+1);
	for(int i = 1; i <= n; ++i) matrix[i][0] = i;
	for(int i = 1; i <= m; ++i) matrix[0][i] = i;

	//caculate
	for(int i = 1; i <= n; ++i)
	{
		const char si = sstr[i-1];
		int cost; //penalty
		for(int j = 1; j <= m; ++j)
		{
			const char tj = tstr[j-1];
			if(si == tj)
			{
				cost = 0;
			}
			else
			{
				cost = 1; 
			}
			const int above = matrix[i-1][j] + 1; //above (i,j)
			const int left = matrix[i][j-1] + 1; //lesf (i.j)
			const int diag = matrix[i-1][j-1] + cost; //diagonal elements
			matrix[i][j] = std::min(above,std::min(left,diag));
		}
	}
	if(isEnglish(sstr) && isEnglish(tstr))
		return matrix[n][m];
	else
		return matrix[n][m] / 3;
}

//sorted by edit distance
void tuneByEditDistance(FreqStringVector& vector,const std::string& str)
{
}
