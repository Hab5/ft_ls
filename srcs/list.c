#include "../include/ft_ls.h"

void            printlist(t_node* head, char path[])
{
    t_node*     cursor;
    
    cursor = head;
    while(cursor != NULL)
    {
        cursor->path = malloc(strlen(path) + strlen(cursor->name) + 1);
        ft_strcpy(cursor->path, path);
        ft_strcat(cursor->path, cursor->name);
        ft_putstr(cursor->name);
        ft_putstr("\n");
        cursor = cursor->next;
    }
    ft_putstr("\n");
}

void            push(t_node **head_ref, char *name) 
{ 
    t_node      *new_node;
    char        *temp;
    
    new_node = (t_node*)malloc(sizeof(t_node)); 
    temp = ft_strdup(name);
    new_node->name = temp; 
    new_node->next = (*head_ref);  
    (*head_ref) = new_node;
}

void            listreverse(t_node **head_ref) 
{ 

    t_node      *prev; 
    t_node      *cursor;
    t_node      *next;

    prev = NULL;
    cursor = *head_ref;  
    while (cursor != NULL) 
    { 
        next  = cursor->next;   
        cursor->next = prev;    
        prev = cursor; 
        cursor = next; 
    } 
    *head_ref = prev;               
} 
 
void            deleteList(t_node **head_ref) 
{ 
    t_node       *cursor; 
    t_node       *next; 

    cursor = *head_ref;
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

void            deleteStack(t_node **head_ref) 
{ 
    t_node*     cursor; 
    t_node*     next; 
  
    cursor = *head_ref; 
    while (cursor != NULL)  
    { 
        next = cursor->next;
        free(cursor->name);
        free(cursor);
        cursor = next; 
    } 
    *head_ref = NULL; 
}
