# Minitalk

Minitalk is a simple demonstration of UNIX signals as a method of inter-process communication (IPC). The program consists of two parts: a server and a client. 

## How it Works

The server waits for signals from a client, and the client sends signals that include a message to the server. The server then prints the message received from the client.

Each character of the message is sent as a series of signals representing the binary encoding of the character. Specifically, `SIGUSR1` represents a binary 0 and `SIGUSR2` represents a binary 1. After each character, the client sends an additional eight `SIGUSR1` signals to indicate the end of the character.

When the server receives a signal, it adds the bit represented by the signal to a buffer. Once eight signals have been received (i.e., a full character in ASCII), the server prints the character and resets the buffer. When the server receives eight `SIGUSR1` signals in a row, it interprets this as the end of the message.

## Usage

To use Minitalk, first start the server in a terminal:

```
./server
```

The server will print its process ID (PID) to the console. This PID will be used to send signals to the server.

Then, in a separate terminal, send a message from the client to the server:

```
./client [server_PID] [message]
```

Replace `[server_PID]` with the PID printed by the server and `[message]` with the message you want to send. The message can be any string without spaces.

For example:

```
./client 12345 "HelloWorld"
```

This command will send the message "HelloWorld" to the server with PID 12345.

## Code Overview

### client.c

The client program takes two command-line arguments: the PID of the server and the message to send.

The function `mt_kill` sends the message to the server. For each character in the string, it sends eight signals representing the binary encoding of the character. It then sends eight additional `SIGUSR1` signals to indicate the end of the character.

### server.c

The server program prints its PID and then waits for signals. 

The function `action` is called when a signal is received. It adds the bit represented by the signal to a buffer. When eight signals have been received, it prints the character represented by the buffer and resets the buffer.

## Note

The code assumes that the client and server are on the same machine. If they are on different machines, they need to be able to send and receive signals to each other, which may require additional configuration.
