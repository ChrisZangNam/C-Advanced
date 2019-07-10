#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INTITAL_SIZE 100
#define INCREMENTAL_SIZE 10

typedef struct{
    void *key;
    void *value;
} Entry;

typedef struct{
    Entry *entries;
    int size;
    int total;
    Entry (*makeNode)(void *, void *);
    int (*compare)(void *, void *);
} SymbolTable;

SymbolTable createSymbolTable(
    Entry (*makeNode)(void *, void *),
    int (*compare)(void *, void *));
void dropSymbolTable(SymbolTable *tab);
void addEntry(void *key, void *value, SymbolTable *book);
Entry *getEntry(void *key, SymbolTable book);

int comparePhone(void *key1, void *key2)
{
    return strcmp((char *)key1, (char *)key2);
}

Entry makePhone(void *name, void *phone)
{
    Entry res;
    res.key = strdup((char *)name);
    res.value = malloc(sizeof(long));
    memcpy(res.value, phone, sizeof(long));
    return res;
}

SymbolTable createSymbolTable(Entry (*makeNode)(void*, void*), int (*compare)(void*, void*))
{
    SymbolTable tab;
    tab.size = INTITAL_SIZE;
    tab.total = 0;
    tab.entries = malloc(sizeof(Entry) * tab.size);
    tab.makeNode = makeNode;
    tab.compare = compare;

    return tab;
}

void dropSymbolTable(SymbolTable *tab)
{
    tab->total = 0;
    tab->size = INTITAL_SIZE;

    free(tab->entries);
}

int binarySearch(Entry *entries, int l, int r, void* key, int* found, int (*compare)(void *, void *))
{
    int index, res;

    if (l > r)
    {
        *found = 0;
        return l;
    }

    index = (l + r) / 2;
    res = compare((char *)entries[index].key, (char *)key);
    if (res == 0)
    {
        *found = 1;
        return index;
    }
    else if (res > 0)
        binarySearch(entries, l, index - 1, key, found, compare);
    else
        binarySearch(entries, index + 1, r, key, found, compare);
}


void addEntry(void *key, void *value, SymbolTable *book)
{
        int found;
        int index = binarySearch(book->entries, 0, book->total-1, key, &found, comparePhone);

        if (found == 1)
            memcpy(book->entries[index], book->makeNode(key, value), sizeof(Entry));
        if (found == 0)
        {
            if (book->total >= book->size)
            {
                book->size += INCREMENTAL_SIZE;
                book->entries = (Entry *)malloc(sizeof(Entry) * book->size);
            }
            Entry *new;
            memcpy(new, book->makeNode(key, value), sizeof(Entry));

            int i = book->total - 1;
            while(i>=0 && book->compare(new->key, book->entries[i].key) <0 )
            {
                memcpy(book->entries[i + 1],book->entries[i], sizeof(Entry));
                i--;
            }
            memcpy(book->entries[i + 1], new, sizeof(Entry));
            book->total++;
        }
}

/*void printPhoneBook(SymbolTable book)
{

    for (int i = 0; i < book.total; i++)
        printf("%s\t%ld\n", book.entries[i].key, book.entries[i].value);
}*/

int main()
{
    SymbolTable p;
    Entry *result;
    p = createSymbolTable(makePhone, comparePhone);

    char name[50];

    addEntry("Manh", 0124567, &p);
    addEntry("BaoAnh", 0121246, &p);
    addEntry("Huy", 01154246, &p);
    addEntry("Loi", 011021246, &p);

   // printPhoneBook(p);

    /*printf("Add name to find: ");
    gets(name);
    result = getPhoneNumber(name, p);
    if (result != NULL)
        printf("Phonenumber is %ld\n", result->number);
    else
        puts("The entry does not exist.");
        */
}
