/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 00:39:15 by jkulka            #+#    #+#             */
/*   Updated: 2023/05/17 21:05:30 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

static void	handle_signal(int sig)
{
	if (sig != SIGUSR1)
	{
		exit(0);
	}
}

static void	send_string(int pid, char *str)
{
	int		i;
	char	c;

	while (*str)
	{
		i = 8;
		c = *str++;
		while (i--)
		{
			if (c >> i & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(30);
		}
	}
	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR1);
		usleep(30);
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3 || !ft_strlen(argv[2]))
	{
		ft_printf(RED"ERROR\n"WHT"Usage: ./client "YEL"[PID] [message]\n");
		return (1);
	}
	ft_printf("Sent "BLU"\"%s\" " WHT"to PID: "YEL"%d\n", argv[2], ft_atoi(argv[1]));
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	send_string(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}