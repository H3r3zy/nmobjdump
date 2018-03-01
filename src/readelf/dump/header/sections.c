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

/*
** Dump sections
*/

static const t_message TYPES[] = {
	{SHT_NULL, "NULL"},
	{SHT_PROGBITS, "PROGBITS"},
	{SHT_NOTE, "NOTE"},
	{SHT_GNU_HASH, "GNU_HASH"},
	{SHT_DYNSYM, "DYNSYM"},
	{SHT_STRTAB, "STRTAB"},
	{SHT_GNU_versym, "VERSYM"},
	{SHT_GNU_verneed, "VERNEED"},
	{SHT_RELA, "RELA"},
	{SHT_INIT_ARRAY, "INIT_ARRAY"},
	{SHT_FINI_ARRAY, "FINI_ARRAY"},
	{SHT_DYNAMIC, "DYNAMIC"},
	{SHT_NOBITS, "NOBITS"},
	{SHT_SYMTAB, "SYMTAB"},
	{SHT_REL, "REL"},
	{SHT_SHLIB, "SHLIB"},
	{SHT_PREINIT_ARRAY, "PREINIT_ARRAY"},
	{SHT_GROUP, "GROUP"},
	{SHT_SYMTAB_SHNDX, "SYMTAB_SHNDX"},
	{SHT_NUM, "NUM"},
	{SHT_LOOS, "LOOS"},
	{SHT_GNU_ATTRIBUTES, "GNU_ATTRIBUTES"},
	{SHT_GNU_LIBLIST, "GNU_LIBLIST"},
	{SHT_CHECKSUM, "CHECKSUM"},
	{SHT_LOSUNW, "LOSUNW"},
	{SHT_SUNW_move, "MOVE"},
	{SHT_SUNW_COMDAT, "SUNW_COMDAT"},
	{SHT_SUNW_syminfo, "SYMINFO"},
	{SHT_GNU_verdef, "VERDEF"},
	{SHT_LOPROC, "LOPROC"},
	{SHT_HIPROC, "HIPROC"},
	{SHT_LOUSER, "LOUSER"},
	{SHT_HIUSER, "HIUSER"},
	{-1, NULL}
};

static const t_message FLAGSTAB[] = {
	{SHF_WRITE, "W"},
	{SHF_ALLOC, "A"},
	{SHF_EXECINSTR, "X"},
	{SHF_MERGE, "M"},
	{SHF_STRINGS, "S"},
	{SHF_INFO_LINK, "I"},
	{SHF_LINK_ORDER, "L"},
	{SHF_OS_NONCONFORMING, "O"},
	{SHF_GROUP, "G"},
	{SHF_TLS, "T"},
	{SHF_COMPRESSED, "C"},
	{SHF_MASKOS, "o"},
	{SHF_MASKPROC, "p"},
	{SHF_ORDERED, "?"},
	{SHF_EXCLUDE, "E"},
	{-1, NULL}
};

/*
** Dump Flags
**
**
*/

static void dump_sections_flags(void const * const ehdr, void const * const shdr, unsigned int idx)
{
	char *flags = strdup("");

	for (unsigned int i = 0; FLAGSTAB[i].name; i++) {
		if (FLAGSTAB[i].id & SHFLAGS(ehdr, shdr, idx)) {
			flags = realloc(flags, strlen(flags) + 1);
			flags = strcat(flags, FLAGSTAB[i].name);
		}
	}
	printf("%3s ", flags);
}

static void dump_section(void const *const ehdr, void const *const shdr,
	unsigned int i)
{
	char *name = malloc(18);

	name[0] = '\0';
	printf("  [%*i] ", calc_int_digits(SHNUM(ehdr)), i);
	printf("%17s ", strncpy(name, &(((char *)(SHTAB(ehdr, shdr,
		ehdr))))[SHNAME(ehdr, shdr, i)], 17));
	print_with_tab(SHTYPE(ehdr, shdr, i), TYPES, 16);
	printf(" %016li ", SHADDR(ehdr, shdr, i));
	printf("%08li ", SHOFFSET(ehdr, shdr, i));
	printf("%016li ", SHSIZE(ehdr, shdr, i));
	printf("%016li ", SHENTSIZE(ehdr, shdr, i));
	dump_sections_flags(ehdr, shdr, i);
	printf("%2i ", SHLINK(ehdr, shdr, i));
	printf("%3i ", SHINFO(ehdr, shdr, i));
	printf("%2li\n", SHADDRALIGN(ehdr, shdr, i));
}

/*
** There are 31 section headers, starting at offset 0xa190:
**
** Section Headers:
**   [Nr] Name              Type             Address           Offset
**        Size              EntSize          Flags  Link  Info  Align
**   [ 0]                   NULL             0000000000000000  00000000
*/
void dump_sections(void const *const ehdr, void const *const shdr)
{
	printf("\nSection Header:\n");
	printf("  [Nr] Name              Type             Address          Offset");
	printf("   Size             EntSize          Flg Lk Inf Al\n");
	for (unsigned int i = 0; i < SHNUM(ehdr); i++) {
		dump_section(ehdr, shdr, i);
	}
	printf("Key to Flags:\n");
	printf("  W (write), A (alloc), X (execute), M (merge), S (strings)");
	printf("\n  I (info), L (link order), G (group), T (TLS), E ");
	printf("(exclude), x (unknown)\n  O (extra OS processing required) o");
	printf("(OS specific), p (processor specific)\n");
}