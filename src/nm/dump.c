/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <ctype.h>
#include <stdio.h>
#include "nm.h"

static bool displayable(void const *const ehdr, void const *const symbol)
{
	if (STINFO(ehdr, symbol) == 4 || STNAME(ehdr, symbol) == 0 ||
		STNAME(ehdr, symbol) == 1)
		return false;
	return true;
}

static void dump_symbol(void const *const ehdr, void const *const shdr,
	void const *const symbol, char const *const strtab
)
{
	unsigned int type = get_type(ehdr, shdr, symbol);
	long unsigned int value = STVALUE(ehdr, symbol);

	if (IS64(ehdr) == true) {
		if ((value || tolower(type) == 'b') && tolower(type) != 'u')
			printf("%016lx ", value);
		else
			printf("                 ");
	} else {
		if ((value || tolower(type) == 'b') && tolower(type) != 'u')
			printf("%08lx ", value);
		else
			printf("         ");
	}
	printf("%c", type);
	printf(" %s\n", &strtab[STNAME(ehdr, symbol)]);
}

void dump_symbols(void const *const ehdr, void const *const shdr, int i
)
{
	void *symbol = (void *)((char *)ehdr + SHOFFSET(ehdr, shdr, i));
	void *end = (void *)((char *)symbol + SHSIZE(ehdr, shdr, i));
	char *strtab =
		(char *)ehdr + SHOFFSET(ehdr, shdr, SHLINK(ehdr, shdr, i));

	while (symbol < end) {
		if (displayable(ehdr, symbol) == true) {
			dump_symbol(ehdr, shdr, symbol, strtab);
		}
		symbol = STNEXT(ehdr, symbol);
	}
}