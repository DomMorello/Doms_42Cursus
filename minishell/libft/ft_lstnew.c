/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 18:12:34 by donglee           #+#    #+#             */
/*   Updated: 2020/04/07 18:13:05 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *ret;

	if ((ret = (t_list *)malloc(sizeof(ret))) == 0)
		return (NULL);
	ret->next = NULL;
	ret->content = content;
	return (ret);
}
