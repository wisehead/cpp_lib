test: add_people list_people

add_people: add_person.cpp protoMid
	g++ -std=c++11 add_person.cpp Person.pro.pb.cc -o add_people `pkg-config --cflags --libs protobuf`

list_people: list_person.cpp protoMid   
	g++ -std=c++11 list_person.cpp Person.pro.pb.cc -o list_people `pkg-config --cflags --libs protobuf`  

protoMid: Person.pro
	protoc -I=. --cpp_out=. ./Person.pro

clean:
	rm -f add_people list_people protoMid
	rm -f Person.pro.pb.cc Person.pro.pb.h

