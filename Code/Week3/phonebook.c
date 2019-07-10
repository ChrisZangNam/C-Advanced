#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INITIAL_SIZE 10
#define INCREMENTAL_SIZE 5

typedef struct{
    long number; //value
    char name[80]; //key
} PhoneEntry;

typedef struct{
    PhoneEntry *entries;
    int total; //so du lieu hien tai
    int size;//so lieu toi da cua phonebook
} PhoneBook;

PhoneBook createPhoneBook()
{
    PhoneBook p;
    p.size = INCREMENTAL_SIZE;
    p.entries = (PhoneEntry *)malloc(sizeof(PhoneEntry) * INITIAL_SIZE);
    p.total = 0;

    return p;
}

void dropPhoneBook(PhoneBook* book)
{
    book->total = 0;
    book->size = INITIAL_SIZE;
    free(book->entries);
}

int binarySearch(PhoneEntry* entries, int l, int r, char *name, int* found)
{
    int index;

    if(l > r)
    {
        *found = 0;
        return l;
    }

    index = (l + r) / 2;
    if(strcmp(entries[index].name, name) == 0){
            *found = 1;
            return index;
    }
    else if(strcmp(entries[index].name, name) > 0)
                binarySearch(entries, l, index-1, name, found);
        else
                binarySearch(entries, index + 1, r, name, found);
}

void move(PhoneBook *book, int index, int last)
{
    if(index > last)
        return;
    book->entries[last + 1] = book->entries[last];
    move(book, index, last - 1);
}

void addPhoneNumber(char *name, long number, PhoneBook* book)
{
    int found;
    int index = binarySearch(book->entries, 0, book->total-1, name, &found);

    if (found == 1)
        book->entries[index].number = number;
    if(found == 0)
    {
        if(book->total >= book->size)
        {
            book->size += INCREMENTAL_SIZE;
            book->entries = (PhoneEntry *)malloc(sizeof(PhoneEntry) * book->size);
        }
        if(book->total != 0)
        {
            move(book, index, book->total - 1);
        }
        book->total++;
        book->entries[index].number = number;
        strcpy(book->entries[index].name, name);
    }
}

PhoneEntry* getPhoneNumber(char* name, PhoneBook book)
{
    int found;
    int pos = binarySearch(book.entries, 0, book.total-1, name, &found);

    if(found == 1)
        return &book.entries[pos];
    else
        return NULL;
}

void printPhoneBook(PhoneBook book)
{

    for (int i = 0; i < book.total ; i++)
        printf("%s\t%ld\n", book.entries[i].name, book.entries[i].number);
}
int main()
{
    PhoneBook p;
    PhoneEntry* result;
    p = createPhoneBook();
    char name[50];

    addPhoneNumber("Manh", 0124567, &p);
    addPhoneNumber("BaoAnh", 0121246, &p);
    addPhoneNumber("Huy", 01154246, &p);
    addPhoneNumber("Loi", 011021246, &p);

    printPhoneBook(p);

    printf("Add name to find: ");
    gets(name);
    result = getPhoneNumber(name, p);
    if(result != NULL)
        printf("Phonenumber is %ld\n", result->number);
    else
        puts("The entry does not exist.");
}
