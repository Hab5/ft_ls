#include "../include/ft_ls.h"

void        print_access(t_stat st)
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

void        print_id(t_pwd *pwd, t_grp *grp, t_stat st, int len[])
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

void        print_date(char *ctime)
{
    int     i;
    
    i = 0;
    ctime += 4;
    ctime[12] = '\0';
    ft_putstr(ctime);
    ft_putstr(" ");
}

void        print_minmajor(t_node *cursor, int len[])
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

void        print_link(t_node *head)
{
	char	buf[1024];
	int		len;

	ft_putstr(head->name);
	ft_putstr(" -> ");
	len = readlink(head->path, buf, sizeof(buf));
	buf[len] = '\0';
	ft_putstr(buf);
}
