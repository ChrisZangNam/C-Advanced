#include <stdlib.h>
#include <stdio.h>
#include "btree.h"
#include <string.h>


typedef struct{
    char name[80];
    long number;
} PhoneBook;


//gcc ~.c -Lbtree/lib -lbt -Ibtree/inc
int
main()
{
    char ph[] = "book2.db";
    PhoneBook phone;

    btinit();
    BTA *book;

    unsigned int choice = 1;

    //open a b-tree file
    book = btopn(ph, 0, 0);
    if(book == NULL)
        book = btcrt(ph, 0, 0);


    while (choice != 0)
    {
        printf("Enter name: ");
        gets(phone.name);
        printf("Enter phone number: ");
        scanf("%ld%*c", &phone.number);

        binsky(book, phone.name, phone.number);

        //btins(book, phone.name, &phone.number, sizeof(phone.number));
        printf("Enter 1 to insert, 0 to exit: ");
        scanf("%d%*c", &choice);
    }
    char name[80];
    long value;

    printf("Enter name to find: ");
    gets(name);
    bfndky(book, name, &value);
    printf("Phone Number: %ld\n", value);
    //close
    btcls(book);
}
