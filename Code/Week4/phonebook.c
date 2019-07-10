#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"

void addPhoneBook(JRB *phonebook, char *name, long number)
{
    JRB node = jrb_find_str(*phonebook, name);

    if (node == NULL)
        jrb_insert_str(*phonebook, name, new_jval_l(number));
    else
        node->val = new_jval_l(number);
}


void traverse(JRB phonebook)
{
    JRB node;
    jrb_traverse(node, phonebook)
    {
        printf("Name: %-20s\tPhone: %ld\n", jval_s(node->key), jval_l(node->val));
    }
}


int main()
{
    JRB phonebook, node;
    phonebook = make_jrb();


    jrb_insert_str(phonebook, "Manh", new_jval_l(566215));
    jrb_insert_str(phonebook, "Chung", new_jval_l(566325));

    char *name = "Manh";
    long number = 54215;

    addPhoneBook(&phonebook, name, number);

    traverse(phonebook);

    node = jrb_find_str(phonebook, "Manh");
    if(node == NULL)
        printf("%s is not exist\n", jval_s(node->key));
    else
        printf("The phone number of %s is %ld\n", jval_s(node->key), jval_l(node->val));

    return 0;
}
