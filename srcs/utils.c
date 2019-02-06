#include "../include/ft_ls.h"

void			flags_error(char *current, int i)
{
	ft_putstr("\x1B[1;31m");
    ft_putstr("ls: illegal option -- ");
	ft_putchar(current[i]);
	ft_putstr("\nusage: ls [-Ralrt] [file ...]\n");
	ft_putstr("\x1B[0m");
}

void			ft_pustrless(const char *str)
{
	int			i;

	i = 0;
	ft_putstr("\x1B[1;31m");
	while(str[i+1] != '\0')
		ft_putchar(str[i++]);
}

char			*get_path(char path[], char *filename)
{
	if(ft_strcmp(filename, ".") != 0)
	{
		ft_strcat(path, filename);
		ft_strcat(path, "/");
		ft_pustrless(path);
		ft_putstr(":\n\x1b[0m");
	}
	return(path);
}

void			get_filepath(t_node **head, char path[])
{
	t_node		*lstcursor;
	char		*temp;

	lstcursor = *head;
    while(lstcursor != NULL)
	{
		temp = malloc(strlen(path) + strlen(lstcursor->name) + 1);
        ft_strcpy(temp, path);
        ft_strcat(temp, lstcursor->name);
		lstcursor->path = temp;
		stat(lstcursor->path, &lstcursor->st);
		free(temp);
		lstcursor = lstcursor->next;
	}
}

void			pop(t_node **head)
{
    if (*head != NULL) 
    {
        t_node *node = *head;
		free(node->name);
        *head = (*head)->next;
        free(node);
    }
}
