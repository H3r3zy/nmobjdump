/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <stdio.h>
#include "objdump.h"

const t_message machines[] = {
	{EM_NONE, "None"},
	{EM_M32, "WE32100"},
	{EM_SPARC, "Sparc"},
	{EM_386, "Intel 80386"},
	{EM_68K, "MC68000"},
	{EM_88K, "MC88000"},
	{EM_860, "Intel 80860"},
	{EM_MIPS, "MIPS R3000"},
	{EM_PARISC, "HPPA"},
	{EM_SPARC32PLUS, "Sparc v8+"},
	{EM_PPC, "PowerPC"},
	{EM_PPC64, "PowerPC64"},
	{EM_S390, "IBM S/390"},
	{EM_ARM, "ARM"},
	{EM_SH, "Renesas / SuperH SH"},
	{EM_SPARCV9, "Sparc v9"},
	{EM_IA_64, "Intel IA-64"},
	{EM_X86_64, "i386:x86-64"},
	{-1, NULL}
};

void dump_header(void *ehdr, void *shdr, char const *shtab,
	char const *const filename
)
{
	long int flag = flag_gestion(ehdr, shdr, shtab);
	char *format = (IS64(ehdr)) ? ("elf64-x86-64") : ("elf32-i386");

	printf("\n%s:     file format %s\n", filename, format);
	printf("architecture: ");
	for (int i = 0; machines[i].name; i++) {
		if (MACHINE(ehdr) == machines[i].id)
			printf("%s", machines[i].name);
	}
	printf(", flags 0x%08lx:\n", flag);
	dump_flag(flag);
	printf("\n");
	printf("start address 0x%016lx\n\n", ENTRY(ehdr));
}