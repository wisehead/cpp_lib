GCOV_FLAGS=-fprofile-arcs -ftest-coverage
CFLAGS+=$(GCOV_FLAGS)
LDFLAGS+=-lpthread $(GCOV_FLAGS)

target=main

all:$(target)

main : test.o main.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "gdb-gcov≤‚ ‘≥Ã–Ú∏≤∏«¬ ..."

%.o : %.c
	$(CC) -g -c $^ -o $@ $(CFLAGS) $(DEFINES)

.PHONY : clean
clean :
	rm -rf *.o
	rm -rf $(target)
	rm -rf *.gcov *.gcda *.gcno
