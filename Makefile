##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## makefile
##

NAME1 	=	my_objdump

NAME2	=	my_nm

CC	=	gcc

RM	=	rm -rf

OBJSRC	=	objdump/dump.c	\
		objdump/objdump.c	\
		objdump/flag.c	\
		objdump/file.c	\
		objdump/header.c	\
		objdump/utils.c

OBJOBJ	=	$(OBJSRC:.c=.o)

NMSRC	=	nm/nm.c	\
		objdump/utils.c	\
		objdump/file.c

NMOBJ	=	$(NMSRC:.c=.o)

CFLAGS	=	-I include
CFLAGS	+=	-W -Wall -Wextra

all:	$(NAME1) $(NAME2)

$(NAME1):	$(OBJOBJ)
	$(CC) $(OBJOBJ) -o $(NAME1) $(CFLAGS)

$(NAME2):	$(NMOBJ)
	$(CC) $(NMOBJ) -o $(NAME2) $(CFLAGS)

objdump:	$(NAME1)

nm:	$(NAME2)

clean:
	$(RM) $(OBJOBJ) $(NMOBJ)

fclean: clean
	$(RM) $(NAME1) $(NAME2)

re: fclean all

debug: CFLAGS += -ggdb3

debug: re

32: CFLAGS += -m32

32: re

.PHONY: all clean fclean re debug $(NAME1) $(NAME2) nm objdump 32
