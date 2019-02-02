#include "../include/ft_ls.h"
#include <errno.h>
t_node *clean_stack(t_node *stack, t_node **head)
{
	t_node *cursor;
	cursor = stack;
	while(cursor != NULL)
	{
		if (stat(cursor->name, &cursor->st) || !(S_ISDIR(cursor->st.st_mode) == 1))
		{
			push(head, cursor->name);
			deleteNode(stack, cursor); //printf("file : %s\n", cursor->name);
		}
		cursor = cursor->next;
	}
	if (!(S_ISDIR(stack->st.st_mode) == 1))
		stack = stack->next;
	MergeSort(&stack);
	MergeSort(head);
	return (stack);
}

void test(int len[])
{
	len[0] = 0;
	len[1] = 1;
	len[2] = 2;
	len[3] = 3;
}

t_node *output_filestack(t_node *head, char options[], char path[])
{
    t_node* cursor;
	static int i;
	i=0;

	int len[6] = {0};
	cursor = head;
	if (options[0] == 0)
		printlist(head);
	else if (options[0] != 0)
	{
		while(cursor != NULL)
    	{	
			path = "\0";
			stat(cursor->name, &cursor->st);
			padding(head, path, len);
			print_long(cursor, cursor->name, len);
			cursor = cursor->next;
		}
	}
	deleteList(&head);
	return (head);
}