adb : main.o address_book.o
	gcc -o adb main.o address_book.o

main.o : main.c address_book.h
	gcc -c main.c address_book.h

address_book.o : address_book.c
	gcc -c address_book.c

clean :
	rm  *.o
