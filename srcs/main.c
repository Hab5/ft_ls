#include "../include/ft_ls.h"

t_node *fill_list(t_node *stack, t_node *head, char options[])
{
	t_dir *dirent;
    DIR *dir;
    
	if(!(dir = opendir(stack->name)))
		ft_putstr("Operation not permitted\n");
	deleteList(&head);
	if(options[2])
    {
		while ((dirent = readdir(dir)) != NULL)
			push(&head, ft_strdup(dirent->d_name));
	}
	if (!(options[2]))
	{
		while ((dirent = readdir(dir)) != NULL)
    	{
			if(dirent->d_name[0] != '.')
				push(&head, ft_strdup(dirent->d_name));
		}
	}
	closedir(dir);
	return (head);
}

t_node *stacking(t_node *stack, t_node *head)
{
	t_node *cursor;

	listreverse(&head);
	cursor = head;
	pop(&stack);
	while(cursor != NULL)
    {
		if(strcmp(cursor->name, ".") != 0 &&
			strcmp(cursor->name, "..") != 0)
		{
		if(S_ISDIR(cursor->st.st_mode))
			push(&stack, ft_strdup(cursor->path));
		}
		cursor = cursor->next;
	}
	return (stack);
}

t_node *print_stack(t_node *stack, t_node *head, char options[], char path[])
{
	t_node *cursor;
	cursor = stack;
	int len[4] = {[0] = 4};
	while(cursor != NULL)
    {
		ft_bzero(path, 1024);
		head = fill_list(cursor, head, options);
		MergeSort(&head);
		get_path(path, cursor->name);
		
		if (!(options[0]))
		{
			head = grab_filepath(path, cursor, head);
			printlist(head);
		}
		if(options[0])
			print_all_long(head, path);
		if(options[1] != 0)
			stack = stacking(stack, head);
	 	cursor = (options[1]) ? stack : cursor->next;
	}
	return(stack);
}

int main(int argc, char **argv)
{
    char options[5];
	char path[1024];
    t_node *head;
	t_node *stack;
    
	head = NULL;
	stack = NULL;
	stack = sort_param(argc, argv, stack, options);// at this point, stack contains files
	stack = clean_stack(stack, &head); // not anymore
	head = output_filestack(head, options, path);
	stack = print_stack(stack, head, options, path);
	
	//pop(&stack);
	// printf("\nFULL STACK : \n");
	// printlist(stack);
	
	
	
	
	printf("\noptions : %c, %c, %c, %c, %c\n", options[0], options[1], options[2], options[3], options[4]);
    return 0;
}