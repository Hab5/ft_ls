#ifndef FT_H
# define FT_H

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "../libft/libft.h"

# define MAJOR(x)((int32_t)(((u_int32_t)(x) >> 24) & 0xff))
# define MINOR(x)((int32_t)((x) & 0xffffff))

typedef struct dirent	t_dir;
typedef struct stat		t_stat;
typedef struct timespec	t_time;
typedef struct passwd	t_pwd;
typedef struct group	t_grp;

typedef struct          s_node
{
    char                *name;
	char			    *path;
	t_pwd			    *pwd;
    t_grp			    *grp;
	t_stat			    st;
    struct              s_node *next;

}                       t_node;

void                    check_options(char *options, char *current);
int                     get_options(char *options, int argc, char **argv);
t_node                  *get_param(int argc, char **argv, t_node **stack, char options[]);
int                     file_exist (char *filename);
t_node                  *sort_param(int argc, char **argv, t_node *stack, char options[]);

t_node                  *clean_stack(t_node *stack, t_node **head);
t_node                  *output_filestack(t_node *head, char options[], char path[]);

void                    printlist(t_node *head, char path[]);
void                    push(t_node **head_ref, char *name);
void                    pushBack(t_node **head, char *name);
void                    listreverse(t_node **head_ref); 
void                    pop(t_node **head);
void                    deleteList(t_node **head_ref);
void                    deleteStack(t_node **head_ref);

int                     MergeSort(t_node** headRef, char path[] ,char options[]);
t_node*                 SortedMerge(t_node* a, t_node* b);
t_node*                 SortedMergeTime(t_node* a, t_node* b);
void                    FrontBackSplit(t_node* source, t_node** frontRef, t_node** backRef);

void                    print_access(t_stat st);
void                    print_id(t_pwd *pwd, t_grp *grp, t_stat st, int len[]);
void                    print_date(char *ctime);
void                    print_minmajor(t_node *cursor, int len[]);
void                    print_link(t_node *head);
void                    print_long(t_node *cursor, int len[]);
void                    print_all_long(t_node *head, char path[]);

void                    padding(t_node *head, int len[]);
void                    padcheck(t_node *cursor, t_pwd *pwd, t_grp *grp, int len[]);
void                    pudding(char *str, int len);

void                    free_filestack(t_node **head);
void                    get_filepath(t_node **head, char path[]);
char                    *get_path(char path[], char *filename);
void                    ft_pustrless(const char *str);
void                    flags_error(char *current, int i);

#endif