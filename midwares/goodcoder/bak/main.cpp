/*******************************************************************************
 *      File Name: main.cpp                                               
 *         Author: Hui Chen. (c) 2015                             
 *           Mail: chenhui13@baidu.com                                        
 *   Created Time: 2015/07/31-15:39                                    
 *	Modified Time: 2015/07/31-15:39                                    
 *******************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <fnmatch.h>
#include <map> 
using namespace std;
const char filename[] = "a.in";
const char tableDefFile[] = "TableDef.txt";
/*
char type_arr[][20] = { 
    {"int"},
    {"float"},
    {"char*"},
    {"UDT_BOOL"},
    {"UDT_USER"}
};  

bool is_this_type_supported(string type)
{
    bool ret = false;
    static int type_arr_size = sizeof(type_arr) / sizeof(type_arr[0]);
    for (int i=0; i< type_arr_size; i++)
    {
        ret = ret || !type.compare(type_arr[i]);
        if (ret)
            return ret;
    }
    return ret;
}
*/
//------------------------------------------------------------------------------
class Base_Type 
{
    public:
        virtual int parse(string str)
        {
            printf("in parse() of Base Class\n");
        }
};
/*
   Base Class of User Defined Type, if you want to define a new UDT, please implement
   the function parse(), and add your UDT name to the array type_arr.

   if you want to add a new User Defined Type, you need to
       1.inherit from UDT;
       2.implement interface parse();
       3.add the name of the new type to array type_arr;
       4.add a member of the new Type to class Parser, and add it to the ha_map in constuctor function;
   */
class UDT: public Base_Type
{
    public:
        virtual int parse(string str)
        {
            printf("in parse() of base UDT\n");
        }
};

class UDT_BOOL:public UDT
{
    public:
        virtual int parse(string str);
    private:
        bool value;
};

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

class UDT_USER:public UDT
{
    public:
        UDT_USER()
        {
            name = NULL;    
        }
        ~UDT_USER()
        {
            if (name != NULL)
            {
                delete [] name;
                name = NULL;
            }
        }
        virtual int parse(string str);
    private:
        int userId;
        char* name;
        int age;
        float money;
};

int UDT_USER::parse(string str)
{
    cout<<"in UDT_USER::parse()!!"<<endl;
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
            cout <<start<<" "<<loc<<" Found sub string " << fields[i] << endl;
            start = loc + 1;
            while(str.c_str()[start]==' ')
            {
                start++;
            }
        }
        else
        {
            cout << "Didn't find sub" << endl;
        }     
        cout<<endl;
    }
    userId = atoi(fields[0].c_str());
    int len_name = fields[1].length();
    cout<<"len_name is:"<<len_name<<endl;
    name = new char[len_name + 1];
    memset( name, 0, len_name+1 );
    //memcpy (fields[1].c_str()dd);
    fields[1].copy( name, len_name );
    age = atoi(fields[2].c_str());
    money = atof(fields[3].c_str());
    printf("userId is:%d; name is:%s; age is:%d; money is:%f\n",userId,name,age,money);
}

class BUILT_IN_INT:public Base_Type 
{
    public:
        virtual int parse(string str);
    private:
        int value;
};

class BUILT_IN_FLOAT:public Base_Type
{
    public:
        virtual int parse(string str);
    private:
        float value;
};
class BUILT_IN_CHAR_STRING:public Base_Type 
{
    public:
        virtual int parse(string str);
    private:
        char* value;
};
int BUILT_IN_INT::parse(string column)
{
    int value = atoi(column.c_str());
    printf("int: %d; ",value);
}

int BUILT_IN_FLOAT::parse(string column)
{
    value = atof(column.c_str());
    printf("float: %f; ",value);
}

int BUILT_IN_CHAR_STRING::parse(string column)
{
    printf("string: %s; ",column.c_str());
}
//------------------------------------------------------------------------------

class TableDef
{
    public:
        TableDef()
        {
            columns.empty();
        }
        ~TableDef()
        {
        }

        int getTableDef();
        int getColCount();
        string get_type(int i);
        int process_array_def(string arr_str, string* ele_type, int* ele_count);
    private:
        std::vector<string> columns; 
};

int TableDef::getTableDef()
{
    ifstream in(tableDefFile);
    cout<<"TABLE DEFINITION:"<<endl;
    cout<<"------------------------------"<<endl;
    for (string str; getline(in, str); )
    {
        cout<<str<<endl;
        columns.push_back(str);
    }
    cout<<"------------------------------"<<endl;
}
int TableDef::getColCount()
{
    return columns.size();
}

int TableDef::process_array_def(string arr_str, string* ele_type, int* ele_count)
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
    if (!Parser::is_this_type_supported(temp_type))
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
    string type = columns[i];
    if (Parser::is_this_type_supported(type))
        return columns[i];
    // this column is arrary, we need to check the definition format first
    int ret = fnmatch("*\\[*\\]", type.c_str(), FNM_PATHNAME|FNM_PERIOD);
    if(0 != ret){
        cout<<"Invalid Data Type!!"<<endl;
        return NULL;
    }

    ret = process_array_def(type, NULL, NULL);
    if (ret != 0)
        return NULL;
    return columns[i];
}
//------------------------------------------------------------------------------
class Parser
{
    public:
        Parser()
        {
            ha_map.clear();
            ha_map["int"]=&ha_builtin_int;
            ha_map["float"]=&ha_builtin_float;
            ha_map["char*"]=&ha_builtin_char_string;
            ha_map["UDT_BOOL"]=&ha_udt_bool;
            ha_map["UDT_USER"]=&ha_udt_user;
        }
        ~Parser()
        {
        }
        TableDef& get_table_def();
        static bool is_this_type_supported(string type);
        int parse_line(string line, int col_count = 0);
        string get_type(int i);
        int parse_array(string def, string column);
        int parse_low(string line, char tab, int col_count, string type=string(""));
        Base_Type* get_handler(string type);
    private:
        TableDef table_def;
        static map<string, Base_Type*> ha_map; 
        BUILT_IN_INT ha_builtin_int;
        BUILT_IN_FLOAT ha_builtin_float;
        BUILT_IN_CHAR_STRING ha_builtin_char_string;
        UDT_BOOL ha_udt_bool;
        UDT_USER ha_udt_user;
};

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
    if (get_table_def().process_array_def(def,&type,&ele_count))
        return -1;
    unsigned int start=0;
    unsigned int loc = 0;
    //find ':'
    char tab = ':';
    loc = arr_str.find(tab, start );
    start = loc + 1;
    // array looks like this: 
    // item1,item2,item3
    string  array = arr_str.substr(start);
    tab = ',';
    parse_low(array, tab, ele_count, type);
}

Base_Type* Parser::get_handler(string type)
{
    map<string, Base_Type*>::iterator it = ha_map.find(type); 
    //my_Itr.find(type.c_str()); 
    if( it != ha_map.end() )
        return it->second; 
    return NULL;
}

bool Parser::is_this_type_supported(string type)
{
    map<string, Base_Type*>::iterator it = ha_map.find(type); 
    if( it != ha_map.end() )
        return true; 
    return false;
}
int Parser::parse_low(string line, char tab, int col_count, string type)
{
    bool type_is_null = false;
    unsigned int start=0;
    unsigned int loc = 0;
    int i=0;
    if (type.empty())
    {
        type_is_null = true;    
    }
    for (;i<col_count;i++)
    {
        if (i==col_count-1)
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
            if (is_this_type_supported(type))
            {
                Base_Type* handler = get_handler(type);
                handler->parse(sub);
            }
            else//array
            {
                parse_array(type,sub);
            }
        }
        else
        {
            cout << "Didn't find sub" << endl;
        }     
        cout<<endl;
    }
}

int Parser::parse_line(string line, int col_count)
{
    if (col_count == 0)
        col_count = get_table_def().getColCount();
    char tab = ' ';

    parse_low(line, tab, col_count);
}
//------------------------------------------------------------------------------
int main(){
    Parser parser;
    parser.get_table_def().getTableDef();
    ifstream in(filename);
    for (string line; getline(in, line); )
    {
        cout<<line<<endl;
        parser.parse_line(line);
    }

}
//-------------------------------------------------------------------------------

