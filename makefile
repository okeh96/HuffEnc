all: hencode hdecode

hencode: hencode.o
	g++ -o hencode hencode.o 

hencode.o: hencode.cc priqueue.h priqueue.cc
	g++ -c hencode.cc

hdecode: hdecode.o 
	g++ -o hdecode hdecode.o 

hdecode.o: hdecode.cc priqueue.h priqueue.cc
	g++ -c hdecode.cc

clean: 
	rm -rf hencode.o priqueue.o hdecode.o hdecode hencode