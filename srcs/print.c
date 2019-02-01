#include "../include/ft_ls.h"

void	print_access(t_stat st)
{
	ft_putchar((S_ISFIFO(st.st_mode)) ? 'p' : '\0');
	ft_putchar((S_ISCHR(st.st_mode)) ? 'c' : '\0');
	ft_putchar((S_ISDIR(st.st_mode)) ? 'd' : '\0');
	ft_putchar((S_ISBLK(st.st_mode)) ? 'b' : '\0');
	ft_putchar((S_ISREG(st.st_mode)) ? '-' : '\0');
	ft_putchar((S_ISLNK(st.st_mode)) ? 'l' : '\0');
	ft_putchar((S_ISSOCK(st.st_mode)) ? 's' : '\0');
	ft_putchar((st.st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((st.st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((st.st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((st.st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((st.st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((st.st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((st.st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((st.st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((st.st_mode & S_IXOTH) ? 'x' : '-');
	ft_putstr("  ");
}

void print_id(t_pwd *pwd, t_grp *grp, t_stat st)
{
    pwd = getpwuid(st.st_uid);
    grp = getgrgid(st.st_gid);
    
    if(pwd != NULL)
        {
            ft_putstr(pwd->pw_name);
            ft_putstr("  ");
        }
    else
        {
            ft_putstr(ft_itoa(st.st_uid));
            ft_putstr("  ");
        }
    if(grp != NULL)
        {
            ft_putstr(grp->gr_name);
            ft_putstr("  ");
        }
    else
        {
            ft_putstr(ft_itoa(st.st_uid));
            ft_putstr("  ");
        }
}

void print_date(char *ctime)
{
    int i;
    
    i = 0;
    ctime += 4;
    ctime[12] = '\0';
    ft_putstr(ctime);
    ft_putstr(" ");
}

void print_minmajor(t_node *cursor, int size)
{
	int		min;
	int		maj;

	if (S_ISCHR(cursor->st.st_mode) || S_ISBLK(cursor->st.st_mode)) 
    {
        maj = major(cursor->st.st_rdev);
        min = minor(cursor->st.st_rdev);
    }
    ft_putnbr(major(cursor->st.st_rdev));
    ft_putstr(", ");
    ft_putnbr(minor(cursor->st.st_rdev));
}

void print_link(t_node *head)
{
	char	buf[1024];
	int		len;

	ft_putstr(head->name);
	ft_putstr(" -> ");
	len = readlink(head->path, buf, sizeof(buf));
	buf[len] = '\0';
	ft_putstr(buf);
}

void print_long(t_node *cursor, char *filename)
{
    lstat(filename, &cursor->st);
    print_access(cursor->st);
    ft_putstr(ft_itoa(cursor->st.st_nlink));
    ft_putstr(" ");
    print_id(cursor->pwd, cursor->grp, cursor->st);
    if(S_ISCHR(cursor->st.st_mode) || S_ISBLK(cursor->st.st_mode))
        print_minmajor(cursor, cursor->st.st_size);
    else
        ft_putstr(ft_itoa(cursor->st.st_size));
    ft_putstr(" ");
    print_date(ctime(&cursor->st.st_mtime));
    if(S_ISLNK(cursor->st.st_mode))
        print_link(cursor);
    else
        ft_putstr(cursor->name);
    ft_putstr("\n");
}

void print_all_long(t_node *head, char path[])
{
	t_node *lstcursor;
    char *filepath;
	lstcursor = head;
    while(lstcursor != NULL)
	{
        lstcursor->path = malloc(strlen(path) + strlen(lstcursor->name) + 1);
        ft_strcpy(lstcursor->path, path);
        ft_strcat(lstcursor->path, lstcursor->name);
		print_long(lstcursor, lstcursor->path);
        lstcursor = lstcursor->next;
	}
}

/*int main()
{
    t_node *list = NULL;
    push(&list, "a.out");
    t_node* cursor;
    
    cursor = list;
    print_long(cursor);
    return 0;
}*/