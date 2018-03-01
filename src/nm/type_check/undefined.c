/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include "nm.h"

bool is_undefined(void const *const ehdr,
	void const *const shdr __attribute__((unused)),
	void const *const symbol, unsigned int ret
)
{
	if (STVALUE(ehdr, symbol) == 0 && ret == UNKNOWN)
		return true;
	return false;
}