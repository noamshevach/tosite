
myprog: proj.o Queue.o SymbolTable.o proj.h Queue.h SymbolTable.h
	gcc -g -ansi -Wall proj.o Queue.o SymbolTable.o proj.h Queue.h SymbolTable.h  -o myprog

proj.o: proj.c 
	gcc -c -ansi -Wall proj.c   -o proj.o

Queue.o: Queue.c 
	gcc -c  -Wall Queue.c   -o Queue.o

SymbolTable.o: SymbolTable.c 
	gcc -c  -Wall SymbolTable.c  -o SymbolTable.o
	