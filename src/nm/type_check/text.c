/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include "nm.h"

bool is_text(void const *const ehdr, void const *const shdr,
	void const *const symbol, unsigned int ret
)
{
	unsigned int idx = STSHNDX(ehdr, symbol);
	unsigned int type = SHTYPE(ehdr, shdr, idx);
	long unsigned int flags = SHFLAGS(ehdr, shdr, idx);
	char const *const sh_name = SECTIONNAME(ehdr, shdr, symbol);

	if (type == SHT_PROGBITS && flags == (SHF_ALLOC | SHF_EXECINSTR) &&
		ret == unknown)
		return true;
	if (0 == strncmp(sh_name, ".init", 5) ||
		0 == strncmp(sh_name, ".fini", 5) ||
		0 == strncmp(sh_name, ".text", 5))
		return true;
	return false;
}