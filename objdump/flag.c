/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <stdio.h>
#include <string.h>
#include "objdump.h"
#include "flag.h"

const t_message flags[] = {{HAS_RELOC, "HAS_RELOC"}, {EXEC_P, "EXEC_P"},
	{HAS_SYMS, "HAS_SYMS"}, {HAS_DEBUG, "HAS_DEBUG"}, {DYNAMIC, "DYNAMIC"},
	{D_PAGED, "D_PAGED"}, {HAS_LINENO, "HAS_LINENO"},
	{HAS_LOCALS, "HAS_LOCALS"}, {WP_TEXT, "WP_TEXT"}, {-1, NULL}};

static bool hasrela(void *ehdr, void *shdr, char const *shtab,
	unsigned int shnum
)
{
	for (unsigned int i = 0; i < shnum; i++) {
		if ((SHTYPE(ehdr, shdr, i) == SHT_RELA ||
			SHTYPE(ehdr, shdr, i) == SHT_REL) &&
			strcmp(&shtab[SHNAME(ehdr, shdr, i)], ".rela.plt") &&
			strcmp(&shtab[SHNAME(ehdr, shdr, i)], ".rel.plt") &&
			strcmp(&shtab[SHNAME(ehdr, shdr, i)], ".rela.dyn") &&
			strcmp(&shtab[SHNAME(ehdr, shdr, i)], ".rel.syn"))
			return true;
	}
	return false;
}

static bool hasdebug(void *ehdr, void *shdr, unsigned int shnum)
{
	for (unsigned int i = 0; i < shnum; i++) {
		if (SHTYPE(ehdr, shdr, i) == SHT_MIPS_DEBUG)
			return true;
	}
	return false;
}

static bool hassyms(void *ehdr, void *shdr, unsigned int shnum)
{
	for (unsigned int i = 0; i < shnum; i++) {
		if (SHTYPE(ehdr, shdr, i) == SHT_SYMTAB)
			return true;
	}
	return false;
}

long int flag_gestion(void *ehdr, void *shdr, char const *shtab)
{
	long int flag = BFD_NO_FLAGS;
	if (PHNUM(ehdr))
		flag += D_PAGED;
	if (TYPE(ehdr) == ET_EXEC)
		flag += EXEC_P;
	if (TYPE(ehdr) == ET_DYN)
		flag += DYNAMIC;
	if (hasrela(ehdr, shdr, shtab, SHNUM(ehdr)))
		flag += HAS_RELOC;
	if (hasdebug(ehdr, shdr, SHNUM(ehdr)))
		flag += HAS_DEBUG;
	if (hassyms(ehdr, shdr, SHNUM(ehdr)))
		flag += HAS_SYMS;
	return flag;
}

void dump_flag(long int flag)
{
	bool first = true;

	for (unsigned int i = 0; flags[i].name; i++) {
		if (flag & flags[i].id && first == false)
			printf(", ");
		if (flag & flags[i].id) {
			printf("%s", flags[i].name);
			first = false;
		}
	}
}