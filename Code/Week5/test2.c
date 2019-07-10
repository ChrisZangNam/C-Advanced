#include<stdio.h>
#include"btree.h"

int main()
{
	char pb[] = "phone.db";

	// Initialization
	btinit();
	BTA *book;

	// Open a b-tree file
	book = btopn(pb, 0, 0);
	if (book == NULL)
		book = btcrt(pb, 0, 0);

	binsky(book, "chung",9998);
	binsky(book, "diep", 9999);

	bupdky(book, "chung", 9999);

	long value;
	int res = bfndky(book, "ha", &value);
	if(res == 0)
		printf("Phone number: %ld\n", value);
	else
		printf("Not be found\n");
	// Close
	btcls(book);

}
