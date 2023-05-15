
#include "minitalk.h"

void sig_handler(int sig_num) {
    if (sig_num == SIGUSR1) {
        // Do nothing - this bit is a 1
    } else if (sig_num == SIGUSR2) {
        // Terminate the message loop - this bit is a 0
        exit(0);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3 || argc > 3) {
        ft_printf("Usage: %s <server_pid> <message>\n", argv[0]);
        exit(1);
    }

    int server_pid = atoi(argv[1]);
    char *message = argv[2];
    int message_length = strlen(message);

    ft_printf("Sending message '%s' to server with PID %d\n", message, server_pid);

    signal(SIGUSR1, sig_handler);
    signal(SIGUSR2, sig_handler);

    for (int i = 0; i < message_length; i++) {
        char c = message[i];
        for (int j = 0; j < 8; j++) {
            if (c & (1 << j)) {
                kill(server_pid, SIGUSR1);
            } else {
                kill(server_pid, SIGUSR2);
            }
            usleep(50); // adjust this delay as needed
        }
    }

    // Signal end of message with 8 SIGUSR2 signals
    for (int i = 0; i < 8; i++) {
        kill(server_pid, SIGUSR2);
        usleep(50); // adjust this delay as needed
    }

    return 0;
}
