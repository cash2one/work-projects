/*************************************************************************
    @ File Name: t_StringUtil.cpp
    @ Method:
    @ Author: Jerry Shi
    @ Mail: jerryshi0110@gmail.com 
    @ Created Time: 2015年07月14日 星期二 14时01分50秒
 ************************************************************************/
#include <iostream>
#include <algorithm>

#include <boost/test/unit_test.hpp>

#include "../StringUtil.h"

#define BOOST_TEST_MODULE FreqString test

BOOST_AUTO_TEST_CASE(Construct1_test)
{
	FreqString fstr;
	BOOST_CHECK_EQUAL(fstr.getString(),"");
	
	BOOST_CHECK_EQUAL(fstr.getFreq(),0.0);
	
	BOOST_CHECK_EQUAL(fstr.getPosition(),(size_t)0);
}

