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

const t_message flags[] = {
	{HAS_RELOC, "HAS_RELOC"},
	{EXEC_P, "EXEC_P"},
	{HAS_SYMS, "HAS_SYMS"},
	{HAS_DEBUG, "HAS_DEBUG"},
	{DYNAMIC, "DYNAMIC"},
	{D_PAGED, "D_PAGED"},
	{HAS_LINENO, "HAS_LINENO"},
	{HAS_LOCALS, "HAS_LOCALS"},
	{WP_TEXT, "WP_TEXT"},
	{-1, NULL}
};

static bool hasrela(SHdr64 *shdr, char const *shtab, unsigned int shnum)
{
	for (unsigned int i = 0; i < shnum; i++) {
		if ((shdr[i].sh_type == SHT_RELA ||
			shdr[i].sh_type == SHT_REL) &&
			strcmp(&shtab[shdr[i].sh_name], ".rela.plt") != 0 &&
			strcmp(&shtab[shdr[i].sh_name], ".rel.plt") != 0 &&
			strcmp(&shtab[shdr[i].sh_name], ".rela.dyn") != 0 &&
			strcmp(&shtab[shdr[i].sh_name], ".rel.syn") != 0)
			return true;
	}
	return false;
}

static bool hasdebug(SHdr64 *shdr, unsigned int shnum)
{
	for (unsigned int i = 0; i < shnum; i++) {
		if (shdr[i].sh_type == SHT_MIPS_DEBUG)
			return true;
	}
	return false;
}

static bool hassyms(SHdr64 *shdr, unsigned int shnum)
{
	for (unsigned int i = 0; i < shnum; i++) {
		if (shdr[i].sh_type == SHT_SYMTAB)
			return true;
	}
	return false;
}

long int flag_gestion(EHdr64 *ehdr, SHdr64 *shdr, char const *shtab)
{
	long int flag = BFD_NO_FLAGS;
	if (ehdr->e_phnum)
		flag += D_PAGED;
	if (ehdr->e_type == ET_EXEC)
		flag += EXEC_P;
	if (ehdr->e_type == ET_DYN)
		flag += DYNAMIC;
	if (hasrela(shdr, shtab, ehdr->e_shnum))
		flag += HAS_RELOC;
	if (hasdebug(shdr, ehdr->e_shnum))
		flag += HAS_DEBUG;
	if (hassyms(shdr, ehdr->e_shnum))
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