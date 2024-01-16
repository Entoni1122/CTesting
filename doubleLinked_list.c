#include <stddef.h>
#include <stdio.h>

#define get_list(x)&(x.list_item)

struct list_node
{
    struct list_node *prev;
    struct list_node *next;
    unsigned int counter;
};

struct int_list_node
{
    struct list_node list_item;
    int value;
};

void printList(struct int_list_node* head) 
{
    while (head != NULL) 
    {
        printf("List Value : %d\n", head->value);
        head = head->list_item.next;
    }
    
}

struct list_node* listPop(struct list_node** head)
{
    if(!(*head))
    {
        return NULL;
    }
    struct list_node* current_head = *head;
    const unsigned int  headCounter = current_head->counter;
    *head = (*head)->next;
    if(*head)
    {
        (*head)->counter = headCounter - 1;
    }
    current_head->next = NULL;
    return current_head;
}

struct list_node* list_get_tail(struct list_node* head)
{
    if(!head)
    {
        return NULL;
    }
    struct list_node *current_node = head;
    struct list_node *last_node = NULL;
    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }
        return last_node;
};

struct list_node* list_append(struct list_node** head, struct list_node* item)
{
    struct list_node* tail = list_get_tail(*head);
    if(!tail)
    {
        *head = item;
        (*head)->counter = 1;
    }
    else
    {
        tail->next = item;
        (*head)->counter++;
    }
    item->prev = tail;
    item->next = NULL;
    return item;
}

unsigned int list_lenght(struct list_node* head)
{
    return head->counter;
}

void deleteAtIndex(struct list_node** head, int index)
{
    unsigned int len = list_lenght(*head);

    if (!*head) 
    {
        printf("La lista è vuota\n");
    }

    if (index == 0) 
    {
        printf("Only element on the list Cancelled\n");
        listPop(head);
        return;
    }

    struct list_node* current = *head;
    int i = 0;
    if(index > len)
    {
        printf("Indice fuori dai limiti della lista\n");
        return;
    }
    while(i < index) 
    {
        current = current->next;
        i++;
    }
    (*head)->counter--;
    current->prev->next = current->next;
}

void remove_item_doubleLinked(struct list_node** head,struct list_node* item)
{
    unsigned int len = list_lenght(*head);
    if (!*head) 
    {
        printf("La lista è vuota\n");
    }
    if (*head == item) 
    {
        listPop(head);
        return;
    }
    struct list_node* current = *head;
    int i = 0;
    
    while(i < len) 
    {
        if (current == item) 
        {
            current->prev->next = current->next;
            (*head)->counter--;
            item = NULL;
        }
        current = current->next;
        i++;
    }
}

void insert_after_item(struct list_node** head,struct list_node* item_in_list,struct list_node* item)
{
    if (*head == NULL || item_in_list == NULL) 
    {
        fprintf(stderr, "La lista o l'elemento nella lista non possono essere nulli\n");
    }

    struct list_node* current = *head;

    while (current != NULL)
    {
        if (current == item_in_list) 
        {
            item->next = current->next;
            item->prev = current;
            if (current->next != NULL) 
            {
                current->next->prev = item;
                (*head)->counter++;
            }
            
            current->next = item;
            return;
        }
        current = current->next;
    }

    fprintf(stderr, "L'elemento nella lista non è stato trovato\n");
}

void insert_before_item(struct list_node** head,struct list_node* item_in_list,struct list_node* item)
{
    if (*head == NULL || item_in_list == NULL) 
    {
        fprintf(stderr, "La lista o l'elemento nella lista non possono essere nulli\n");
    }

    struct list_node* current = *head;

    int count = (*head)->counter;

    if(current == item_in_list)
    {
        item->prev = NULL;
        item->next = current;
        current->prev = item;
        (*head) = item; 
        (*head)->counter = count + 1;
        return;
    }

    while (current != NULL)
    {
        if (current == item_in_list) 
        {
            item->prev = current->prev;
            item->next = current;
            if (current->next != NULL) 
            {
                current->prev->next = item;
                (*head)->counter++;
            }
            current->prev = item;
            return;
        }
        current = current->next;
    }

    fprintf(stderr, "L'elemento nella lista non è stato trovato\n");
}


int main(int argc, char** argv)
{
    struct int_list_node* head = NULL;
    struct int_list_node item;
    struct int_list_node item1;
    struct int_list_node item2;
    struct int_list_node item3;
    struct int_list_node item4;
    struct int_list_node item5;
    struct int_list_node item6;
    
    item.value = 100;
    item1.value = 111;
    item2.value = 122;
    item3.value = 133;
    item4.value = 144;
    item5.value = 155;
    item6.value = 166;

    printf("-------------------Appening items-----------------------\n");
    list_append(&head,get_list(item));
    list_append(&head,get_list(item1));
    list_append(&head,get_list(item2));
    printList(head);


    printf("---------------Insert after and before------------------\n");

    //insert_after_item(&head,get_list(item2),get_list(item3));
    
    //To check if ur asking fdor the firs item (head.prev = null)
    insert_before_item(&head,get_list(item),get_list(item4));
    printList(head);


    printf("---------------------Delete at index---------------------\n");

    //Remove item from double linked with and index
    deleteAtIndex(&head,2);
    printList(head);

    printf("------------------Delete at same item adress-------------------\n");

    //Remove item from double linked with and item
    remove_item_doubleLinked(&head,get_list(item));

    printList(head);

    return 0;
}
