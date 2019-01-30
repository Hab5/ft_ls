#include "../include/ft_ls.h"

void check_options(char *options, char *current)
{
    int i;

    i = 1;
    while(current[i] != '\0')
    {
        if (current[i] == 'l')
            options[0]= '1';
        else if (current[i] == 'R')
            options[1] = '1';
        else if (current[i] == 'a')
            options[2] = '1';
        else if (current[i] == 'r')
            options[3] = '1';
        else if (current[i] == 't')
            options[4] = '1';
        else
        {
            flags_error(current, i);
            exit(0);
        }
        i++;
    }
}

int get_options(char *options, int argc, char **argv)
{
    int i;
    i = 1;
    ft_bzero(options, 5);

    while (i < argc && argv[i][0] == '-' && argv[i][1] != '\0')
        {
           check_options(options, argv[i]);
           i++;
        }
    return (i);
}

int file_exist(char *filename)
{
    struct stat buf;
    return (stat(filename, &buf) == 0);
}

void get_param(int argc, char **argv, t_node **stack, int current)
{

    if (argc  <= current)
        push(stack, ".");
    while (argc > current)
    {
        push(stack, argv[argc - 1]);
        argc--;
    }
}

t_node *sort_param(int argc, char **argv, t_node *stack, char options[])
{
	int current;
	t_node *cursor;
	
	current = get_options(options, argc, argv);
	get_param(argc, argv, &stack, current);
	cursor = stack;
	while (cursor != NULL)
	{
		if(file_exist(cursor->name) != 1)
		{
			deleteNode(stack, cursor);
			ft_putstr("ls: ");
			ft_putstr(cursor->name);
			ft_putstr(": No such file or directory\n");
		}
		cursor = cursor->next;
	}
	if (file_exist(stack->name) != 1)
		stack = stack->next;
    if (!(stack))
        exit(0);
	return (stack);
}