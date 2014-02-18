/*
** malloc.c for  in /home/daguen_s/Projets/malloc-2017-daguen_s
**
** Made by daguen_s
** Login   <daguen_s@epitech.net>
**
** Started on  Tue Jan 28 11:30:13 2014 daguen_s
** Last update Sun Feb 16 23:32:42 2014 daguen_s
*/

#include "malloc.h"

t_block				*g_buckets[32];
t_block				*g_list;

void				*calloc(size_t nmemb, size_t size)
{
  void				*ptr;

  ptr = malloc(nmemb * size);
  if (ptr)
    memset(ptr, 0, nmemb * size);
  return (ptr);
}

void				*realloc(void *ptr, size_t size)
{
  size_t			my_size;
  void				*ret;
  t_block			*b;

  ret = NULL;
  if (ptr == NULL)
    ret = malloc(size);
  else
    {
      if (size == 0)
	free(ptr);
      else
	{
	  b = (t_block *)((void *)ptr - BLOCK_SIZE);
	  my_size = pow(2, b->p);
	  if (my_size > size)
	    return (ptr);
	  ret = malloc(size);
	  ret = memcpy(ret, ptr, my_size);
	  free(ptr);
	}
    }
  return (ret);
}

void				free(void *ptr)
{
  t_block			*elem;
  unsigned int			power_of_ptr;

  if (!ptr)
    return;
  elem = (t_block *)((char*)ptr - BLOCK_SIZE);
  if (elem->_free == 0)
    {
      printf("This pointeur is already free!!!\n");
      return;
    }
  power_of_ptr = elem->p;
  elem->_free = 0;
  elem->next = g_buckets[power_of_ptr];
  g_buckets[power_of_ptr] = elem;
}

t_block				*create_new_block(unsigned int power)
{
  t_block			*tab[3];
  int				page;
  int				alloc;
  int				size;

  page = sysconf(_SC_PAGESIZE);
  size = (int)pow(2, power);
  alloc = ((size / page) + (size > page ? 0 : 1)) * page;
  if ((tab[0] = sbrk(alloc)) == (void*)-1)
    {
      printf("sbrk: failure in create_new_block.\n");
      return (NULL);
    }
  block_fragmentation(tab, alloc / size, power);
  push_back(tab[0]);
  return (tab[0]);
}

void				*malloc(size_t size)
{
  static pthread_mutex_t	my_mutex = PTHREAD_MUTEX_INITIALIZER;
  t_block			*ptr;
  unsigned int			power;

  if (size == 0)
    return (NULL);
  size = resize(size);
  power = get_power(BLOCK_SIZE + size);
  while (pthread_mutex_lock(&my_mutex) != 0);
  if ((ptr = g_buckets[power]) == NULL)
    ptr = create_new_block(power);
  else
    {
      ptr->_free = 1;
      g_buckets[power] = ptr->next;
    }
  while (pthread_mutex_unlock(&my_mutex) != 0);
  return ((char *)ptr + BLOCK_SIZE);
}
