/*************************************************************************
    @ File Name: t_timestamp.cpp
    @ Method:
    @ Author: Jerry Shi
    @ Mail: jerryshi0110@gmail.com 
    @ Created Time: 2015年07月24日 星期五 10时03分32秒
 ************************************************************************/
#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <boost/filesystem.hpp>


using namespace std;

int main()
{

	cout << "Simulate data update mechanism...\n";
	string dir = "../../resource";
	string timefile = ".RecommendEngineTimestamp";
	std::size_t timestamp_ = 0;
	if(!boost::filesystem::exists(dir))
	{
		boost::filesystem::create_directory(dir);
	}
	else
		cout << "source directory exists!\n";

	string path = dir;
	path += "/";
	path += timefile;

	ifstream in;
	in.open(path.c_str(),std::ifstream::in);
	if(in)
		in >> timestamp_;
	in.close();
	cout << "last time is:" << timestamp_ << endl;

	//is need build
	string newdata = dir + "/" + "newdata.txt";

	boost::filesystem::directory_iterator end;
//	for(boost::filesystem::directory_iterator it(dir); it != end; ++it)
//	{
	//	const string p = it->path().string();
	const string p = newdata;
		if(boost::filesystem::is_regular_file(p))
		{
	std::time_t mt = boost::filesystem::last_write_time(p);
	if(mt > timestamp_)
	{
		cout << "files has been changed ,need index again!\n";
		cout << "last write time is :" << mt << endl;
	}
	}
	//}
	std::time_t mmt = time(NULL);
	if(mmt - timestamp_ > 100)
		cout << "times interval has already over 100 seconds!\n";



}

