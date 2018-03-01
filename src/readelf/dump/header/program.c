/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <stdio.h>
#include <stdlib.h>
#include <message.h>
#include "readelf.h"

static const t_message TYPES[] = {
	{PT_NULL, "NULL"},
	{PT_LOAD, "LOAD"},
	{PT_DYNAMIC, "DYNAMIC"},
	{PT_INTERP, "INTERP"},
	{PT_NOTE, "NOTE"},
	{PT_SHLIB, "SHLIB"},
	{PT_PHDR, "PHDR"},
	{PT_TLS, "TLS"},
	{PT_NUM, "NUM"},
	{PT_LOOS, "LOOS"},
	{PT_GNU_EH_FRAME, "GNU_EH_FRAME"},
	{PT_GNU_STACK, "GNU_STACK"},
	{PT_GNU_RELRO, "GNU_RELRO"},
	{PT_LOSUNW, "LOSUNW"},
	{PT_SUNWBSS, "SUNWBSS"},
	{PT_SUNWSTACK, "SUNWSTACK"},
	{PT_HISUNW, "HISUNW"},
	{PT_HIOS, "HIOS"},
	{PT_LOPROC, "LOPROC"},
	{PT_HIPROC, "HIPROC"},
	{-1, NULL}
};

static const t_message FLAGSTAB[] = {

	{PF_R, "R"},
	{PF_W, "W"},
	{PF_X, "E"},
	{PF_MASKOS, "O"},
	{PF_MASKPROC, "P"},
	{-1, NULL}
};

static void dump_flags(void const *const ehdr, void const *const phdr,
	unsigned int i)
{
	char *flags = strdup("     ");

	for (unsigned int j = 0; FLAGSTAB[j].name; j++) {
		if (PHFLAGS(ehdr, phdr, i) & FLAGSTAB[j].id) {
			flags[j] = FLAGSTAB[j].name[0];
		}
	}
	printf("%s  ", flags);
}

static void dump_sections_link_to_segment(void const *const ehdr,
	void const *const shdr, void const *const phdr, unsigned int idx)
{
	char *tab = (char *)SHTAB(ehdr, shdr, ehdr);
	long unsigned int start = 0;
	long unsigned int end = 0;

	printf("  %02i     ", idx);
	for (unsigned int i = 0; i < SHNUM(ehdr); i++) {
		start = PHOFFSET(ehdr, phdr, idx);
		end = PHOFFSET(ehdr, phdr, idx) + PHFILESZ(ehdr, phdr, idx);

		if (start <= SHOFFSET(ehdr, shdr, i) &&
			SHOFFSET(ehdr, shdr, i) < end &&
			strlen(&(tab[SHNAME(ehdr, shdr, i)]))) {
			printf("%s ", &(tab[SHNAME(ehdr, shdr, i)]));
		}
	}
	printf("\n");
}

void dump_programs(void const *const ehdr, void const *const phdr,
	void const *const shdr)
{
	printf("\nProgram Header:\n");
	printf("  Type           Offset             VirtAddr           ");
	printf("PhysAddr           FileSiz            ");
	printf("MemSiz              Flags  Align\n");
	for (unsigned int i = 0; i < PHNUM(ehdr); i++) {
		printf("  ");
		print_with_tab(PHTYPE(ehdr, phdr, i), TYPES, 14);
		printf(" 0x%016lx 0x%016lx 0x%016lx 0x%016lx 0x%016lx  ",
			PHOFFSET(ehdr, phdr, i), PHVADDR(ehdr, phdr, i),
			PHPADDR(ehdr, phdr, i), PHFILESZ(ehdr, phdr, i),
			PHMEMSZ(ehdr, phdr, i));
		dump_flags(ehdr, phdr, i);
		printf("%lx\n", PHALIGN(ehdr, phdr, i));
	}
	printf("\n Section to Segment mapping:\n  Segment Setions...\n");
	for (unsigned int i = 0; i < PHNUM(ehdr); i++) {
		dump_sections_link_to_segment(ehdr, shdr, phdr, i);
	}
}