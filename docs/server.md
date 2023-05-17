/************************************/
/*           Server Program          */
/************************************/

The server program is responsible for receiving and processing data transmitted by a client process using custom signals.

The server code consists of the following components:

1. `sig_handler` - Signal Handler Function:
   - This function is registered as the signal handler for `SIGUSR1` and `SIGUSR2`.
   - It handles the signals received during the communication process.
   - The function accumulates the received bits to reconstruct the transmitted data.
   - When a complete byte (8 bits) is received, it processes the byte by printing it to the standard output.
   - If the byte is non-zero, it sends a `SIGUSR1` signal back to the client to acknowledge successful reception.
   - If the byte is zero, it sends a `SIGUSR2` signal to the client to indicate the end of transmission.

2. `main` Function:
   - The entry point of the program.
   - Displays the server PID on the console.
   - Registers the `sig_handler` function as the signal handler for `SIGUSR1` and `SIGUSR2`.
   - Enters an infinite loop using `pause()` to wait for signals.

3. Error Handling and Output:
   - There are no specific error checks or error messages in the server code.
   - It uses the `ft_printf` function to display formatted output.

/************************************/
/*         End of Server Code        */
/************************************/
