/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <stdio.h>
#include "readelf.h"

void dump_elf(void const *const ehdr,
	void const *const shdr,
	void const *const phdr)
{
	dump_header(ehdr);
	printf("\n");
	dump_sections(ehdr, shdr);
	dump_programs(ehdr, phdr, shdr);
	dump_relas(ehdr, shdr);
	dump_symbols(ehdr, shdr);
	dump_notes_section(ehdr, shdr);
}