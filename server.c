// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <signal.h>
// #include <string.h>

// #define MAX_STRING_LENGTH 100

// void sig_handler(int sig_num) {
//     if (sig_num == SIGUSR1) {
//         printf("Server received SIGUSR1 signal\n");
//     } else if (sig_num == SIGUSR2) {
//         printf("Server received SIGUSR2 signal\n");
//     }
// }

// int main() {
//     printf("Server PID: %d\n", getpid());

//     struct sigaction sa;
//     memset(&sa, 0, sizeof(sa));
//     sa.sa_handler = sig_handler;
//     sigaction(SIGUSR1, &sa, NULL);
//     sigaction(SIGUSR2, &sa, NULL);

//     while (1) {
//         pause();
//     }

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define MAX_STRING_LENGTH 100

void sig_handler(int sig_num, siginfo_t *sig_info, void *context) {
    static int bit_count = 0;
    static char current_byte = 0;
    static char received_string[MAX_STRING_LENGTH];

    if (sig_num == SIGUSR1) {
        current_byte |= (1 << bit_count);
    }

    bit_count++;

    if (bit_count == 8) {
        strncat(received_string, &current_byte, 1);
        bit_count = 0;
        current_byte = 0;
    }

    if (received_string[strlen(received_string) - 1] == '\0') {
        printf("Received string: %s\n", received_string);
        memset(received_string, 0, MAX_STRING_LENGTH);
    }
}



int main() {
    printf("Server PID: %d\n", getpid());

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = sig_handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    while (1) {
        pause();
    }

    return 0;
}
