CC = g++

all: calcA calcAt1 calcAt2 calcAt4 calcAp1 calcAp2 calcAp4

calcA: calcA.cpp
	$(CC) -o $@ $^

calcAt1: calcAt1.cpp
	$(CC) -o $@ $^

calcAt2: calcAt2.cpp
	$(CC) -o $@ $^

calcAt4: calcAt4.cpp
	$(CC) -o $@ $^

calcAp1: calcAp1.cpp
	$(CC) -o $@ $^

calcAp2: calcAp2.cpp
	$(CC) -o $@ $^

calcAp4: calcAp4.cpp
	$(CC) -o $@ $^