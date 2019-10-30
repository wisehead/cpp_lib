/*******************************************************************************
 *      file name: add_person.cpp                                               
 *         author: Hui Chen. (c) 2019                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2019/10/30-16:05:48                              
 *  modified time: 2019/10/30-16:05:48                              
 *******************************************************************************/
#include "Person.pro.pb.h"
#include <fstream>
#include <iostream>
using namespace std;

void PromptForAddress(tutorial::Person*);

int main(int argc, char* argv[])
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    if(2 != argc)
    {
        //必须指定电话本名称才执行程序
        cerr << "Usage:  " << argv[0] << " ADDRESS_BOOK_FILE" << endl;
        return -1;
    }

    tutorial::AddressBook address_book;

    fstream in("ADDRESS_BOOK_FILE", ios::binary | ios::in);
    if(!in)
    {
        cerr << "open file ADDRESS_BOOK_FILE failed!\n";
        return -1;
    }

    if(!address_book.ParseFromIstream(&in))
    {
        cerr << "Parse File ADDRESS_BOOK_FILE failed!\n";
        return -1;
    }

    in.close();
    //增加一个Person
    //具有repeated的属性可通过add_fieldname方法增加一个属性
    PromptForAddress(address_book.add_person());

    fstream out("ADDRESS_BOOK_FILE", ios::binary | ios::out | ios::trunc);
    if(!address_book.SerializeToOstream(&out))
    {
        cerr << "Failed to Write Address Book!\n";
        return -1;  
    }

    //可选的，回收所有ProtoBuf分配的对象
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}


void PromptForAddress(tutorial::Person* person)
{
    cout<<"Enter a Person ID number: ";
    int id;
    cin >> id;
    person->set_id(id);
    /*忽略CIN的前256个字符，或者忽略CIN的换行符之前的字符，包括换行符
    这样的话不会将换行符之前的其他类型的数据保留在输入缓冲中    
    */
    cin.ignore(256, '\n');
    cout<<"Enter name: ";
    getline(cin, *person->mutable_name());

    cout<< "Enter email address (blank for none): ";
    string email;
    getline(cin,email);
    if(!email.empty())
        person->set_email(email);
    while(true)
    {
        cout<<"Enter a phone number (or leave blank to finish): ";
        string number;
        getline(cin, number);
        if(number.empty())
            break;
        tutorial::Person::PhoneNumber* phone_number = person->add_phone();
        phone_number->set_number(number);

        cout<<"Is this a mobile, home, or work phone? ";
        string type;
        getline(cin, type);
        if(type == "mobile")
            phone_number->set_type(tutorial::Person::MOBILE);
        else if( type == "home")
            phone_number->set_type(tutorial::Person::HOME);
        else if (type == "work")
            phone_number->set_type(tutorial::Person::WORK);
        else
        {
            cout << "Unknown phone type.  Using default." << endl;
            phone_number->set_type(tutorial::Person::HOME);
        }

    }

}
