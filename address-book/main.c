#include <stdio.h>
#include <stdlib.h>
#include "address_book.h"

void main(void) {
	struct Person *ptr, *next;
	struct Address_book *pab;
	// create an address book
    	pab = create_address_book();

	// print the address book created
	print_address_book(pab);

	// free space when we are done 
	destroy_address_book(pab);
}
