/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:02:38 by kalam             #+#    #+#             */
/*   Updated: 2024/02/02 12:13:10 by kalam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <fcntl.h> //def open
# include <stdlib.h> //def malloc + free
# include <unistd.h> // def read
# include <stddef.h> //def size_t
# include <stdio.h> //def printf

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

int			found_newline(t_list *link_list);
int			total_len(t_list *link_list);
t_list		*readline_linklist(int byte_read, char *buf, t_list **link_list);
t_list		*add_content_to_link_list(char *content, t_list **link_list);
char		*join_str_from_link_list(t_list *link_list);
void		*clean_link_list(t_list **link_list);
t_list		*str_after_newline(t_list *link_list, t_list **new);
char		*get_next_line(int fd);
void		update_linklist(t_list **link_list, int fd, char *buf);

#endif
