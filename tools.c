/*
** tools.c for  in /home/daguen_s/Projets/malloc-2017-daguen_s/my
**
** Made by daguen_s
** Login   <daguen_s@epitech.net>
**
** Started on  Sun Feb  9 17:24:27 2014 daguen_s
** Last update Sun Feb 16 17:17:14 2014 daguen_s
*/

#include "malloc.h"

extern t_block	*g_buckets[32];
extern t_block	*g_list;

void		push_back(t_block *add)
{
  t_block	*tmp;

  tmp = g_list;
  add->prev = NULL;
  if (!tmp)
    g_list = add;
  else
    {
      while (tmp->prev)
	tmp = tmp->prev;
      tmp->prev = add;
    }
}

int		get_power(size_t size)
{
  int		i;

  i = 0;
  while (i < 32)
    {
      if (size < (size_t)pow(2, i))
	return (i);
      i++;
    }
  return (-1);
}

void		block_fragmentation(t_block *tab[3], int blck,
				    unsigned int power)
{
  t_block	tmp;
  int		i;

  i = 0;
  tmp._free = 0;
  tmp.p = power;
  tab[2] = tab[0];
  while (i < blck)
    {
      tmp.next = NULL;
      tmp.prev = NULL;
      tab[1] = (t_block*)((char*)tab[2] + (int)pow(2, power));
      if (i + 1 < blck)
	tmp.next = tab[1];
      else
	tmp.next = NULL;
      memcpy(tab[2], &tmp, BLOCK_SIZE);
      tab[2] = tab[1];
      i++;
    }
  tab[0]->_free = 1;
}

size_t		resize(size_t size)
{
  size_t	page_size;
  int		i;

  i = 1;
  page_size = sysconf(_SC_PAGESIZE);
  while (page_size >> i)
    ++i;
  --i;
  return ((((size - 1) >> i) << i) + page_size);
}

void		show_alloc_mem()
{
  t_block	*tmp;

  tmp = g_list;
  printf("break : %p\n", sbrk(0));
  while (tmp)
    {
      if (tmp->_free)
	       printf("%p - %p : %d\n", tmp, (char *)tmp +
		      (int)pow(tmp->p, 2) + BLOCK_SIZE,
		      (unsigned int)pow(2, tmp->p));
      tmp = tmp->prev;
    }
}
