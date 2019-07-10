#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

//gcc -o btree btree.c -Iinc -Llib -lbt

int main(){
	char pb[] = "phonebook.db";

	//Initialization
	btinit();
	BTA *book;

	//Open a b-tree file
	book = btopn(pb,0,0);
	if  (book == NULL) book = btcrt(pb,0,0);

	binsky(book, "chung", 9294238);
	binsky(book, "diep" , 2342342);

	long value;
	bfndky(book, "chung", &value);
	printf("Phone number: %ld\n",value);

	//Close
	btcls(book);

}