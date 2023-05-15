// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   server.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jkulka <jkulka@student.42heilbronn.de>     +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/05/09 12:55:39 by jkulka            #+#    #+#             */
// /*   Updated: 2023/05/15 15:04:24 by jkulka           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minitalk.h"
// #define BUFFER_SIZE 2048

// void	sig_handler(int sig_num)
// {
// 	static int	bit_count;
// 	static char	current_byte;

// 	bit_count = 0;
// 	current_byte = 0;
// 	handle_bit(sig_num, &bit_count, &current_byte);
// 	handle_byte(&bit_count, &current_byte);
// }

// void	handle_bit(int sig_num, int *bit_count, char *current_byte)
// {
// 	if (sig_num == SIGUSR1)
// 	{
// 		*current_byte |= (1 << *bit_count);
// 	}
// 	(*bit_count)++;
// }

// void	handle_byte(int *bit_count, char *current_byte)
// {
// 	static char	received_buffer[BUFFER_SIZE + 1];
// 	static int	buffer_length;

// 	buffer_length = 0;
// 	if (*bit_count == 8)
// 	{
// 		if (*current_byte == '\0')
// 		{
// 			received_buffer[buffer_length] = '\0';
// 			ft_printf("Received message: %s\n", received_buffer);
// 			set_zero(bit_count, current_byte);
// 			buffer_length = 0;
// 			ft_memset(received_buffer, 0, BUFFER_SIZE + 1);
// 		}
// 		else if (buffer_length < BUFFER_SIZE)
// 		{
// 			received_buffer[buffer_length] = *current_byte;
// 			buffer_length++;
// 			set_zero(bit_count, current_byte);
// 		}
// 		else
// 		{
// 			ft_printf("Buffer full - discarding remaining characters\n");
// 			set_zero(bit_count, current_byte);
// 			buffer_length = 0;
// 			ft_memset(received_buffer, 0, BUFFER_SIZE + 1);
// 		}
// 	}
// }

// void	set_zero(int *bit_count, char *current_byte)
// {
// 	*bit_count = 0;
// 	*current_byte = 0;
// }

// int	main(void)
// {
// 	ft_printf("Server PID: %d\n", getpid());

// 	struct sigaction sa;
// 	ft_memset(&sa, 0, sizeof(sa));
// 	sa.sa_handler = sig_handler;
// 	sigaction(SIGUSR1, &sa, NULL);
// 	sigaction(SIGUSR2, &sa, NULL);

// 	while (1)
// 	{
// 		pause();
// 	}
// 	return (0);
// }





#include "minitalk.h"
#define BUFFER_SIZE 2048

void sig_handler(int sig_num);
void handle_bit(int sig_num, int *bit_count, char *current_byte);
void handle_byte(int *bit_count, char *current_byte);
void handle_termination(int *bit_count, char *current_byte);
void handle_non_termination(int *bit_count, char *current_byte, int *buffer_length, char *received_buffer);
void set_zero(int *bit_count, char *current_byte);

void sig_handler(int sig_num) {
    static int bit_count;
    static char current_byte;

    handle_bit(sig_num, &bit_count, &current_byte);
    handle_byte(&bit_count, &current_byte);
}

void handle_bit(int sig_num, int *bit_count, char *current_byte) {
    if (sig_num == SIGUSR1) {
        *current_byte |= (1 << *bit_count);
    }
    (*bit_count)++;
}

void handle_byte(int *bit_count, char *current_byte) {
    static char received_buffer[BUFFER_SIZE + 1];
    static int buffer_length = 0;

    if (*bit_count == 8) {
        if (*current_byte == '\0') {
            handle_termination(bit_count, current_byte);
        } else {
            handle_non_termination(bit_count, current_byte, &buffer_length, received_buffer);
        }
    }
}

void handle_termination(int *bit_count, char *current_byte) {
    static char received_buffer[BUFFER_SIZE + 1];

    received_buffer[0] = '\0';
    ft_printf("Received message: %s\n", received_buffer);
    set_zero(bit_count, current_byte);
    buffer_length = 0;
    ft_memset(received_buffer, 0, BUFFER_SIZE + 1);
}

void handle_non_termination(int *bit_count, char *current_byte, int *buffer_length, char *received_buffer) {
    if (*buffer_length < BUFFER_SIZE) {
        received_buffer[*buffer_length] = *current_byte;
        (*buffer_length)++;
        set_zero(bit_count, current_byte);
    } else {
        ft_printf("Buffer full - discarding remaining characters\n");
        set_zero(bit_count, current_byte);
        *buffer_length = 0;
        ft_memset(received_buffer, 0, BUFFER_SIZE + 1);
    }
}

void set_zero(int *bit_count, char *current_byte) {
    *bit_count = 0;
    *current_byte = 0;
}

int main(void) {
    ft_printf("Server PID: %d\n", getpid());

    struct sigaction sa;
    ft_memset(&sa, 0, sizeof(sa));
    sa.sa_handler = sig_handler;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    while (1) {
        pause();
    }
    return (0);
}
