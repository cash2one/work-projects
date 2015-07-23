/*************************************************************************
    @ File Name: NString.hpp
    @ Method:string normalize class,include lower/upper,unicode <--> utf8,etc.
    @ Author: Jerry Shi
    @ Mail: jerryshi0110@gmail.com 
    @ Created Time: 2015年07月23日 星期四 13时48分01秒
 ************************************************************************/
#ifndef NSTRING_HPP
#define NSTRING_HPP


#include <iostream>
#include <string>
#include <vector>

#include <cstdio>
#include <cstdlib>
#include <cerrno>


class NString
{
	private:
		char* str;
		std::size_t length;

	public:

		NString(const std::string& inStr)
			:str(inStr.c_str())
		{
		}
		~NString()
		{
		}

		void to_lower_case()
		{
		}

		void to_upper_case()
		{
		}
};




#endif //NString.hpp
