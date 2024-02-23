/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:26:23 by kalam             #+#    #+#             */
/*   Updated: 2024/02/22 19:40:04 by kalam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// read the line from fd to buf,
// pass the buf to another function to add to the link list.

t_list	*readline_linklist(int byte_read, char *buf, t_list **link_list)
{
	char	*content;
	int		i;
	int		content_len;

	content_len = 0;
	while (content_len < byte_read && buf[content_len])
		content_len++;
	content = malloc(sizeof(char) * (content_len + 1));
	if (!content)
		return (NULL);
	i = 0;
	while (i < content_len)
	{
		content[i] = buf[i];
		i++;
	}
	content[i] = '\0';
	return (add_content_to_link_list(content, link_list));
}

// add the buff to the end of the link list
// or set it as the link list itself if the link list is empty

t_list	*add_content_to_link_list(char *content, t_list **link_list)
{
	t_list	*new;
	t_list	*temp;

	temp = NULL;
	new = malloc(sizeof(t_list));
	if (!new || !link_list || !content)
		return (NULL);
	new->content = content;
	new->next = NULL;
	if (!*link_list)
	{
		*link_list = new;
		return (*link_list);
	}
	temp = *link_list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (*link_list);
}

// as the buff may contain the first few letters of next line,
// store the string after new line ('\n') in the static variable.

t_list	*str_after_newline(t_list *link_list, t_list **new)
{
	int		i;
	int		len;
	char	*leftover;

	i = 0;
	len = 0;
	*new = NULL;
	while (link_list->next)
		link_list = link_list->next;
	while (link_list->content[len])
		len++;
	while (link_list->content[i] && link_list->content[i] != '\n')
		i++;
	if (link_list->content[i] == '\n')
		i++;
	leftover = malloc(sizeof(char) * (len - i + 1));
	if (!leftover)
		return (NULL);
	len = 0;
	while (link_list->content[i])
		leftover[len++] = link_list->content[i++];
	leftover[len] = '\0';
	return (add_content_to_link_list(leftover, new));
}

void	update_linklist(t_list **link_list, int fd, char *buf)
{
	int	byte_read;

	while (!found_newline(*link_list))
	{
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (byte_read <= 0)
			break ;
		if (!readline_linklist(byte_read, buf, link_list))
			clean_link_list(link_list);
	}
}

// the body of the function, connect everything by allocate memory
// keep checking if the link list has \n, if no, keep doing following
// 1. add a new link list node;
// 2. copy the buf to link list content
// if yes, string join the whole link list before the \n,
// then, if there is anything after \n (means it is no EOF),
// store it in the static variable

char	*get_next_line(int fd)
{
	char			*buf;
	char			*this_line;
	static t_list	*link_list;
	t_list			*new_list;

	buf = malloc(sizeof(char) * BUFFER_SIZE);
	if (fd < 0 || BUFFER_SIZE < 0 || !buf)
	{
		free(buf);
		return (NULL);
	}
	update_linklist(&link_list, fd, buf);
	this_line = join_str_from_link_list(link_list);
	if (!this_line || !str_after_newline(link_list, &new_list))
	{
		free(this_line);
		free(buf);
		return (clean_link_list(&link_list));
	}
	clean_link_list(&link_list);
	link_list = new_list;
	free(buf);
	return (this_line);
}
