/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:55:10 by jkulka            #+#    #+#             */
/*   Updated: 2023/05/15 15:03:35 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK
#	define MINITALK

#	include "libft/src/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# define BYTES_S 8
# define TIME_SLP 200


void handle_bit(int sig_num, int* bit_count, char* current_byte);

void handle_byte(int* bit_count, char* current_byte);
void send_message(int server_pid, const char* message);
void send_bit(int server_pid, int bit);
void send_byte(int server_pid, char byte);
void set_zero(int *bit_count, char *current_byte);
#endif


