#include "minitalk.h"

char	*str_to_bin(unsigned int n)
{
	char	*num;
	int		i;

	num = ft_calloc(sizeof(char), BYTES_S + 1);
	i = 0;
	while (n > 0)
	{
		num[BYTES_S - 1 - i] = n % 2 + '0';
		i++;
		n /= 2;
	}
	while (i < BYTES_S)
	{
		num[BYTES_S - 1 - i] = '0';
		i++;
	}
	return (num);
}

void	send_signal(int pid, int signal)
{
	kill(pid, signal);
	usleep(TIME_SLP);
}

void	send_char(char *num, int pid)
{
	int	len;
	int	dif;
	int	i;

	len = 0;
	while (num[len])
		len++;
	dif = BYTES_S - len;
	i = 0;
	while (i < dif)
	{
		send_signal(pid, SIGUSR1);
		i++;
	}
	i = 0;
	while (num[i])
	{
		if (num[i] == '0')
			send_signal(pid, SIGUSR1);
		else
			send_signal(pid, SIGUSR2);
		i++;
	}
	free(num);
}

int	main(int argc, char *argv[])
{
	int		pid;
	int		i;
	char	*str;

	if (argc < 3)
		return (0);
	pid = ft_atoi(argv[1]);
	i = 0;
	str = argv[2];
	while (str[i])
	{
		send_char(str_to_bin(str[i]), pid);
		i++;
	}
	send_char(str_to_bin('\n'), pid);
	send_char(str_to_bin('\0'), pid);
	return (0);
}