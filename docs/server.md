Server Program
==============

The server program is responsible for receiving and processing data transmitted by a client process using custom signals.

Components
-----------

1. `sig_handler` - Signal Handler Function:
   - Registers as the signal handler for `SIGUSR1` and `SIGUSR2`.
   - Handles signals received during the communication process.
   - Accumulates received bits to reconstruct transmitted data.
   - Processes a complete byte (8 bits) by printing it to the standard output.
   - Sends `SIGUSR1` back to the client to acknowledge successful reception (non-zero byte).
   - Sends `SIGUSR2` to the client to indicate the end of transmission (zero byte).

2. `main` Function:
   - Displays the server PID.
   - Registers `sig_handler` as the signal handler for `SIGUSR1` and `SIGUSR2`.
   - Enters an infinite loop using `pause()` to wait for signals.

Error Handling and Output
-------------------------
- No specific error checks or error messages in the server code.
- Uses `ft_printf` for formatted output.

