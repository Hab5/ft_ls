#include "../include/ft_ls.h"
#include<stdio.h> 
#include<stdlib.h>
#include <string.h>

int MergeSort(t_node** headRef) 
{ 
	t_node* head; 
	t_node* a; 
	t_node* b;

    head = *headRef;
    if ((head == NULL) || (head->next == NULL)) 
    	return (0); 

	FrontBackSplit(head, &a, &b);
	MergeSort(&a); 
	MergeSort(&b);
	*headRef = SortedMerge(a, b);
    return (0);
}

t_node* SortedMerge(t_node* a, t_node* b) 
{ 
	t_node* result;
    
    result = NULL; 
  
	if (a == NULL) 
    	return(b); 
	else if (b == NULL) 
    	return(a); 
	if (strcmp(a->name, b->name) < 0)
	{ 
    	result = a; 
    	result->next = SortedMerge(a->next, b); 
	} 
	else
	{ 
    	result = b; 
    	result->next = SortedMerge(a, b->next); 
	} 
	return(result); 
} 

void FrontBackSplit(t_node* source, t_node** frontRef, t_node** backRef) 
{ 
    t_node* fast; 
	t_node* slow; 

    slow = source; 
    fast = source->next; 
    while (fast != NULL) 
    { 
        fast = fast->next; 
        if (fast != NULL) 
        { 
            slow = slow->next; 
            fast = fast->next; 
        }
    }
    *frontRef = source; 
    *backRef = slow->next; 
    slow->next = NULL;  
}