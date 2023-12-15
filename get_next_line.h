/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:02:38 by kalam             #+#    #+#             */
/*   Updated: 2023/12/15 18:09:54 by kalam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*str_buf;
	struct s_list	*next;
}				t_list;

int			found_newline(t_list *list);
t_list		*find_last_node(t_list *list);
char		*get_line(t_list *list);
void		copy_str(t_list *list, char *str);
int			len_to_newline(t_list *list);
void		polish_list(t_list **list);
char		*get_next_line(int fd);
void		dealloc(t_list **list, t_list *clean_node, char *buf);
void		create_list(t_list **list, int fd);
int			main(void);
#endif
