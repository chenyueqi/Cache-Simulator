# setting compiler and compile options
CC = gcc
CFLAGS = -std=c99

#target to compile
CFILES = $(shell find ./ -name "*.c")
OBJS = $(CFILES:.c=.o)

#test files
TESTFILE = $(shell find ../../test/ -name "*.trace")

#result files
RESULTFILE = ../../result/LM/result.txt

cache_simulator: $(OBJS)
	$(CC) -o cache_simulator $(OBJS) $(CFLAGS)

.PHONY: clean test
test: 
	./cache_simulator $(TESTFILE) $(RESULTFILE)

clean: 
	rm -f cache_simulator
	rm -f $(OBJS) $(OBJS:.o=.d)
	rm -f *~
