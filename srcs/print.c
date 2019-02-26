/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:13:03 by mbellaic          #+#    #+#             */
/*   Updated: 2019/02/26 14:13:07 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void		padcheck(t_node *cursor, t_pwd *pwd, t_grp *grp, int len[])
{
	char	*temp;

	temp = ft_itoa(cursor->st.st_nlink);
	if ((int)ft_strlen(temp) > len[0])
		len[0] = ft_strlen(temp);
	free(temp);
	if ((int)ft_strlen(pwd->pw_name) > len[1])
		len[1] = ft_strlen(pwd->pw_name);
	if ((int)ft_strlen(grp->gr_name) > len[2])
		len[2] = ft_strlen(grp->gr_name);
	temp = ft_itoa(cursor->st.st_size);
	if ((int)ft_strlen(temp) > len[3])
		len[3] = ft_strlen(temp);
	free(temp);
	temp = ft_itoa(major(cursor->st.st_rdev));
	if ((int)ft_strlen(temp) > len[4])
		len[4] = ft_strlen(temp);
	free(temp);
	temp = ft_itoa(minor(cursor->st.st_rdev));
	if ((int)ft_strlen(temp) > len[5])
		len[5] = ft_strlen(temp);
	free(temp);
}

void		pudding(char *str, int len)
{
	int		i;

	i = 0;
	while (i++ < len - (int)ft_strlen(str))
		ft_putstr(" ");
}

void		padding(t_node *head, int len[])
{
	t_node	*cursor;
	t_pwd	*pwd;
	t_grp	*grp;

	cursor = head;
	len[0] = 0;
	len[1] = 0;
	len[2] = 0;
	len[3] = 0;
	len[4] = 0;
	len[5] = 0;
	len[6] = 0;
	while (cursor != NULL)
	{
		pwd = getpwuid(cursor->st.st_uid);
		grp = getgrgid(cursor->st.st_gid);
		padcheck(cursor, pwd, grp, len);
		len[6] += cursor->st.st_blocks;
		cursor = cursor->next;
	}
}

void		print_long(t_node *cursor, int len[])
{
	char	*temp;

	print_access(cursor->st);
	temp = ft_itoa(cursor->st.st_nlink);
	pudding(temp, len[0]);
	ft_putstr(temp);
	free(temp);
	ft_putstr(" ");
	print_id(cursor->pwd, cursor->grp, cursor->st, len);
	if (S_ISCHR(cursor->st.st_mode) || S_ISBLK(cursor->st.st_mode))
		print_minmajor(cursor, len);
	else
	{
		temp = ft_itoa(cursor->st.st_size);
		pudding(temp, len[3]);
		ft_putstr(temp);
		free(temp);
	}
	ft_putstr(" ");
	print_date(ctime(&cursor->st.st_mtime));
	if (S_ISLNK(cursor->st.st_mode))
		print_link(cursor);
	else
		ft_putstr(cursor->name);
	ft_putstr("\n");
}

void		print_all_long(t_node *head, char path[])
{
	t_node	*lstcursor;
	int		len[7];
	int		i;

	i = 0;
	lstcursor = head;
	bzero(len, 7);
	padding(head, len);
	while (lstcursor != NULL)
	{
		lstcursor->path = malloc(ft_strlen(path) + \
						ft_strlen(lstcursor->name) + 1);
		ft_strcpy(lstcursor->path, path);
		ft_strcat(lstcursor->path, lstcursor->name);
		if (i++ == 0)
		{
			ft_putstr("total ");
			ft_putnbr(len[6]);
			ft_putstr("\n");
		}
		print_long(lstcursor, len);
		lstcursor = lstcursor->next;
	}
	ft_putstr("\n");
}
