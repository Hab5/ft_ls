#include "../include/ft_ls.h"

void printlist(t_node* head)
{
    t_node* cursor;
    
    cursor = head;
    while(cursor != NULL)
    {
        ft_putstr(cursor->name);
        ft_putstr("\n");
        cursor = cursor->next;
    }
    ft_putstr("\n");
}

void push(t_node **head_ref, char *name) 
{ 
    t_node* new_node;
    char *temp;
    
    new_node = (t_node*)malloc(sizeof(t_node)); 
    temp = strdup(name);
    new_node->name = temp; 
    new_node->next = (*head_ref);  
    (*head_ref) = new_node;
}

void listreverse(t_node **head_ref) 
{ 

    t_node* prev = NULL; 
    t_node* current = *head_ref; 
    t_node* next; 
    while (current != NULL) 
    { 
        next  = current->next;   
        current->next = prev;    
        prev = current; 
        current = next; 
    } 
    *head_ref = prev;               
} 
 
void deleteList(t_node **head_ref) 
{ 
   t_node* cursor = *head_ref; 
   t_node* next; 
  
   while (cursor != NULL)  
   { 
        next = cursor->next;
        free(cursor->name);
        free(cursor->path);
        free(cursor); 
        cursor = next; 
   } 
   *head_ref = NULL; 
}

void deleteStack(t_node **head_ref) 
{ 
   t_node* cursor = *head_ref; 
   t_node* next; 
  
   while (cursor != NULL)  
   { 
        next = cursor->next;
        free(cursor->name);
        free(cursor);
        cursor = next; 
   } 
   *head_ref = NULL; 
}