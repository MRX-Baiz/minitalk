/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaiz <mbaiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:16:57 by mbaiz             #+#    #+#             */
/*   Updated: 2024/05/22 09:55:02 by mbaiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void check_and_reset_sender(int new_pid, int *current_pid, unsigned int *c, int *bit)
{
	if (*current_pid != new_pid)
	{
		*current_pid = new_pid;
		*c = 0;
		*bit = 0;
	}
}

void	handler_sig(int signal, siginfo_t *inform, void *context)
{
	static unsigned int	c;
	static int			bit;
	static int			cpid;

	(void)context;
	if (cpid != inform->si_pid)
	 check_and_reset_sender(inform->si_pid, &cpid, &c, &bit);
	c = (signal == SIGUSR2) << bit | c;
	bit++;
	if (bit == 8)
	{
		if (c)
			ft_printf("%c", c);
		bit = 0;
		c = 0;
	}
}

int	main(int arc, char **argv)
{
	int					pid;
	struct sigaction	action;

	(void)argv;
	if (arc != 1)
	{
		ft_printf("Error syntaxique \n");
		return (0);
	}
	pid = getpid();
	ft_printf("Server ID is %d\n", pid);
	action.sa_sigaction = handler_sig;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &action, 0);
	sigaction(SIGUSR2, &action, 0);
	while (1)
		pause();
}



