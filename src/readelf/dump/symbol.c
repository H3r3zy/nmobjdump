/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <stdio.h>
#include "readelf.h"

static const t_message TYPES[] = {
	{STT_NOTYPE, "NOTYPE"},
	{STT_OBJECT, "OBJECT"},
	{STT_FUNC, "FUNC"},
	{STT_SECTION, "SECTION"},
	{STT_FILE, "FILE"},
	{STT_COMMON, "COMMON"},
	{STT_TLS, "TLS"},
	{STT_NUM, "NUM"},
	{STT_LOOS, "LOOS"},
	{STT_HIOS, "HIOS"},
	{STT_LOPROC, "LOPROC"},
	{STT_HIPROC, "HIPROC"},
	{-1, NULL}
};

static const t_message BINDS[] = {
	{STB_LOCAL, "LOCAL"},
	{STB_GLOBAL, "GLOBAL"},
	{STB_WEAK, "WEAK"},
	{STB_NUM, "NUM"},
	{STB_LOOS, "LOOS"},
	{STB_HIOS, "HIOS"},
	{STB_LOPROC, "LOPROC"},
	{STB_HIPROC, "HIPROC"},
	{-1, NULL}
};

static const t_message VISIBILITY[] = {
	{STV_DEFAULT, "DEFAULT"},
	{STV_INTERNAL, "INTERNAL"},
	{STV_HIDDEN, "HIDDEN"},
	{STV_PROTECTED, "PROTECTED"},
	{-1, NULL}
};

static void dump_symbol(void const *const ehdr, void const *const shdr,
	unsigned int i)
{
	void *sym = (void *)((char *)ehdr + SHOFFSET(ehdr, shdr, i));
	void *end = (void *)((char *)sym + SHSIZE(ehdr, shdr, i));
	char *tab = (char *)ehdr + SHOFFSET(ehdr, shdr, SHLINK(ehdr, shdr, i));

	for (unsigned int j = 0; sym < end; j++) {
		printf("   %3i: %016li  %4li ", j,
			STVALUE(ehdr, sym), STSIZE(ehdr, sym));
		print_with_tab(STTYPE(ehdr, sym), TYPES, 7);
		printf(" ");
		print_with_tab(STBIND(ehdr, sym), BINDS, 6);
		printf(" ");
		print_with_tab(STOTHER(ehdr, sym), VISIBILITY, 8);
		if (STSHNDX(ehdr, sym) && STSHNDX(ehdr, sym) != 65521)
			printf(" %-3i ", STSHNDX(ehdr, sym));
		else if (STSHNDX(ehdr, sym))
			printf(" ABS ");
		else
			printf(" UND ");
		printf("%s\n", &tab[STNAME(ehdr, sym)]);
		sym = STNEXT(ehdr, sym);
	}
}

void dump_symbols(void const *const ehdr, void const *const shdr)
{
	for (unsigned int i = 0; i < SHNUM(ehdr); i++) {
		if (SHTYPE(ehdr, shdr, i) == SHT_SYMTAB ||
			SHTYPE(ehdr, shdr, i) == SHT_DYNSYM) {
			printf("\nSymbol table '%s' contains %li entries:\n",
				&(((char *)SHTAB(ehdr, shdr, ehdr))
				[SHNAME(ehdr, shdr, i)]),
				SHENTSIZE(ehdr, shdr, i));
			printf("   Num:    Value          Size Type    Bind");
			printf("   Vis      Ndx Name\n");
			dump_symbol(ehdr, shdr, i);
		}
	}
}