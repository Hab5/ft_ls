#include "../include/ft_ls.h"


int	ft_putstrfree(char *str)
{
	int len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		ft_putchar(str[len++]);
	free(str);
	return (len);
}


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

void print_id(t_pwd *pwd, t_grp *grp, t_stat st, int len[])
{
    pwd = getpwuid(st.st_uid);
    grp = getgrgid(st.st_gid);
    
    if(pwd != NULL)
        {
            pudding(pwd->pw_name, len[1]);
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
            pudding(grp->gr_name, len[2]);
            ft_putstr(grp->gr_name);
            ft_putstr("  ");
        }
    else
        {
            ft_putstr(ft_itoa(st.st_gid));
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

void print_minmajor(t_node *cursor, int size, int len[])
{
	int		min;
	int		maj;

	if (S_ISCHR(cursor->st.st_mode) || S_ISBLK(cursor->st.st_mode)) 
    {
        maj = major(cursor->st.st_rdev);
        min = minor(cursor->st.st_rdev);
    }
    pudding(ft_itoa(major(cursor->st.st_rdev)), len[4]);
    ft_putnbr(major(cursor->st.st_rdev));
    ft_putstr(", ");
    pudding(ft_itoa(minor(cursor->st.st_rdev)), len[5]);
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

void padcheck(t_node *cursor, t_pwd *pwd, t_grp *grp, int len[])
{
    char *temp;
    temp = ft_itoa(cursor->st.st_nlink);
    if(strlen(temp) > len[0])
        len[0] = strlen(temp);
    free(temp);
    if(strlen(pwd->pw_name) > len[1])
        len[1] = strlen(pwd->pw_name);
    if(strlen(grp->gr_name) > len[2])
        len[2] = strlen(grp->gr_name);
    temp = ft_itoa(cursor->st.st_size);
    if(strlen(temp) > len[3])
        len[3] = strlen(temp);
    free(temp);
    temp = ft_itoa(major(cursor->st.st_rdev));
    if(strlen(temp) > len[4])
        len[4] = strlen(temp);
    free(temp);
    temp = ft_itoa(minor(cursor->st.st_rdev));
    if(strlen(temp) > len[5])
        len[5] = strlen(temp);
    free(temp);
    len[6] += cursor->st.st_blocks;           
}

void pudding(char *str, int len)
{
    int i;
    
    i = 0;
    while(i++ < len - strlen(str))
        ft_putstr(" ");
}

void padding(t_node *head, char path[], int len[])
{ 
    t_node *cursor;
    t_pwd *pwd;
    t_grp *grp;
    char *temp;
    cursor = head;
    while(cursor != NULL)
    {
        temp = malloc(strlen(path) + strlen(cursor->name) + 1);
        ft_strcpy(temp, path);
        ft_strcat(temp, cursor->name);
        lstat(temp, &cursor->st);
        pwd = getpwuid(cursor->st.st_uid);
        grp = getgrgid(cursor->st.st_gid);
        padcheck(cursor, pwd, grp, len);
        free(temp);
        cursor = cursor->next;
    }
}

void print_long(t_node *cursor, char *filename, int len[])
{
    char *temp;
    lstat(filename, &cursor->st);
    print_access(cursor->st);
    temp = ft_itoa(cursor->st.st_nlink);
    pudding(temp, len[0]);
    ft_putstr(temp);
    free(temp);
    ft_putstr(" ");
    print_id(cursor->pwd, cursor->grp, cursor->st, len);
    if(S_ISCHR(cursor->st.st_mode) || S_ISBLK(cursor->st.st_mode))
        print_minmajor(cursor, cursor->st.st_size, len);
    else
    {
        temp = ft_itoa(cursor->st.st_size);
        pudding(temp, len[3]);
        ft_putstr(temp);
        free(temp);
    }
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
	int i;

    i = 0;
    lstcursor = head;
    int len[7] = {0};
    while(lstcursor != NULL)
	{
        lstcursor->path = malloc(strlen(path) + strlen(lstcursor->name) + 1);
        ft_strcpy(lstcursor->path, path);
        ft_strcat(lstcursor->path, lstcursor->name);
        padding(head, path, len);
		if (i++ == 0)
        {
            ft_putstr("total ");
            ft_putnbr(len[6]);
            ft_putstr("\n");
        }
        print_long(lstcursor, lstcursor->path, len);
        lstcursor = lstcursor->next;
	}
    ft_putstr("\n");
}