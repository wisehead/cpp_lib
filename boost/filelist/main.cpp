/*******************************************************************************
 *      file name: main.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/07/05-17:54:11                              
 *  modified time: 2020/07/05-17:54:11                              
 *******************************************************************************/
#include <iostream>
#include <boost/filesystem.hpp>
using namespace std;

int main()
{
	string targetPath="/Users/chenhui13/github/cpp_lib/boost";
	boost::filesystem::path myPath(targetPath);
	boost::filesystem::directory_iterator endIter;
	for (boost::filesystem::directory_iterator iter(myPath); iter != endIter; iter++) {
	  if (boost::filesystem::is_directory(*iter)) {
		cout << "is dir" << endl;
		cout << iter->path().string() << endl;
	  } else {
		cout << "is a file" << endl;
		cout << iter->path().string() << endl;
	  }
	}
}
