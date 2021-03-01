/*******************************************************************************
 *      file name: list_person.cpp                                               
 *         author: Hui Chen. (c) 2019                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2019/10/30-16:06:31                              
 *  modified time: 2019/10/30-16:06:31                              
 *******************************************************************************/

#include "Person.pro.pb.h"
#include <iostream>
#include <fstream>

using namespace std;
void ListPeople(const tutorial::AddressBook& address_book);
int main(int argc, char * argv[])
{
    if(2!=argc)
    {
        cerr << "Usage:  " << argv[0] << " ADDRESS_BOOK_FILE" << endl;
        return -1;
    }

    fstream in("ADDRESS_BOOK_FILE", ios::in | ios::binary);
    tutorial::AddressBook address_book;
    if(!address_book.ParseFromIstream(&in))
    {
        cerr << "Parse Input File failed!"<< endl;
        return -1;
    }

    ListPeople(address_book);
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}

void ListPeople(const tutorial::AddressBook& address_book)
{
    //fieldName_size方法返回具有repeated属性的个数
    for(int i=0; i< address_book.person_size();i++)
    {
        const tutorial::Person& person = address_book.person(i);
        cout<<"Person ID: "<<person.id();
        cout<<"Name: "<<person.name();
        cout<<"Email: "<<person.email();

        for(int j=0; j< person.phone_size();j++)
        {
            const tutorial::Person::PhoneNumber& phone_number = person.phone(j);
            switch(phone_number.type())
            {
                case tutorial::Person::MOBILE:
                  cout << "  Mobile phone #: ";
                  break;
                case tutorial::Person::HOME:
                  cout << "  Home phone #: ";
                  break;
                case tutorial::Person::WORK:
                  cout << "  Work phone #: ";
                  break;
            }
            cout<<phone_number.number()<<endl;  
        }

    }
}
