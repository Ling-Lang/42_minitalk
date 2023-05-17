/************************************/
/*           Client Program          */
/************************************/

The client program is responsible for transmitting a string of characters to a server process using custom signals.

The client code consists of the following components:

1. `handle_signal` - Signal Handler Function:
   - This function is registered as the signal handler for `SIGUSR1` and `SIGUSR2`.
   - Its purpose is to handle signals received during the communication process.
   - If a signal other than `SIGUSR1` is received, it terminates the program with `exit(0)`.

2. `send_string` Function:
   - This function takes the server process ID (`pid`) and the string to be transmitted (`str`) as parameters.
   - It sends the string character by character to the server process using custom signals.
   - For each character, it loops 8 times to transmit each bit of the character.
   - If the bit is 1, it sends a `SIGUSR2` signal to the server; otherwise, it sends a `SIGUSR1` signal.
   - After transmitting each bit, it pauses for a short period using `usleep(30)`.

3. `main` Function:
   - The entry point of the program.
   - It validates the command-line arguments, requiring the server process ID (`PID`) and a non-empty message.
   - Displays the message and the server PID on the console.
   - Registers the `handle_signal` function as the signal handler for `SIGUSR1` and `SIGUSR2`.
   - Calls the `send_string` function to transmit the message to the server process.
   - Enters an infinite loop using `pause()` to wait for signals.

4. Error Handling and Output:
   - If the command-line arguments are invalid or the message is empty, it displays an error message.
   - It uses the `ft_printf` function to display formatted output.

/************************************/
/*         End of Client Code        */
/************************************/
