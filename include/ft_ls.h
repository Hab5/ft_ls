/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 13:27:52 by mbellaic          #+#    #+#             */
/*   Updated: 2019/02/26 13:27:56 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include "../libft/libft.h"

# define MAJOR(x)((int32_t)(((u_int32_t)(x) >> 24) & 0xff))
# define MINOR(x)((int32_t)((x) & 0xffffff))

typedef struct dirent	t_dir;
typedef struct stat		t_stat;
typedef struct timespec	t_time;
typedef struct passwd	t_pwd;
typedef struct group	t_grp;

typedef struct			s_node
{
	char				*name;
	char				*path;
	t_pwd				*pwd;
	t_grp				*grp;
	t_stat				st;
	struct s_node		*next;

}						t_node;

void					check_options(char *options, char *current);
int						get_options(char *options, int argc, char **argv);
t_node					*get_param(int argc, char **argv, t_node **stack, \
															char options[]);
int						file_exist (char *filename);
t_node					*sort_param(int argc, char **argv, t_node *stack, \
															char options[]);

t_node					*clean_stack(t_node *stack, t_node **head);
t_node					*output_filestack(t_node *head, char options[], \
															char path[]);

void					printlist(t_node *head, char path[]);
void					push(t_node **head_ref, char *name);
void					listreverse(t_node **head_ref);
void					pop(t_node **head);
void					deletelist(t_node **head_ref);
void					deletestack(t_node **head_ref);

int						merge_sort(t_node **headref, char path[], \
													char options[]);
t_node					*sortedmerge(t_node *a, t_node *b);
t_node					*sortedmerge_time(t_node *a, t_node *b);
void					frontback_split(t_node *source, t_node **frontref, \
														t_node **backref);

void					print_access(t_stat st);
void					print_id(t_pwd *pwd, t_grp *grp, t_stat st, int len[]);
void					print_date(char *ctime);
void					print_minmajor(t_node *cursor, int len[]);
void					print_link(t_node *head);
void					print_long(t_node *cursor, int len[]);
void					print_all_long(t_node *head, char path[]);

void					padding(t_node *head, int len[]);
void					padcheck(t_node *cursor, t_pwd *pwd, t_grp *grp, \
															int len[]);
void					pudding(char *str, int len);

void					free_filestack(t_node **head);
void					get_filepath(t_node **head, char path[], \
												char options[]);
char					*get_path(char path[], char *filename);
void					ft_pustrless(const char *str);
void					flags_error(char *current, int i);

#endif
