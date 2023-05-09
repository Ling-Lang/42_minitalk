
#define MAX_STRING_LENGTH 1000

void sig_handler(int sig_num, siginfo_t *sig_info, void *context) {
    static int bit_count = 0;
    static char current_byte = 0;
    static char received_string[MAX_STRING_LENGTH];
    static int received_length = 0;

    if (sig_num == SIGUSR1) {
        current_byte |= (1 << bit_count);
    }

    bit_count++;

    if (bit_count == 8) {
        strncat(received_string, &current_byte, 1);
        received_length++;
        bit_count = 0;
        current_byte = 0;
    }

    if (received_length > 0 && received_string[received_length - 1] == '\0') {
        printf("Received string: %s\n", received_string);
        memset(received_string, 0, MAX_STRING_LENGTH);
        received_length = 0;
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
