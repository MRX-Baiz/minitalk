/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaiz <mbaiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:15:56 by mbaiz             #+#    #+#             */
/*   Updated: 2024/05/22 10:18:09 by mbaiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signal(int pid, unsigned int c)
{
	int		bit;

	bit = 0;
	while (bit < 8)
	{
		if (c >> bit & 1)
		{
			if(kill(pid, SIGUSR2)==-1)
			{
				printf("error1");
				exit(0);
			}
		}
		else
		{
			if(kill(pid, SIGUSR1)==-1)
			{
				printf("error\n");
				exit(0);
			}
		}
		bit++;
		usleep(50);
	}
}

int	main(int argc, char *argv[])
{
	pid_t		server_pid;
	int			i;

	if (argc != 3)
	{
		ft_printf("Usage: %s 'pid'  'message'\n", argv[0]);
		exit(0);
	}
	server_pid = ft_atoi(argv[1]);
	if ((unsigned long long)server_pid > MAX_PID || server_pid < 0)
	{
		ft_printf("the PID is bypassed!");
		exit(0);
	}
	i = 0;
	while (argv[2][i])
    {
		send_signal(server_pid, argv[2][i]);
        i++;
    }

	return (0);
}