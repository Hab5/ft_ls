/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:15:54 by mbellaic          #+#    #+#             */
/*   Updated: 2019/02/26 14:15:56 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int			merge_sort(t_node **head_ref, char path[], char options[])
{
	t_node	*head;
	t_node	*a;
	t_node	*b;

	head = *head_ref;
	if ((head == NULL) || (head->next == NULL))
		return (0);
	frontback_split(head, &a, &b);
	merge_sort(&a, path, options);
	merge_sort(&b, path, options);
	if (!options[4])
		*head_ref = sortedmerge(a, b);
	if (options[4])
		*head_ref = sortedmerge_time(a, b);
	return (0);
}

t_node		*sortedmerge(t_node *a, t_node *b)
{
	t_node	*result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (ft_strcmp(a->name, b->name) < 0)
	{
		result = a;
		result->next = sortedmerge(a->next, b);
	}
	else
	{
		result = b;
		result->next = sortedmerge(a, b->next);
	}
	return (result);
}

t_node		*sortedmerge_time(t_node *a, t_node *b)
{
	t_node	*result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (a->st.st_mtime > b->st.st_mtime)
	{
		result = a;
		result->next = sortedmerge_time(a->next, b);
	}
	else
	{
		result = b;
		result->next = sortedmerge_time(a, b->next);
	}
	return (result);
}

void		frontback_split(t_node *source, t_node **frontref, t_node **backref)
{
	t_node	*fast;
	t_node	*slow;

	slow = source;
	fast = source->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*frontref = source;
	*backref = slow->next;
	slow->next = NULL;
}
