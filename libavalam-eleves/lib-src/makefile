all: lib
lib : libavalam.so libavalam.a


libavalam.so : libavalam.c
	gcc -shared -I../include -fPIC libavalam.c -o libavalam.so

libavalam.a : libavalam.c
	gcc -I../include -c  libavalam.c -o libavalam.o
	ar qvs libavalam.a  libavalam.o

clean: 
	rm -f  libavalam.so libavalam.a *.o
