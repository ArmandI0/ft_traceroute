/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:36:23 by aranger           #+#    #+#             */
/*   Updated: 2024/02/29 10:52:20 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FD_H
# define FT_PRINTF_FD_H
# include "../libft.h"
# include <unistd.h>
# include <stdarg.h>

size_t	ft_print_char(char c, int fd);
size_t	ft_print_string(char *str, int fd);
int		ft_print_decimal(int nbr, int fd);
int		ft_print_adress(unsigned long long ptr, int fd);
int		ft_print_unsigned(unsigned int nbr, int fd);
int		ft_print_hexadecimal_lower(unsigned int nbr, int fd);
int		ft_print_hexadecimal_upper(unsigned int nbr, int fd);

#endif
