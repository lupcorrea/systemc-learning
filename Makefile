CC = g++

all:
	g++ -o test *.cpp -I /Users/lupcorrea/Documents/SystemC/systemc-2.3.1/include -L /Users/lupcorrea/Documents/SystemC/systemc-2.3.1/lib -lsystemc

clean:
	rm test
