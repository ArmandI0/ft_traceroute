/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:36:23 by aranger           #+#    #+#             */
/*   Updated: 2023/11/28 13:43:21 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "../libft.h"
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *str, ...);
size_t	ft_print_char(char c);
size_t	ft_print_string(char *str);
int		ft_print_decimal(int nbr);
int		ft_print_adress(unsigned long long ptr);
int		ft_print_unsigned(unsigned int nbr);
int		ft_print_hexadecimal_lower(unsigned int nbr);
int		ft_print_hexadecimal_upper(unsigned int nbr);

#endif
