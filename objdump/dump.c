/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "objdump.h"

static bool section_displayable(void *data, void *shdr, char const *shtab, int idx)
{
	int type = SHTYPE(data, shdr, idx);
	const char *name = &shtab[SHNAME(data, shdr, idx)];

	if (strcmp(name, ".rela.dyn") == 0 || strcmp(name, ".rela.plt") == 0 ||
		strcmp(name, ".rel.plt") == 0 || strcmp(name, ".rel.dyn") == 0)
		return (true);
	if (type == SHT_NULL || type == SHT_NOBITS || type == SHT_SYMTAB ||
		type == SHT_RELA || type == SHT_REL)
		return (false);
	if (type == SHT_STRTAB && !(SHFLAGS(data, shdr, idx) & SHF_ALLOC))
		return (false);
	if (!SHSIZE(data, shdr, idx))
		return (false);
	return (true);
}

static void dump_hex(char const *data, long unsigned int offset,
	long unsigned int size
)
{
	unsigned int cnt = 0;

	while (cnt < 16) {
		if (cnt > 0 && cnt % 4 == 0)
			printf(" ");
		if (cnt + offset < size)
			printf("%02x", (unsigned char)*(data + offset + cnt));
		else
			printf("  ");
		cnt++;
	}
}

static void dump_ascii(char const *data, long unsigned int offset,
	long unsigned int size
)
{
	unsigned int cnt = 0;
	unsigned char c = 0;

	while (cnt < 16) {
		if (offset + cnt >= size) {
			printf(" ");
			cnt++;
			continue;
		}
		c = (unsigned char)*(data + offset + cnt);
		if (!isprint(c)) {
			c = '.';
		}
		printf("%c", c);
		cnt++;
	}
}

static void dump_section(void *data, void *shdr, int i)
{
	long unsigned int offset = 0;
	int padding = 0;

	while (offset < SHSIZE(data, shdr, i)) {
		padding = calc_hex_digits(SHADDR(data, shdr, i) + offset);
		if (padding < 4)
			padding = 4;
		printf(" %0*lx ", padding, SHADDR(data, shdr, i) + offset);
		dump_hex(CONTENT(data, SHOFFSET(data, shdr, i)), offset,
			SHSIZE(data, shdr, i));
		printf("  ");
		dump_ascii(CONTENT(data, SHOFFSET(data, shdr, i)), offset,
			SHSIZE(data, shdr, i));
		printf("\n");
		offset += 16;
	}
}

void dump_sections(void *data, void *shdr, char const *shtab, int shnum)
{
	int i = 0;

	while (i < shnum) {
		if (section_displayable(data, shdr, shtab, i) == true) {
			printf("Contents of section %s:\n",
				&shtab[SHNAME(data, shdr, i)]);
			dump_section(data, shdr, i);
		}
		i++;
	}
}
