#include <iostream>
#include <boost/regex.hpp>
#include <string>

using namespace std;
using namespace boost;

int main(int argc, char* argv[]){
  cout << "--input source string" << endl;
  string str;
  getline(cin, str);

  while(true){
    string regex_str;
    cout << "--input regex" << endl;
    getline(cin, regex_str);
    regex delimiter(regex_str);
    
    vector<string> results;
    string s = str; // regex_splitするとソース文字列が破壊されるので
    regex_split(back_inserter(results), s, delimiter);
    cout << str << endl;
    
    for(int i = 0; i < results.size(); i++){
      cout << '"' << results[i] << '"' << endl;
    }
  }
  return 0;
}

/*
    string s="1:2:3";
    string temp;
    boost::regex pat(":");
    list l;
    boost::regex_split(std::back_inserter(l),s,pat);
    while(l.size()){
        s = *(l.begin());
        l.pop_front();
        cout<    }
*/
