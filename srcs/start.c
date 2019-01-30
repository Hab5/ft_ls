#include "../include/ft_ls.h"

t_node *clean_stack(t_node *stack, t_node **head)
{
	t_node *cursor;
	cursor = stack;
	while(cursor != NULL)
	{
		stat(cursor->name, &cursor->st);
		if (S_ISREG(cursor->st.st_mode) == 1)
		{
			push(head, cursor->name);
			deleteNode(stack, cursor); //printf("file : %s\n", cursor->name);
		}
		cursor = cursor->next;
	}
	if (S_ISREG(stack->st.st_mode) == 1)
		stack = stack->next;
	printf("\nCLEAN STACK :\n");
	MergeSort(&stack);
	MergeSort(head);
	printlist(stack);
	return (stack);
}

t_node *output_filestack(t_node *head, char options[])
{
    t_node* cursor;
	
	cursor = head;
	if (options[0] == 0)
		printlist(head);
	else if (options[0] != 0)
	{
		while(cursor != NULL)
    	{
			print_long(cursor, cursor->name);
			cursor = cursor->next;
		}
	}
	deleteList(&head);
	return (head);
}