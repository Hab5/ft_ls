#include "../include/ft_ls.h"

char *get_path(char path[], char *filename)
{
	ft_strcat(path, filename);
	ft_strcat(path, "/");
	printf("\n%s\n", path);
	return(path);
}

int pop( t_node **head )
{
    if ( *head != NULL ) 
    {
        t_node *node = *head;
        *head = ( *head )->next;
        free( node );
        return 1;
    }
    else
    {
        return 2;
    }
}

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

t_node *grab_filepath(char path[], t_node *stack, t_node *head)
{
	t_node *lstcursor;

	lstcursor = head;
    while(lstcursor != NULL)
	{
		lstcursor->path = malloc(strlen(path) + strlen(lstcursor->name) + 1);
        ft_strcpy(lstcursor->path, path);
        ft_strcat(lstcursor->path, lstcursor->name);
		stat(lstcursor->path, &lstcursor->st);
		lstcursor = lstcursor->next;
	}
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
    t_node *head;
	t_node *stack;
	char path[1024];
    
	head = NULL;
	stack = NULL;
	stack = sort_param(argc, argv, stack, options);// at this point, stack contains files
	stack = clean_stack(stack, &head); // not anymore
	head = output_filestack(head, options);
	stack = print_stack(stack, head, options, path);
	
	//pop(&stack);
	// printf("\nFULL STACK : \n");
	// printlist(stack);
	
	
	
	
	printf("\noptions : %c, %c, %c, %c, %c\n", options[0], options[1], options[2], options[3], options[4]);
    return 0;
}