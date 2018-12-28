/*******************************************************************************
 *      File Name: parser.h                                               
 *         Author: Hui Chen. (c) 2015                             
 *           Mail: chenhui13@baidu.com                                        
 *   Created Time: 2015/08/05-15:18                                    
 *	Modified Time: 2015/08/05-15:18                                    
 *******************************************************************************/
using namespace std;
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>

class Base_Type 
{
    public:
        virtual int parse(string str)
        {
            printf("in parse() of Base_Type.\n");
            return 0;
        }
};
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
/*
   Base Class of User Defined Type, if you want to define a new UDT, please implement
   the function parse(), and add your UDT name to the array type_arr.

   if you want to add a new User Defined Type, you need to
   1.inherit from UDT;
   2.implement interface parse();
   3.add a member of the new Type to class Handler, and add it to the ha_map in constuctor function;
   */
class UDT: public Base_Type
{
    public:
        virtual int parse(string str)
        {
            printf("in parse() of UDT.\n");
            return 0;
        }
};

class UDT_BOOL:public UDT
{
    public:
        virtual int parse(string str);
    private:
        bool value;
};

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

typedef map<string, Base_Type*> MAP_STRING_BASETYPE; 

class Handler
{
    public:
        static Handler * GetInstance()//通过静态公有函数获得该类的实例对象
        {
            if(m_pInstance==NULL)
                m_pInstance=new Handler();
            return m_pInstance;
        }

        bool is_this_type_supported(string type);
        Base_Type* get_handler(string type);
    private:
        Handler()
        {
            ha_map.clear();
            ha_map["int"]=&ha_builtin_int;
            ha_map["float"]=&ha_builtin_float;
            ha_map["char*"]=&ha_builtin_char_string;
            ha_map["UDT_BOOL"]=&ha_udt_bool;
            ha_map["UDT_USER"]=&ha_udt_user;
        }
        static Handler * m_pInstance;
        class Garbo//删除Handler实例的对象
        {
            public:
                ~Garbo()
                {
                    if(Handler::m_pInstance)
                    {
                        delete Handler::m_pInstance;
                    }
                }
        };
        static Garbo gb;//在程序结束时，系统会调用它的析构函数

        MAP_STRING_BASETYPE ha_map; 
        BUILT_IN_INT ha_builtin_int;
        BUILT_IN_FLOAT ha_builtin_float;
        BUILT_IN_CHAR_STRING ha_builtin_char_string;
        UDT_BOOL ha_udt_bool;
        UDT_USER ha_udt_user;
};
Handler * Handler::m_pInstance=NULL;//初始化静态数据成员


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

        int init();
        int getColCount();
        string get_type(int i);
        int check_and_get_array_def(string arr_str, string* ele_type, int* ele_count);
    private:
        std::vector<string> columns; 
};

class Parser
{
    public:
        Parser()
        {
        }
        ~Parser()
        {
        }
        TableDef& get_table_def();
        int parse_line(string line);
        int parse_array(string def, string column);
        int parse_low(string line, char tab, int col_count, string type=string(""));
    private:
        TableDef table_def;
};

