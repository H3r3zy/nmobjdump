/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include "nm.h"

bool is_bss(void const *const ehdr, void const *const shdr,
	void const *const symbol, unsigned int ret
)
{
	unsigned int idx = STSHNDX(ehdr, symbol);
	unsigned int type = SHTYPE(ehdr, shdr, idx);
	long unsigned int flags = SHFLAGS(ehdr, shdr, idx);
	const char *const sh_name = SECTIONNAME(ehdr, shdr, symbol);

	if (type == SHT_NOBITS && flags == (SHF_ALLOC | SHF_WRITE) &&
		ret == UNKNOWN)
		return true;
	if (0 == strncmp(sh_name, ".bss", 4) ||
		0 == strncmp(sh_name, ".tbss", 5))
		return true;
	return false;
}