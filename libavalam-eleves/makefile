all: build/avalam build/avalam-static

INC=-I./include
LIB=-L./lib

build/avalam.o : example/main.c
	gcc $(INC) -c example/main.c -o build/avalam.o

build/avalam:build/avalam.o 
	gcc $(LIB) build/avalam.o -o build/avalam -lavalam


build/avalam-static:build/avalam.o 
	gcc $(LIB) -static build/avalam.o -o build/avalam-static -lavalam


clean: 
	rm -f build/*
