##
## Makefile for  in /home/daguen_s/rendu/PSU_2013_malloc
##
## Made by daguen_s
## Login   <daguen_s@epitech.net>
##
## Started on  Sun Feb 16 17:08:16 2014 daguen_s
## Last update Sun Feb 16 17:10:31 2014 daguen_s
##

SRC=		malloc.c\
		tools.c

INCLUDE=	malloc.h

CFLAGS=

LDFLAGS=

OBJ=		$(SRC:.c=.o)

NAME=		libmy_malloc_$(HOSTTYPE).so

PREPROCESSOR=	$(SRC:.c=.i)

ASM=		$(SRC:.c=.s)

all:		$(NAME)

full:		$(NAME) asm preprocessor

preprocessor:	$(PREPROCESSOR)

%.i:		%.c $(INCLUDE)
		gcc -E $(@:.i=.c) > $@

asm:		$(ASM)

%.s:		%.c $(INCLUDE)
		gcc -S $<

#linking project
$(NAME):	$(OBJ)
		gcc -shared -Wl,-soname,$@ -o $@ $^ -lc $(LDFLAGS) -lpthread -lm
		ln -sf $(NAME) libmy_malloc.so

#object Generation
%.o:		%.c $(INCLUDE)
		gcc -fPIC -g -c $< $(CFLAGS)

clean:
		rm -f $(OBJ)
		@rm -f $(addsuffix .gch, $(INCLUDE))
		@rm -f $(ASM)
		@rm -f $(PREPROCESSOR)

fclean:		clean
		rm -f $(NAME)
		rm -f libmy_malloc.so

re:		fclean all

backup:		$(SRC)
		tar -cf $(addsuffix .tar, $(NAME)) $^

help:
		@echo -e make option:
		@echo -e all
		@echo -e file.c
		@echo -e file.s
		@echo -e file.i
		@echo -e file.o
		@echo -e file.h
		@echo -e preprocessor
		@echo -e asm
		@echo -e clean
		@echo -e fclean
		@echo -e cache
		@echo -e clean_cache
		@echo -e re
		@echo -e backup

.PHONY:		clean fclean help re
