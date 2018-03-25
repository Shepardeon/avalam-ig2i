all: avalam-diag.exe

json.o: src/json.c
	gcc -c src/json.c -I src/include/ -o obj/json.o

avalam-diag.exe: src/main.c json.o
	gcc obj/*.o src/main.c -I src/include/ -L lib/* -o bin/avalam-diag.exe

clean:
	rm -f obj/*

clean-all:
	rm -f obj/*
	rm -f bin/avalam-diag.exe