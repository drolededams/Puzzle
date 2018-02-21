/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   N-Puzzle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 12:03:58 by dgameiro          #+#    #+#             */
/*   Updated: 2018/02/21 19:43:56 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPuzzle_H
# define NPuzzle_H
# include "../libft/includes/libft.h"
# include <fcntl.h>
# include <stdio.h>
# define BAD_LINE 1
# define SIZES 2
# define TOO_LOW 3
# define NO_SIZE 4

typedef struct		s_puzzle_data
{
	int size;
	int line;
	int** puzzle;
}					t_puzzle_data;

void	get_file(char *file, t_puzzle_data *data);
int		good_line(char *line);
void	analyse_line(char *line, t_puzzle_data *data);
int		tablen(char **tab);
void	mem_puzzle(t_puzzle_data *data);
void	exit_bad_file(char **line, t_puzzle_data *data, int code);
void	exit_alloc_failed(void);
char	**strcomsplit(const char *s, char c);
void	free_tab(char **tab);
#endif
