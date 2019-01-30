void basicfill(int argc, t_node *stack, t_node **head)
{
    t_dir *dirent;
    DIR *dir;
    t_node* cursor;
	
	cursor = stack;
	while(cursor != NULL)
    {
        dir = opendir(cursor->name);
        while ((dirent = readdir(dir)) != NULL)
        {
            if (dirent->d_name[0] != '.')
				push(head, dirent->d_name);
        }
		outputdirname(cursor);
		MergeSort(head);
		printlist(*head);
		printsomething(stack);
		deleteList(head);
		cursor = cursor->next;
    }
    closedir(dir);
}

void fillA(int argc, t_node *stack, t_node **head)
{
    t_dir *dirent;
    DIR *dir;
    t_node* cursor;
	
	cursor = stack;
	while(cursor != NULL)
    {
        dir = opendir(cursor->name);
        while ((dirent = readdir(dir)) != NULL)
        {
				push(head, dirent->d_name);
        }
		outputdirname(cursor);
		MergeSort(head);
		//printsomething(*head);
		printlist(*head);
		deleteList(head);
		cursor = cursor->next;
    }
    closedir(dir);
}
void get_param(int argc, char **argv, t_node **stack, char *options)
{
    int i;
    t_dir *dirent;
    DIR *dir;

    i = get_options(options, argc, argv);
    if (i == argc)
        push(stack, ".");
    while (i < argc)
    {
        while(argv[i] != NULL)
        {    
            dir = opendir(argv[i]);
            if (dir != NULL)
                push(stack, argv[i]);
            if (dir == NULL)
                printf("%s : No such file or directory\n", argv[i]);
            i++;
        }
    }
}