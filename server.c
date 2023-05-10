/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:55:39 by jkulka            #+#    #+#             */
/*   Updated: 2023/05/10 11:00:40 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minitalk.h"
#define BUFFER_SIZE 2048

void sig_handler(int sig_num) {
    static int bit_count = 0;
    static char current_byte = 0;
    static char received_buffer[BUFFER_SIZE + 1]; // +1 for null terminator
    static int buffer_length = 0;

    if (sig_num == SIGUSR1) {
        current_byte |= (1 << bit_count);
    }

    bit_count++;

    if (bit_count == 8) {
        if (current_byte == '\0') {
            received_buffer[buffer_length] = '\0'; // add null terminator
            ft_printf("Received message: %s\n", received_buffer);
            bit_count = 0;
            current_byte = 0;
            buffer_length = 0;
            memset(received_buffer, 0, BUFFER_SIZE + 1); // clear buffer
        } else if (buffer_length < BUFFER_SIZE) {
            received_buffer[buffer_length] = current_byte;
            buffer_length++;
            bit_count = 0;
            current_byte = 0;
        } else {
            ft_printf("Buffer full - discarding remaining characters\n");
            bit_count = 0;
            current_byte = 0;
            buffer_length = 0;
            memset(received_buffer, 0, BUFFER_SIZE + 1); // clear buffer
        }
    }
}


int main() {
    ft_printf("Server PID: %d\n", getpid());

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = sig_handler;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    while (1) {
        pause();
    }
    return 0;
}