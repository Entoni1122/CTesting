#include <stddef.h>
#include <stdio.h>

#define get_list(x)&(x.list_item)

struct list_item* listPop(struct list_item** head);
struct list_item* list_append(struct list_item** head, struct list_item* item);

 struct list_item  
{
    struct list_item* next;
    unsigned int counter;

};

struct int_item
{
    struct list_item list_item;
    int value;
};

struct list_item* list_get_tail(struct list_item* head)
{
    if(!head)
    {
        return NULL;
    }
    struct list_item *current_node = head;
    struct list_item *last_node = NULL;
    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }
        return last_node;
};

struct list_item* list_append(struct list_item** head, struct list_item* item)
{
    struct list_item* tail = list_get_tail(*head);
    if(!tail)
    {
        *head = item;
    }
    else
    {
        tail->next = item;
    }
    item->next = NULL;
    return item;
}

unsigned int list_lenght(struct list_item* head)
{
    return head->counter;
}

void list_remove_at(struct list_item** head, int index)
{
    unsigned int len = list_lenght(*head);

    if (!*head) 
    {
        printf("La lista è vuota\n");
    }

    if (index == 0) 
    {
        printf("Next Time call pop\n");
        listPop(head);
        return;
    }

    struct list_item* current = *head;
    struct list_item* previous = NULL;
    int i = 0;
    if(index > len)
    {
        printf("Indice fuori dai limiti della lista\n");
        return;
    }
    while(i < index) 
    {
        previous = current;
        current = current->next;
        i++;
    }
    previous->next = current->next;
}

struct list_item* list_remove_specific(struct list_item** head,struct list_item* target)
{
    unsigned int len = list_lenght(*head);
    
    struct list_item* current = *head;
    struct list_item* prev = NULL;
    
    if(len != 0 || target < len)
    {
        if(current == target)
        {
            listPop(head);
            return NULL;
        }
        for (int i = 0; i < len; i++)
        {
            prev = current;
            current =  current->next;
            if(current == target)
            {
                prev->next = current->next;
                current = NULL;
                break;
            }
        }
        return *head;
    }
    else
    {
        return NULL;
    }
}

void printList(struct int_item* head) 
{
    while (head != NULL) 
    {
        printf("List Value : %d\n", head->value);
        head = head->list_item.next;
    }
}

struct list_item* listPop(struct list_item** head)
{
    if(!*head)
    {
        return NULL;
    }
    struct list_item* current_head = *head;
    const unsigned int  headCounter = current_head->counter;
    *head = (*head)->next;
    if(*head)
    {
        (*head)->counter = headCounter - 1;
    }
    current_head->next = NULL;
    return current_head;
}

void reverse_list(struct list_item** _head)
{
    struct  list_item* current = *_head;
    struct  list_item* next = NULL;
    struct  list_item* prev = NULL;

    while(!current)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    (*_head) = prev;
}

int main(int argc, char** argv)
{
    struct list_item* head = NULL;
    struct int_item item;
    struct int_item item1;
    struct int_item item2;
    struct int_item item3;
    struct int_item item4;
    struct int_item item5;
    
    item.value = 100;
    item1.value = 111;
    item2.value = 122;
    item3.value = 133;
    item4.value = 144;
    item5.value = 155;
    
    list_append(&head,(struct list_item *)get_list(item));
    list_append(&head,(struct list_item *)get_list(item1));
    list_append(&head,(struct list_item *)get_list(item2));
    list_append(&head,(struct list_item *)get_list(item3));
    list_append(&head,(struct list_item *)get_list(item4));
    list_append(&head,(struct list_item *)get_list(item5));

    printf("-----------List-----------------\n");

    printList(head);

    printf("-----------Remove at specific-----------------\n");

    list_remove_specific(&head,get_list(item3));
    printList(head);
    
    printf("-----------Remove at index-----------------\n");

    list_remove_at(&head,2);
    printList(head);

    printf("-----------Reverse--------------------\n");

    reverse_list(&head);
    printList(head);

    return 0;
}