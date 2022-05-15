all: test1


test1: test1.o cq.o
	g++ ./test1.o ./cq.o -o test1 -lgmock -lgtest -lpthread  

cq.o: ../cq.cpp
	g++ -c ../cq.cpp

test1.o: test1.cpp
	g++ -c test1.cpp -I../
	
clean:
	rm -f test1.o cq.o test1

