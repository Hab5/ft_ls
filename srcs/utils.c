#include "../include/ft_ls.h"

void flags_error(char *current, int i)
{
    ft_putstr("ls: illegal option -- ");
	ft_putchar(current[i]);
	ft_putstr("\nusage: ls [-Ralrt] [file ...]\n");
}

void outputdirname(t_node *cursor)
{
	//if(ft_strcmp(cursor->name, ".") > 0 && cursor->next != NULL)
	//{
		ft_putstr(cursor->name);
		ft_putstr(": \n");
	//}
}