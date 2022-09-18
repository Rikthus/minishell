/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:03:31 by maxperei          #+#    #+#             */
/*   Updated: 2021/11/11 16:32:48 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_block;

	new_lst = 0;
	while (lst)
	{
		new_block = ft_lstnew((*f)(lst->content));
		if (!new_block)
		{
			ft_lstclear(&new_lst, (*del));
			return (0);
		}
		ft_lstadd_back(&new_lst, new_block);
		lst = lst->next;
	}
	return (new_lst);
}
