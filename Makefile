all: preprocess encode

preprocess:  preprocess.o 
	g++ preprocess.o -o preprocess

preprocess.o: preprocess.cpp defns.h
	g++ -c preprocess.cpp

encode:  encode.o 
	g++ encode.o -o encode

encode.o: encode.cpp defns.h
	g++ -c encode.cpp

clean:
	rm *.o output