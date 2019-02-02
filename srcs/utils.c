#include "../include/ft_ls.h"

void flags_error(char *current, int i)
{
    ft_putstr("ls: illegal option -- ");
	ft_putchar(current[i]);
	ft_putstr("\nusage: ls [-Ralrt] [file ...]\n");
}

void ft_pustrless(const char *str)
{
	int i;

	i = 0;
	while(str[i+1] != '\0')
		ft_putchar(str[i++]);
}

char *get_path(char path[], char *filename)
{
	ft_strcat(path, filename);
	ft_strcat(path, "/");
	ft_putstr("\n");
	ft_pustrless(path);
	ft_putstr(":\n");
	//printf("\n%s\n", path);
	return(path);
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