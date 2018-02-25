/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include "nm.h"

bool is_data(void const *const ehdr, void const *const shdr,
	void const *const symbol, unsigned int ret
)
{
	unsigned int idx = STSHNDX(ehdr, symbol);
	unsigned int type = SHTYPE(ehdr, shdr, idx);
	long unsigned int flags = SHFLAGS(ehdr, shdr, idx);

	if (type == SHT_PROGBITS && flags == (SHF_ALLOC | SHF_WRITE) &&
		ret == unknown)
		return true;
	if ((type & SHT_NOBITS) == 0 && ret == unknown)
		return true;
	return false;
}