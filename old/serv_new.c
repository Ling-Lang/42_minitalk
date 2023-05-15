#include "minitalk.h"

int	binary_to_num(struct s_bin n)
{
	int	num;
	int	decimal_num;
	int	base;
	int	res;

	decimal_num = 0;
	base = 1;
	num = ft_atoi(n.bit);
	while (num > 0)
	{
		res = num % 10;
		decimal_num = decimal_num + res * base;
		num /= 10;
		base *= 2;
	}
	return (decimal_num);
}

void	sighandler(int signum)
{
	static struct s_bin	num;
	int					print;

	if (num.started != 1)
	{
		num.started = 1;
		num.current = 0;
	}
	if (signum == SIGUSR1)
		num.bit[num.current] = '0';
	else if (signum == SIGUSR2)
		num.bit[num.current] = '1';
	num.current++;
	if (num.current == BYTES_S)
	{
		print = binary_to_num(num);
		write(1, &print, 1);
		num.current = 0;
	}
}
void	manage_signals(int signum, siginfo_t *info, void *oldact)
{
	(void)info;
	(void)oldact;
	sighandler(signum);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf(YEL"PID: "WHT"%i\n"RESET, getpid());
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = manage_signals;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		sleep(1);
	return (0);
}