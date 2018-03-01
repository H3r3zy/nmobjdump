/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#ifndef PSU_2017_NMOBJDUMP_READELF_H
#define PSU_2017_NMOBJDUMP_READELF_H

#include "message.h"
#include "elf_file.h"

/*
** Dump
*/

void dump_elf(void const *const ehdr, void const *const shdr,
	void const *const phdr);
void dump_header(void const *const ehdr);
void dump_sections(void const *const ehdr, void const *const shdr);
void print_with_tab(int value, t_message const *const tab, int size);
void dump_symbols(void const *const ehdr, void const *const shdr);
void dump_relas(void const *const ehdr, void const *const shdr);
void dump_programs(void const *const ehdr, void const *const phdr,
	void const *const shdr);
void dump_notes_section(void const *const ehdr, void const *const shdr);

/*
** Utils
*/

unsigned int calc_int_digits(size_t n);

/*
** Errors
*/

typedef enum errors {
	SUCCESS = 0,
	DIRECTORY = 1,
	NOT_RECOGNIZED = 2,
	TRUNCATED = 3,
	NO_FILE = 4
} errors;

/*
** Header information
*/

#define DATAINFO(ehdr) \
(IDENT(ehdr, EI_DATA) == ELFDATA2LSB ? \
"2's complement, little endian" : \
"2's complement, big endian")

#define VERSIONINFO(ehdr) \
(IDENT(ehdr, EI_VERSION) == EV_CURRENT ? \
"1 (current)" : \
"0 (invalid")

#endif //PSU_2017_NMOBJDUMP_READELF_H
