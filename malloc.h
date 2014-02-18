/*
** malloc.h for malloc.h in /home/daguen_s/Projets/malloc-2017-daguen_s
**
** Made by daguen_s
** Login   <daguen_s@epitech.net>
**
** Started on  Tue Jan 28 11:27:03 2014 daguen_s
** Last update Sun Feb 16 16:13:51 2014 daguen_s
*/

#ifndef _MALLOC_H_
# define _MALLOC_H_

#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

typedef struct		s_block
{
  unsigned int		p;
  int			_free;
  struct s_block	*prev;
  struct s_block	*next;
}			t_block;

#define			BLOCK_SIZE sizeof(t_block)

/* tools.c */
int			get_power(size_t size);
size_t			resize(size_t size);
void			show_alloc_mem();
void			push_back(t_block *add);
void			block_fragmentation(t_block *tab[3], int blck, unsigned int power);

/* malloc.c*/
void			*calloc(size_t nmemb, size_t size);
void			*realloc(void *ptr, size_t size);
void			free(void *ptr);
t_block			*create_new_block(unsigned int power);
void			*malloc(size_t size);

#endif /* _MALLOC_H_ */
