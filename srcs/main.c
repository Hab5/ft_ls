#include "../include/ft_ls.h"

void get_path(char path[], char *filename)
{
	ft_strcat(path, filename);
	ft_strcat(path, "/");
	printf("\n%s\n", path);

}

t_node *fill_list(t_node *stack, t_node *head, char options[])
{
	t_dir *dirent;
    DIR *dir;
    
	dir = opendir(stack->name);
	if(options[2] != 0)
    {
		while ((dirent = readdir(dir)) != NULL)
    	{
			push(&head, dirent->d_name);
    	}
	}
	if (!(options[2] != 0))
	{
		while ((dirent = readdir(dir)) != NULL)
    	{
			if(dirent->d_name[0] != '.')
				push(&head, dirent->d_name);
		}
	}
	return (head);
}

t_node *print_stack(t_node *stack, t_node *head, char options[], char path[])
{
	t_node *cursor;
	
	cursor = stack;
	while(cursor != NULL)
    {
		ft_bzero(path, 1024);
		if (!(options[0] != 0))
		{
			head = fill_list(cursor, head, options);
			MergeSort(&head);
			printlist(head);
			deleteList(&head);
		}
		if(options[0] != 0)
		{
			head = fill_list(cursor, head, options);
			MergeSort(&head);
			get_path(path, cursor->name);
			print_all_long(head, path);
			deleteList(&head);
		}
		cursor = cursor->next;
	}
	return(head);
}

int main(int argc, char **argv)
{
    char options[5];
    t_node *head;
	t_node *stack;

	char path[1024];
	ft_bzero(path, 1024);
    
	head = NULL;
	stack = NULL;
	stack = sort_param(argc, argv, stack, options);// at this point, stack contains files
	stack = clean_stack(stack, &head); // not anymore
	head = output_filestack(head, options);
	print_stack(stack, head, options, path);
    printf("\noptions : %c, %c, %c, %c, %c\n", options[0], options[1], options[2], options[3], options[4]);
    return 0;
}