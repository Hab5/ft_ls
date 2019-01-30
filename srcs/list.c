#include "../include/ft_ls.h"

void printlist(t_node* head)
{
    t_node* cursor;
    
    cursor = head;
    while(cursor != NULL)
    {
        ft_putstr(cursor->name);
        //printf("%lld", cursor->st_size);
        ft_putstr("\n");
        cursor = cursor->next;
    }
    ft_putstr("\n");
}

void push(t_node** head_ref, char *name) 
{ 
    t_node* new_node; 
    new_node = (t_node*)malloc(sizeof(t_node)); 
    new_node->name = name; 
    new_node->next = (*head_ref);  
    (*head_ref) = new_node;   
}


void deleteNode(t_node *head, t_node *cursor) 
{
   t_node *temp;
   t_node *ptr;
   
   temp = cursor;
   if (temp == NULL)
      printf("nothing to delete\n");
   else {
      if (temp == head) 
      {
         head = head->next;
         //free(temp);
      }
      else 
      {
         ptr = head;
         while (ptr->next != temp)
            ptr = ptr->next;
         ptr->next = temp->next;
         //free(temp);
      }
   }
}
 
void deleteList(t_node **head_ref) 
{ 
   t_node* cursor = *head_ref; 
   t_node* next; 
  
   while (cursor != NULL)  
   { 
       next = cursor->next; 
       free(cursor); 
       cursor = next; 
   } 
   *head_ref = NULL; 
} 