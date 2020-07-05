#include <iostream>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>

using namespace std;
using namespace boost;
namespace fs = boost::filesystem;

int main(int argc, char *argv[])
{
//B_chenhui
        string logdirname("./notexistdir");
        boost::filesystem::path logdir(logdirname.c_str());
        boost::filesystem::file_status s = boost::filesystem::status(logdir);
        if( !boost::filesystem::is_directory(s) )
        {
            cout<< "not a directory, mkdir" <<endl;
            if(boost::filesystem::create_directory(logdir))
            {
                cout<<"directory create ok" <<endl;
            }
            else
            {
                cout<<"directory create fail" <<endl;
            }
        }
        else
        {
            cout<<"is a directory" <<endl;
        }
//E_chenhui
  //string pt = argv[1];
  //fs::path path = complete(fs::path(pt, fs::native));
  //int res = fs::create_directory(path);
  //cout << res << endl;
  return 0;
}
