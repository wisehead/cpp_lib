prefix=/usr/local
INCPATH=$(prefix)/include
LIBPATH=$(prefix)/lib


LIBS+=$(LIBPATH)/libboost_thread-mt.a

all:
	clang++ -L/usr/local/lib -lboost_thread-mt -lboost_system main.cpp -o main
