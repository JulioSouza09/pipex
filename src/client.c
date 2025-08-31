/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 17:17:49 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/08/31 18:09:38 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minitalk.h"

int	main(void)
{
	printf("Client is properly working...\n");
	printf(INCLUDE_TEST);
	test_including_file();
	ft_putendl_fd("Libft works as well!", 1);
	return (0);
}
