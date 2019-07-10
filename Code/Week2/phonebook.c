#include <stdio.h>
#include <stdlib.h>
#define MAX_PHONE_NUMBER 100

typedef struct{
    long number;
    char name[80];
} PhoneEntry;

typedef struct{
    PhoneEntry enries[MAX_PHONE_NUMBER];
    int total;
} PhoneBook;

void addPhoneNumber(long number, char *name, PhoneBook *book)
{
    book->enries[]
}
