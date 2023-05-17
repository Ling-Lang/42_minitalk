Client Program
==============

The client program is responsible for transmitting a string of characters to a server process using custom signals.

Components
-----------

1. `handle_signal` - Signal Handler Function:
   - Registers as the signal handler for `SIGUSR1` and `SIGUSR2`.
   - Handles signals received during the communication process.
   - Terminates the program with `exit(0)` if a signal other than `SIGUSR1` is received.

2. `send_string` Function:
   - Transmits the string character by character to the server process using custom signals.
   - Loops 8 times to transmit each bit of a character.
   - Sends a `SIGUSR2` signal to the server if the bit is 1; otherwise, sends a `SIGUSR1` signal.
   - Pauses briefly using `usleep(30)` after each bit transmission.

3. `main` Function:
   - Validates command-line arguments: server process ID (`PID`) and non-empty message.
   - Displays the message and server PID.
   - Registers `handle_signal` as the signal handler for `SIGUSR1` and `SIGUSR2`.
   - Calls `send_string` to transmit the message to the server.
   - Enters an infinite loop using `pause()` to wait for signals.

Error Handling and Output
-------------------------
- Displays an error message if command-line arguments are invalid or the message is empty.
- Uses `ft_printf` for formatted output.

