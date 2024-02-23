/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:04:59 by kalam             #+#    #+#             */
/*   Updated: 2024/02/02 11:58:33 by kalam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_newline(t_list *link_list)
// find if there is a new line in the list.
// if yes then return 1 (means yes in boolean).
// if no, return 0 (means no in boolean).
{
	int		i;

	i = 0;
	if (!link_list)
		return (0);
	while (link_list->next)
		link_list = link_list->next;
	while (link_list->content[i])
	{
		if (link_list->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	total_len(t_list *link_list)
{
	int	len;
	int	i;

	len = 0;
	while (link_list)
	{
		i = 0;
		while (link_list->content[i])
		{
			len++;
			i++;
		}
		link_list = link_list->next;
	}
	return (len);
}

//after we found new line(\n) and that means finished the line,
//we need to call a fucntion to join existing link list's content together.

char	*join_str_from_link_list(t_list *link_list)
{
	int		i;
	int		j;
	char	*line;

	if ((!link_list) || (total_len(link_list) == 0))
		return (NULL);
	line = malloc(sizeof(char) * (total_len(link_list) + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (link_list)
	{
		j = 0;
		while (link_list->content[j] && link_list->content[j] != '\n')
			line[i++] = link_list->content[j++];
		if (link_list->content[j] == '\n')
		{
			line[i++] = link_list->content[j];
			break ;
		}
		link_list = link_list->next;
	}
	line[i] = '\0';
	return (line);
}

//after join the line, free the link list memory.

void	*clean_link_list(t_list **link_list)
{
	t_list	*temp;

	if (link_list)
	{
		while (*link_list)
		{
			free((*link_list)->content);
			temp = (*link_list)->next;
			free(*link_list);
			*link_list = temp;
		}
		*link_list = NULL;
	}
	return (NULL);
}
