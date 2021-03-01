/*******************************************************************************
 *      File Name: main.cpp                                               
 *         Author: Hui Chen. (c) 2015                             
 *           Mail: chenhui13@baidu.com                                        
 *   Created Time: 2015/07/31-15:39                                    
 *	Modified Time: 2015/07/31-15:39                                    
 *******************************************************************************/
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <fnmatch.h>
#include <map> 
#include "./parser.h"
using namespace std;
const char filename[] = "a.in";
const char table_def_file[] = "TableDef.txt";
//------------------------------------------------------------------------------
int UDT_BOOL::parse(string str)
{
    if (!str.compare("TRUE"))
    {
        value = true;
        printf("UDT_BOOL: %d; ",value);
        return 0;
    }
    else if (!str.compare("FALSE"))
    {
        value = false;
        printf("UDT_BOOL: %d; ",value);
        return 0;
    }
    else
        return -1;
}

int UDT_USER::parse(string str)
{
    //cout<<"in UDT_USER::parse()!!"<<endl;
    unsigned int start=0;
    unsigned int loc = 0;
    int i=0;
    char tab = ',';
    std::vector<string> fields; 
    fields.empty();
    int col_count = 4;
    for (;i<col_count;i++)
    {
        if (i==col_count-1)
            loc = str.length();
        else
            loc = str.find(tab, start );
        if( loc != string::npos )
        {
            string temp = str.substr(start,loc-start);
            fields.push_back(temp);
            //cout <<start<<" "<<loc<<" Found sub string " << fields[i] << endl;
            start = loc + 1;
            while(str.c_str()[start]==' ')
            {
                start++;
            }
        }
        else
        {
            cout << "UDT_USER::parse(): Didn't find sub string." << endl;
            return -1;
        }     
        cout<<endl;
    }
    userId = atoi(fields[0].c_str());
    int len_name = fields[1].length();
    //cout<<"len_name is:"<<len_name<<endl;
    name = new char[len_name + 1];
    memset( name, 0, len_name+1 );
    fields[1].copy( name, len_name );
    age = atoi(fields[2].c_str());
    money = atof(fields[3].c_str());
    printf("userId is:%d; name is:%s; age is:%d; money is:%f\n",userId,name,age,money);
    if (name != NULL)
    {
        delete [] name;
        name = NULL;
    }
    return 0;
}

int BUILT_IN_INT::parse(string column)
{
    int value = atoi(column.c_str());
    printf("int: %d; ",value);
    return 0;
}

int BUILT_IN_FLOAT::parse(string column)
{
    value = atof(column.c_str());
    printf("float: %f; ",value);
    return 0;
}

int BUILT_IN_CHAR_STRING::parse(string column)
{
    int len_name = column.length();
    //cout<<"len_name is:"<<len_name<<endl;
    value = new char[len_name + 1];
    memset( value, 0, len_name+1 );
    column.copy( value, len_name );
    printf("string: %s; ",value);
    // each time when we exit this funcion, free the memory
    if (value)
    {
        delete [] value;
        value = NULL;
    }
    return 0;
}

//------------------------------------------------------------------------------
Base_Type* Handler::get_handler(string type)
{
    map<string, Base_Type*>::iterator it = ha_map.find(type); 
    if( it != ha_map.end() )
        return it->second; 
    return NULL;
}

bool Handler::is_this_type_supported(string type)
{
    map<string, Base_Type*>::iterator it = ha_map.find(type); 
    if( it != ha_map.end() )
        return true; 
    return false;
}

//------------------------------------------------------------------------------
int TableDef::init()
{
    ifstream in(table_def_file);
    cout<<"TABLE DEFINITION:"<<endl;
    cout<<"------------------------------"<<endl;
    for (string str; getline(in, str); )
    {
        cout<<str<<endl;
        columns.push_back(str);
    }
    cout<<"------------------------------"<<endl;
    return 0;
}

int TableDef::getColCount()
{
    return columns.size();
}

int TableDef::check_and_get_array_def(string arr_str, string* ele_type, int* ele_count)
{
    unsigned int start = 0;
    unsigned int left_loc = 0;
    unsigned int right_loc = 0;
    char left_bracket = '[';
    char right_bracket = ']';
    string sub;
    left_loc = arr_str.find(left_bracket, start );
    right_loc = arr_str.find(right_bracket, start );
    sub = arr_str.substr(left_loc+1,right_loc - left_loc -1);
    int temp_count = atol(sub.c_str());
    if (temp_count <= 0)
    {
        printf("The array num is invalid!!\n");
        return -1;
    }
    string temp_type = arr_str.substr(0,left_loc);
    if (!Handler::GetInstance()->is_this_type_supported(temp_type))
    {
        cout<<"Invalid Data Type!!"<<endl;
        return -1;
    }

    if (ele_type != NULL)
        *ele_type = temp_type;
    if (ele_count != NULL)
        *ele_count = temp_count;
    return 0;
}

string TableDef::get_type(int i)
{
    string empty("");
    if (i<0 || i> getColCount())
        return empty;
    string type = columns[i];
    if (Handler::GetInstance()->is_this_type_supported(type))
        return columns[i];
    // this column is arrary, we need to check the definition format first
    int ret = fnmatch("*\\[*\\]", type.c_str(), FNM_PATHNAME|FNM_PERIOD);
    if(0 != ret){
        cout<<"TableDef::get_type(): Invalid Data Type!!"<<endl;
        return empty;
    }

    ret = check_and_get_array_def(type, NULL, NULL);
    if (ret != 0)
        return empty;
    return columns[i];
}
//------------------------------------------------------------------------------
TableDef& Parser::get_table_def()
{
    return table_def;    
}
/*
   arr_str looks like this:
num:item1,item2,item3
*/
int Parser::parse_array(string def, string arr_str)
{
    string type;
    int ele_count = 0;
    if (get_table_def().check_and_get_array_def(def,&type,&ele_count))
    {
        cout<<"Parser::parse_array(): get array def failed."<<endl;
        return -1;
    }
    unsigned int start=0;
    unsigned int loc = 0;
    //find ':'
    char tab = ':';
    loc = arr_str.find(tab, start );
    if ( loc == string::npos )
    {
        cout<<"Parser::parse_array(): can't find sub string."<<endl;
        return -1;
    }
    start = loc + 1;
    // array looks like this: 
    // item1,item2,item3
    string  array = arr_str.substr(start);
    tab = ',';
    if (parse_low(array, tab, ele_count, type))
        return -1;
    return 0;
}

int Parser::parse_low(string line, char tab, int ele_count, string type)
{
    if (ele_count <= 0)
    {
        cout<<"Parser::parse_low(): ele_count is invalid."<<endl;
        return -1;
    }
    bool type_is_null = false;
    unsigned int start=0;
    unsigned int loc = 0;
    int i=0;
    if (type.empty())
    {
        type_is_null = true;    
    }
    for (;i<ele_count;i++)
    {
        if (i==ele_count-1)
            loc = line.length();
        else
            loc = line.find(tab, start );
        if( loc != string::npos )
        {
            string sub = line.substr(start,loc-start);
            //cout <<start<<" "<<loc<<" Found sub string " << sub << endl;
            start = loc + 1;
            while(line.c_str()[start]==' ')
            {
                start++;
            }
            if (type_is_null)
            {
                type = get_table_def().get_type(i);
            }
            if (Handler::GetInstance()->is_this_type_supported(type))
            {
                Base_Type* handler = Handler::GetInstance()->get_handler(type);
                if (handler==NULL)
                    cout<<"NULL------------------"<<endl;
                if (handler)
                {
                    int ret = handler->parse(sub);
                    if (ret != 0)
                    {
                        cout <<"Parser::parse_low(): got error in parse."<<endl;
                        return -1;
                    }
                }
            }
            else//array
            {
                if (parse_array(type,sub))
                    return -1;
            }
        }
        else
        {
            cout << "Parser::parse_low(): Didn't find sub string." << endl;
            return -1;
        }     
        cout<<endl;
    }
    return 0;
}

int Parser::parse_line(string line)
{
    int  col_count = get_table_def().getColCount();
    char tab = ' ';
    return parse_low(line, tab, col_count);
}
//------------------------------------------------------------------------------
int main(){
    Parser parser;
    parser.get_table_def().init();
    ifstream in(filename);
    for (string line; getline(in, line); )
    {
        cout<<line<<endl;
        if (parser.parse_line(line) )
        {
            cout<<"main(): get error from parse_line."<<endl;
            return -1;
        }
    }

}
//-------------------------------------------------------------------------------

