#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

cll_node *cll_head(cll_node *list) {
    if (list == NULL)
        return NULL;

    while (list->prev != NULL) {
        list = list->prev;
        if (list->is_head == 1) {
            break;
        }
    }

    return list;
}

cll_node *cll_tail(cll_node *list) {
    cll_node *head = cll_head(list);
    if (head == NULL)
        return NULL;

    return head->prev;
}

unsigned long cll_length(cll_node *list) {
    unsigned long length = 0;
    cll_node *head = cll_head(list);

    if (head == NULL)
        return 0;

    cll_node *current = head;
    do {
        length++;
        current = current->next;
    } while (current != head);

    return length;
}

cll_node *cll_find(cll_node *list, int value) {
    cll_node *head = cll_head(list);
    if (head == NULL)
        return NULL;

    cll_node *current = list;
    do {
        if (current->value == value)
            return current;
        current = current->next;
    } while (current != head);

    return NULL;
}

cll_node *cll_remove(cll_node *list) {
    if (list == NULL){
        free(list);
        return NULL;
    }
        
    cll_node *prev = list->prev;
    cll_node *next = list->next;

    if (prev == list && next == list) {
        free(list);
        return NULL;
    }

    prev->next = next;
    
    next->prev = prev;

    if (list->is_head && next != list) {
        
        next->is_head = 1;
    }

    free(list);
    return next;
}

cll_node *cll_insert(int value, cll_node *list, int before) {
    cll_node *new_node = (cll_node *)malloc(sizeof(cll_node));
    if (new_node == NULL)
        return NULL;

    new_node->value = value;
    new_node->is_head = 0;

    if (list == NULL) {
        new_node->is_head = 1;
        new_node->prev = new_node;
        new_node->next = new_node;
        return new_node;
    }

    if (before) {
        cll_node *prev = list->prev;
        new_node->prev = prev;
        new_node->next = list;
       
        prev->next = new_node;
        list->prev = new_node;
    } else {
        cll_node *next = list->next;
        new_node->prev = list;
        new_node->next = next;
        
        next->prev = new_node;
        list->next = new_node;
    }

    return new_node;
}


void cll_show(cll_node *list) {
    cll_node *head = cll_head(list);
    cll_node *ptr = head;
    putchar('[');
    if (ptr) {
        do {
            if (!ptr->is_head) 
                printf(", "); 
            if (ptr == list) 
                putchar('*');
            printf("%d", ptr->value);
            if (ptr == list) 
                putchar('*');
            ptr = ptr->next;
        } while (ptr != head);
    }
    puts("]");
}

int main(int argc, const char *argv[]) {

    cll_node *x = NULL;
    putchar('A'); cll_show(x);
    x = cll_insert(25, x, 1);
    putchar('B'); cll_show(x);
    x = cll_insert(1, x, 0);
    putchar('C'); cll_show(x);
    x = cll_insert(98, x, 1);
    putchar('D'); cll_show(x);
    x = cll_insert(0, x, 1);
    putchar('E'); cll_show(x);
    x = cll_insert(-8, cll_tail(x), 0);
    putchar('F'); cll_show(x);
    cll_node *y = cll_head(x);
    putchar('G'); cll_show(y);
    printf("Length: %lu (or %lu)\n", cll_length(y), cll_length(x));
    x = cll_remove(x);
    putchar('H'); cll_show(x);
    putchar('I'); cll_show(y);
    x = cll_remove(cll_find(y, 98));
    putchar('J'); cll_show(x);
    putchar('K'); cll_show(y);

    return 0;
}