/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 17:33:29 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/08/31 17:42:34 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minitalk.h"

#define FILE_TEST "Including other '.c' files seems to be working as well!\n"

void	test_including_file(void)
{
	printf(FILE_TEST);
}
