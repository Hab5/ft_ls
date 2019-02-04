#include "../include/ft_ls.h"

void check_options(char *options, char *current)
{
    int i;

    i = 1;
    while(current[i] != '\0')
    {
        if (current[i] == 'l')
            options[0] = '1';
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

t_node *get_param(int argc, char **argv, t_node **stack, char options[])
{
    t_node *head;
    int current;
    t_stat st;

    current = get_options(options, argc, argv);
    head = NULL;
    if (argc <= current)
            push(stack, ".");
    while (argc > current)
    {   
        stat(argv[argc - 1], &st);

        if (file_exist(argv[argc - 1]) == 1 && (S_ISDIR(st.st_mode)))
            push(stack, argv[argc - 1]);

        else if(file_exist(argv[argc - 1]) == 1 && !(S_ISDIR(st.st_mode)))
            push(&head, argv[argc - 1]);
        else
        {
            ft_putstr("\x1B[31mls: ");
			ft_putstr(argv[argc-1]);
			ft_putstr(": No such file or directory\x1B[0m\n");
        }
        argc--;
    }
    return (head);
}

void free_filestack(t_node **head)
{
    t_node *cursor;

    cursor = *head;
    while(cursor != NULL)
    {
        free(cursor->path);
        cursor = cursor->next;
    }
}