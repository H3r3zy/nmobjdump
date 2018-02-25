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

void dump_elf(void const *const ehdr, void const *const shdr);
void dump_header(void const *const ehdr);

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
