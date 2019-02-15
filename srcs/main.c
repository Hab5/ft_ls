#include "../include/ft_ls.h"

t_node			*output_filestack(t_node *head, char options[], char path[])
{
    t_node		*cursor;

	int len[7] = {0};
    bzero(len, 7);
	if (!(options[0]))
	{
		printlist(head, path);
		free_filestack(&head);
	}
	else if (options[0])
	{
		get_filepath(&head, path, options);
		MergeSort(&head, path, options);
		padding(head, len);
		cursor = head;
		while(cursor != NULL)
    	{	
			print_long(cursor, len);
			cursor = cursor->next;
		}
	}
	deleteStack(&head);
	return (head);
}

t_node			*stacking(t_node *stack, t_node **head)
{
	t_node		*cursor;

	listreverse(head);
	cursor = *head;
	pop(&stack);
	while(cursor != NULL)
    {
		if(ft_strcmp(cursor->name, ".") != 0 &&
			ft_strcmp(cursor->name, "..") != 0)
		{
		if(S_ISDIR(cursor->st.st_mode))
			push(&stack, cursor->path);
		}
		cursor = cursor->next;
	}
	deleteList(head);
	return (stack);
}

void			fill_list(t_node *stack, t_node **head, char options[])
{
	t_dir		*dirent;
    DIR			*dir;
    
	deleteList(head);
	if(!(dir = opendir(stack->name)))
		return;
	if(options[2])
    {
		while ((dirent = readdir(dir)) != NULL)
			push(head, dirent->d_name);
	}
	if (!(options[2]))
	{
		while ((dirent = readdir(dir)) != NULL)
    	{
			if(dirent->d_name[0] != '.')
				push(head, dirent->d_name);
		}
	}
	closedir(dir);
}

t_node			*print_stack(t_node *stack, t_node *head, char options[], char path[])
{
	t_node		*cursor;
	
	cursor = stack;
	while(cursor != NULL)
    {
		ft_bzero(path, 1024);
		fill_list(cursor, &head, options);
		get_path(path, cursor->name);
		get_filepath(&head, path, options);
		MergeSort(&head, path, options);
		if (options[3])
			listreverse(&head);
		if (!(options[0]))
			printlist(head, path);
		if(options[0])
			print_all_long(head, path);
		if(options[1])
			stack = stacking(stack, &head);
		deleteList(&head);
	 	cursor = (options[1]) ? stack : cursor->next;
	}
	return(stack);
}

int				main(int argc, char **argv)
{
    char		options[5];
	char		path[1024];
    t_node		*head;
	t_node		*stack;
    
	head = NULL;
	stack = NULL;
	head = get_param(argc, argv, &stack, options);
	head = output_filestack(head, options, path);
	stack = print_stack(stack, head, options, path);
	deleteStack(&stack);
    return 0;
}
