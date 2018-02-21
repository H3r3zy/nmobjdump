/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "objdump.h"

static bool section_displayable(SHdr64 *shdr, char const *shtab, int idx)
{
	int type = shdr[idx].sh_type;
	const char *name = &shtab[shdr[idx].sh_name];

	if (strcmp(name, ".rela.dyn") == 0 || strcmp(name, ".rela.plt") == 0 ||
		strcmp(name, ".rel.plt") == 0 || strcmp(name, ".rel.dyn") == 0)
		return (true);
	if (type == SHT_NULL || type == SHT_NOBITS || type == SHT_SYMTAB ||
		type == SHT_RELA || type == SHT_REL)
		return (false);
	if (type == SHT_STRTAB && !(shdr[idx].sh_flags & SHF_ALLOC))
		return (false);
	if (!shdr[idx].sh_size)
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

static void dump_section(void *data, SHdr64 *shdr, int i)
{
	long unsigned int offset = 0;
	int padding = 0;

	while (offset < shdr[i].sh_size) {
		padding = calc_hex_digits(shdr[i].sh_addr + offset);
		if (padding < 4)
			padding = 4;
		printf(" %0*lx ", padding, shdr[i].sh_addr + offset);
		dump_hex(CONTENT(data, shdr[i].sh_offset), offset,
			shdr[i].sh_size);
		printf("  ");
		dump_ascii(CONTENT(data, shdr[i].sh_offset), offset,
			shdr[i].sh_size);
		printf("\n");
		offset += 16;
	}
}

void dump_sections(void *data, SHdr64 *shdr, char const *shtab, int shnum)
{
	int i = 0;

	while (i < shnum) {
		if (section_displayable(shdr, shtab, i) == true) {
			printf("Contents of section %s:\n",
				&shtab[shdr[i].sh_name]);
			dump_section(data, shdr, i);
		}
		i++;
	}
}