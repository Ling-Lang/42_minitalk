/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:55:39 by jkulka            #+#    #+#             */
/*   Updated: 2023/05/10 11:12:05 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minitalk.h"

#define INITIAL_BUFFER_SIZE 64

void sig_handler(int sig_num) {
    static int bit_count = 0;
    static char current_byte = 0;
    static char *received_buffer = NULL;
    static int buffer_length = 0;

    if (received_buffer == NULL) {
        received_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char)); // +1 for null terminator
    }

    if (sig_num == SIGUSR1) {
        current_byte |= (1 << bit_count);
    }

    bit_count++;

    if (bit_count == 8) {
        if (current_byte == '\0') {
            received_buffer[buffer_length] = '\0'; // add null terminator
            printf("Received message: %s\n", received_buffer);
            bit_count = 0;
            current_byte = 0;
            buffer_length = 0;
            free(received_buffer);
            received_buffer = NULL;
        } else {
            received_buffer[buffer_length] = current_byte;
            buffer_length++;
            bit_count = 0;
            current_byte = 0;

            if (buffer_length >= BUFFER_SIZE) {
                printf("Buffer full - allocating more memory\n");
                char *temp = realloc(received_buffer, (BUFFER_SIZE * 2 + 1) * sizeof(char));
                if (temp == NULL) {
                    printf("Failed to allocate more memory\n");
                    exit(1);
                }
                received_buffer = temp;
                memset(received_buffer + buffer_length, 0, BUFFER_SIZE + 1);
                buffer_length += BUFFER_SIZE;
            }
        }
    }
}


int main() {
    printf("Server PID: %d\n", getpid());

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
