/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malrifai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:19:15 by malrifai          #+#    #+#             */
/*   Updated: 2024/11/17 11:48:26 by malrifai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <stdio.h>

int row_len(char **row)
{
  int i;

  i = 0;
  while(row[i])
    i++;
  return (i);
}

int *split_row(char *row, int *argc)
{
  char **splited_row;
  int *heights;
  int i;
  int len;

  len = 0;
  i = 0;
  splited_row = ft_split(row, ' ');
  len = row_len(splited_row);
  *argc = len;
  heights = (int *)malloc(len * sizeof(int));
  while (i < len)
  {
    heights[i] = ft_atoi(splited_row[i]);
    free(splited_row[i]);
    i++;
  }
  free(splited_row);
  return heights;
}
 
int get_row_numbers(int fd)
{
  char *line;
  int i;

  i = 0;
  while((line = get_next_line(fd)) != NULL)
  {
    free(line);
    i++;
  }
  close(fd);
  return i;
}

void print_int_array(int **array, int rows, int cols) {
    if (!array) {
        printf("Array is NULL.\n");
        return;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", array[i][j]);
        }
	free(array[i]);
        printf("\n"); // Move to the next row
    }
    free(array);
}

int main(int argc, char **argv)
{
  //t_point  *map;
  int fd;
  int count;
  char  *line;
  int **map;
  int i;
  
  i = 0;
  fd = open(argv[1], O_RDONLY);
  count = get_row_numbers(fd);
  map = malloc(count * sizeof(int *));
  fd = open(argv[1], O_RDONLY);
  while((line = get_next_line(fd)) != NULL)
  {
    map[i++] = split_row(line, &argc);
    free(line);
  }
  close(fd);

  print_int_array(map, count, argc);
}
