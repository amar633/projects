
#include <stdio.h>
#include <stdlib.h>
#include "address_book.h"

void print_person(const struct Person* person){
    printf("\n-------------------\nName:\t %s\n", person->name);
    printf("Age:\t %d\n", person->age);
    printf("Phone:\t %s\n", person->phone);
  }

void print_address_book(const struct Address_book* address_book){
	struct Person *tmp;
	printf("\n\nAddress Book Listing\n\n");
	tmp = address_book->person;
	for(int i = 0; i <= address_book->address_book_size; i++) {
		print_person(tmp);
		tmp = tmp->next;
  }
}

struct Address_book* create_address_book(void){
    char answer;
	// allocate memory
    struct Address_book *pad= (struct Address_book *) malloc (sizeof(struct Address_book));
	struct Person *ptr= (struct Person *) malloc (sizeof(struct Person));
	pad->person = ptr;
    do {
		printf("Enter Name: ");
		scanf("%s", ptr->name);
		printf("Enter phone: ");
		scanf("%s", ptr->phone);
		printf("Enter age: ");
		scanf("%d", &ptr->age);
		printf("\nDo you want new entry ? Enter y or n ");
		scanf(" %c", &answer);

		if (answer =='y'){
		// create space for next entry in the address book
		struct Person *next= (struct Person *) malloc (sizeof(struct Person));
			// update pointer to point at next person
			ptr->next = next;
			ptr = ptr->next;
			pad->address_book_size += 1;
		} ;
  } while (answer == 'y');
    return pad;
}

void destroy_address_book(struct Address_book* address_book){
   struct Person* tmp;
  // free memory location for all structures holding the persons in the address book
   while (address_book->person != NULL)
		{
			tmp = address_book->person;
			address_book->person= address_book->person->next;
			free(tmp);
		}
	// finally freeing space occupied by the address_book structures
	free (address_book);
}
