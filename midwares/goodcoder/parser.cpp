/*******************************************************************************
 * Copyright 2015 Baidu Inc. All Rights Reserved.
 * Author: Hui Chen (chenhui13@baidu.com)
 *
 * File Name: parser.cpp                                               
 * Source file, this file implements the parser functionality.
 * Created Time: 2015/07/31-15:39                                    
 *******************************************************************************/
#include "./parser.h"
#include <fstream>
#include <stdlib.h>
#include <fnmatch.h>
// the file to be parsed.
const char filename[] = "a.in";

namespace goodcoder{

const char table_def_file[] = "TableDef.txt";
//------------------------------------------------------------------------------
// parse the user defined type UdtBool.
int UdtBool::parse(string str) {
    if (!str.compare("TRUE")) {
        _value = true;
        printf("UdtBool: %d; ",_value);
        return 0;
    } else if (!str.compare("FALSE")) {
        _value = false;
        printf("UdtBool: %d; ",_value);
        return 0;
    } else {
        return -1;
    }
}

// parse the user defined type UdtUser.
int UdtUser::parse(string str) {
    //cout<<"in UdtUser::parse()!!"<<endl;
    unsigned int start=0;
    unsigned int loc = 0;
    int i=0;
    char tab = ',';
    std::vector<string> fields; 
    fields.empty();
    int col_count = 4;

    for (; i<col_count; i++) {
        if (i==col_count-1) {
            loc = str.length();
        } else {
            loc = str.find(tab, start );
        }

        if (loc != string::npos) {
            string temp = str.substr(start,loc-start);
            fields.push_back(temp);
            //cout <<start<<" "<<loc<<" Found sub string " << fields[i] << endl;
            start = loc + 1;
            while(str.c_str()[start]==' ') {
                start++;
            }
        } else {
            cout << "UdtUser::parse(): Didn't find sub string." << endl;
            return -1;
        }     
    }

    _userId = atoi(fields[0].c_str());

    int len_name = fields[1].length();
    //cout<<"len_name is:"<<len_name<<endl;
    _name = new char[len_name + 1];
    memset( _name, 0, len_name+1 );
    fields[1].copy( _name, len_name );
    
    _age = atoi(fields[2].c_str());
    _money = atof(fields[3].c_str());

    printf("userId is:%d; name is:%s; age is:%d; money is:%f\n",_userId,_name,_age,_money);

    if (_name != NULL) {
        delete [] _name;
        _name = NULL;
    }

    return 0;
}

// parse the built in INT.
int BuiltinInt::parse(string column) {
    _value = atoi(column.c_str());
    printf("int: %d; ",_value);
    return 0;
}

// parse the built in FLOAT.
int BuiltinFloat::parse(string column) {
    _value = atof(column.c_str());
    printf("float: %f; ",_value);
    return 0;
}

// parse the built in char*
int BuiltinCharString::parse(string column) {
    int len_name = column.length();
    //cout<<"len_name is:"<<len_name<<endl;
    _value = new char[len_name + 1];
    memset( _value, 0, len_name+1 );
    column.copy( _value, len_name );
    printf("string: %s; ",_value);

    // each time when we exit this funcion, free the memory
    if (_value) {
        delete [] _value;
        _value = NULL;
    }
    return 0;
}

//------------------------------------------------------------------------------
// get the corresponding handler for the type from the handler map, 
// return NULL if not found.
BaseType* Handler::get_handler(string type) {
    MAP_STRING_BASETYPE::iterator it = _handler_map.find(type); 
    if (it != _handler_map.end()) {
        return it->second; 
    }
    return NULL;
}

// check whether this type is supported in this parser.
// if not supported, you might want to define a new type to parse it.
bool Handler::is_this_type_supported(string type) {
    MAP_STRING_BASETYPE::iterator it = _handler_map.find(type); 
    if (it != _handler_map.end()) {
        return true; 
    }
    return false;
}

//------------------------------------------------------------------------------
// read the table definition from the table_def_file, which is provided by user
// to define the table struct.
int TableDef::init() {
    std::ifstream in(table_def_file);
    cout<<"TABLE DEFINITION:"<<endl;
    cout<<"------------------------------"<<endl;
    for (string str; getline(in, str);) {
        cout<<str<<endl;
        columns.push_back(str);
    }
    cout<<"------------------------------"<<endl;
    return 0;
}

int TableDef::get_col_count() {
    return columns.size();
}

// this function is used to parse the string to array definition, and validate it.
// if will also return the array type and element count if the pass-in parameter is not NULL.
int TableDef::check_and_get_array_def(string arr_str, string* ele_type, int* ele_count) {
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
    if (temp_count <= 0) {
        printf("The array num is invalid!!\n");
        return -1;
    }

    string temp_type = arr_str.substr(0,left_loc);
    if (!Handler::get_instance()->is_this_type_supported(temp_type)) {
        cout<<"Invalid Data Type!!"<<endl;
        return -1;
    }

    if (ele_type != NULL) {
        *ele_type = temp_type;
    }
    if (ele_count != NULL) {
        *ele_count = temp_count;
    }
    return 0;
}

// get the data type of the column.
// the data type is already read-in in init(). 
// if there are any errors, return an emptyp string.
string TableDef::get_type(int i) {
    string empty("");
    if (i < 0 || i > get_col_count()) {
        return empty;
    }

    string type = columns[i];
    if (Handler::get_instance()->is_this_type_supported(type)) {
        return columns[i];
    }

    // this column is arrary, we need to check the definition format first
    int ret = fnmatch("*\\[*\\]", type.c_str(), FNM_PATHNAME|FNM_PERIOD);
    if (0 != ret) {
        cout<<"TableDef::get_type(): Invalid Data Type!!"<<endl;
        return empty;
    }

    ret = check_and_get_array_def(type, NULL, NULL);
    if (ret != 0) {
        return empty;
    }
    return columns[i];
}
//------------------------------------------------------------------------------
TableDef& Parser::get_table_def() {
    return _table_def;    
}

// def is the array definition, it tells us the data type of this array.
// and the count of the elements.
// arr_str looks like this:  num:item1,item2,item3
int Parser::parse_array(string def, string arr_str) {
    string type;
    int ele_count = 0;
    if (get_table_def().check_and_get_array_def(def,&type,&ele_count)) {
        cout<<"Parser::parse_array(): get array def failed."<<endl;
        return -1;
    }

    unsigned int start=0;
    unsigned int loc = 0;
    //find ':'
    char tab = ':';
    loc = arr_str.find(tab, start );
    if (loc == string::npos) {
        cout<<"Parser::parse_array(): can't find sub string."<<endl;
        return -1;
    }

    start = loc + 1;
    // array looks like this: 
    // item1,item2,item3
    string  array = arr_str.substr(start);
    tab = ',';
    if (parse_low(array, tab, ele_count, type)) {
        return -1;
    }
    return 0;
}

// line: is the string to be parsed
// tab:  is the separator
// ele_count: tells us how many elements in this string(line). 
// type: the data type of this line (when the caller is parse_array), if 
//       the caller is parse_line, then type is an empty string, since
//       the data type of each columns are different. it has to get the
//       data type from TableDef::get_type().
int Parser::parse_low(string line, char tab, int ele_count, string type) {
    if (ele_count <= 0) {
        cout<<"Parser::parse_low(): ele_count is invalid."<<endl;
        return -1;
    }

    bool type_is_null = false;
    unsigned int start=0;
    unsigned int loc = 0;
    int i=0;
    if (type.empty()) {
        type_is_null = true;    
    }

    for (; i < ele_count; i++) {
        if (i == ele_count-1) {
            loc = line.length();
        } else {
            loc = line.find(tab, start );
        }

        if (loc != string::npos) {
            string sub = line.substr(start,loc-start);
            //cout <<start<<" "<<loc<<" Found sub string " << sub << endl;
            start = loc + 1;
            while(line.c_str()[start]==' ') {
                start++;
            }

            if (type_is_null) {
                type = get_table_def().get_type(i);
            }

            if (Handler::get_instance()->is_this_type_supported(type)) {
                BaseType* handler = Handler::get_instance()->get_handler(type);
                if (handler==NULL) {
                    cout<<"NULL------------------"<<endl;
                }
                
                if (handler) {
                    int ret = handler->parse(sub);
                    if (ret != 0) {
                        cout <<"Parser::parse_low(): got error in parse."<<endl;
                        return -1;
                    }
                }
            } else {
                if (parse_array(type,sub)) {
                    return -1;
                }
            }
        } else {
            cout << "Parser::parse_low(): Didn't find sub string." << endl;
            return -1;
        }     
        cout<<endl;
    }
    return 0;
}

// parse a line from the input file.
int Parser::parse_line(string line) {
    int  col_count = get_table_def().get_col_count();
    char tab = ' ';
    return parse_low(line, tab, col_count);
}

}//namespace goodcoder
//------------------------------------------------------------------------------
int main() {
    goodcoder::Parser parser;
    parser.get_table_def().init();
    std::ifstream in(filename);

    for (string line; getline(in, line); ) {
        cout<<line<<endl;
        if (parser.parse_line(line)) {
            cout<<"main(): get error from parse_line."<<endl;
            return -1;
        }
    }

}
//-------------------------------------------------------------------------------
