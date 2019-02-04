#include "../include/ft_ls.h"

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
        // temp = malloc(strlen(path) + strlen(cursor->name) + 1);
        // ft_strcpy(temp, path);
        // ft_strcat(temp, cursor->name);
        lstat(cursor->path, &cursor->st);
        pwd = getpwuid(cursor->st.st_uid);
        grp = getgrgid(cursor->st.st_gid);
        padcheck(cursor, pwd, grp, len);
        len[6] += cursor->st.st_blocks;
        //free(temp);
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