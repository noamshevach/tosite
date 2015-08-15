
myprog: proj.o Queue.o SymbolTable.o 
	gcc -g -ansi -Wall proj.o Queue.o SymbolTable.o  -o myprog

proj.o: proj.c 
	gcc -c -ansi -Wall proj.c   -o proj.o

Queue.o: Queue.c 
	gcc -c -ansi -Wall Queue.c   -o Queue.o

SymbolTable.o: SymbolTable.c 
	gcc -c -ansi -Wall SymbolTable.c  -o SymbolTable.o
	