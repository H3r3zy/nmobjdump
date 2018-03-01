##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## makefile
##

NAME1 	=	my_objdump

NAME2	=	my_nm

NAME3	=	my_readelf

CC	=	gcc

RM	=	rm -rf

OBJSRC	=	src/objdump/dump.c	\
		src/objdump/objdump.c	\
		src/objdump/flag.c	\
		src/file.c	\
		src/objdump/header.c	\
		src/utils.c

OBJOBJ	=	$(OBJSRC:.c=.o)

NMSRC	=	src/nm/nm.c	\
		src/nm/dump.c	\
		src/nm/type.c	\
		src/utils.c	\
		src/file.c	\
		src/nm/type_check/bss.c	\
		src/nm/type_check/undefined.c	\
		src/nm/type_check/absolute.c	\
		src/nm/type_check/common.c	\
		src/nm/type_check/data.c	\
		src/nm/type_check/readonly.c	\
		src/nm/type_check/text.c

NMOBJ	=	$(NMSRC:.c=.o)

READELFSRC	=	src/file.c	\
			src/utils.c	\
			src/readelf/readelf.c	\
			src/readelf/dump/dump.c	\
			src/readelf/dump/file_header.c \
			src/readelf/dump/sections.c

READELFOBJ	=	$(READELFSRC:.c=.o)

CFLAGS	=	-I include
CFLAGS	+=	-W -Wall -Wextra

all:	$(NAME1) $(NAME2)

$(NAME1):	$(OBJOBJ)
	$(CC) $(OBJOBJ) -o $(NAME1) $(CFLAGS)

$(NAME2):	$(NMOBJ)
	$(CC) $(NMOBJ) -o $(NAME2) $(CFLAGS)

$(NAME3):	$(READELFOBJ)
	$(CC) $(READELFOBJ) -o $(NAME3) $(CFLAGS)

objdump:	$(NAME1)

nm:	$(NAME2)

readelf:	$(NAME3)

clean:
	$(RM) $(OBJOBJ) $(NMOBJ) $(READELFOBJ)
	$(RM) $(shell find . -type f -name "*.html")
	$(RM) $(shell find . -type f -name "*.png")
	$(RM) $(shell find . -type f -name "*.css")
	$(RM) $(shell find . -type f -name "*.gcda")
	$(RM) $(shell find . -type f -name "*.gcno")
	$(RM) app.info

fclean: clean
	$(RM) $(NAME1) $(NAME2) $(NAME3)

re: fclean all

debug: CFLAGS += -ggdb3

debug: re

test: CFLAGS += -lgcov --coverage

test: re

.PHONY: all clean fclean re debug $(NAME1) $(NAME2) $(NAME3) nm objdump test readelf
