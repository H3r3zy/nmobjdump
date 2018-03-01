/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include "nm.h"

bool is_common(void const *const ehdr,
	void const *const shdr __attribute__((unused)),
	void const *const symbol, unsigned int ret
)
{
	if (STSHNDX(ehdr, symbol) == SHN_COMMON && ret == UNKNOWN)
		return true;
	return false;
}