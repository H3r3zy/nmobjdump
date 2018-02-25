/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include "readelf.h"

void dump_elf(void const *const ehdr,
	void const *const shdr __attribute__((unused)))
{
	dump_header(ehdr);
}