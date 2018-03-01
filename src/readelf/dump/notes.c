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

static const t_message DESC_GNU[] = {
	{0, "Linux"},
	{1, "Hurd"},
	{2, "Solaris"},
	{3, "FreeBSD"},
	{4, "NetBSD"},
	{5, "Syllable"},
	{6, "NaCl"},
	{-1, NULL}
};

static void dump_desc(void const *const ehdr, char const *const note,
	char const *const desc)
{
	for (unsigned int i = 0; i < NDESCSZ(ehdr, note); i++) {
		printf("%02x", desc[i] & 0xff);
	}
	printf("\n");
}

static int get_desc_value(char const *const desc, unsigned int size) {
	int tmp = desc[0];

	for (; size > 1; size--) {
		tmp |= desc[size - 1] << (size - 1) * 8;
	}
	return tmp;
}

static void dump_nt(void const *const ehdr, char const *const note)
{
	char const *const desc = note + NSIZEOF(ehdr) + NNAMESZ(ehdr, note);

	switch (NTYPE(ehdr, note)) {
	case NT_GNU_BUILD_ID:
		printf("NT_GNU_BUILD_ID (unique build ID bitstring)\n    %s",
			"Build ID: ");
		dump_desc(ehdr, note, desc);
		printf("\n");
		break;
	case NT_GNU_ABI_TAG:
		printf("NT_GNU_ABI_TAG (ABI version tag)\n    OS: ");
		print_with_tab(get_desc_value(desc, 4) , DESC_GNU, -1);
		printf(", ABI: %i.%i.%i\n", get_desc_value(&desc[4], 4),
		get_desc_value(&desc[8], 4), get_desc_value(&desc[12], 4));
		break;
	case NT_GNU_HWCAP:
		printf("NT_GNU_HWCAP (DSO-supplied software HWCAP info)\n");
		break;
	case NT_GNU_GOLD_VERSION:
		printf("NT_GNU_GOLD_VERSION (gold version)\n    Version: %s\n",
		desc);
		break;
	}

}

static void dump_note_section(void const *const ehdr, void const *const shdr,
	unsigned int idx)
{
	char *note = (char *) ehdr + SHOFFSET(ehdr, shdr, idx);
	char *end = note + SHSIZE(ehdr, shdr, idx);

	for (unsigned int i = 0; note < end; i++) {
		printf("  %-20s 0x%08x       ", note + NSIZEOF(ehdr),
			NDESCSZ(ehdr, note));
		dump_nt(ehdr, note);
		note += NSIZEOF(ehdr) + NNAMESZ(ehdr, note) + NDESCSZ(ehdr, note);
	}

}

void dump_notes_section(void const *const ehdr, void const *const shdr)
{
	for (unsigned int i = 0; i < SHNUM(ehdr); i++) {
		if (SHTYPE(ehdr, shdr, i) == SHT_NOTE) {
			printf("\nDisplaying notes found at file offset 0x");
			printf("%08lx with length 0x%08lx:\n",
				SHOFFSET(ehdr, shdr, i),
				SHSIZE(ehdr, shdr, i));
			printf("  Owner                 Data size       ");
			printf("Description\n");
			dump_note_section(ehdr, shdr, i);
		}
	}
}