/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#ifndef PSU_2017_NMOBJDUMP_OBJDUMP_H
#define PSU_2017_NMOBJDUMP_OBJDUMP_H

#include <elf.h>
#include "message.h"
#include "elf_file.h"

typedef void * ptr;

unsigned int calc_hex_digits(long int n);

long int flag_gestion(void *, void *, char const *);

/*
** Dump
*/
void dump_sections(void *, void *, char const *, int);

void dump_flag(long int);

void dump_header(void *, void *, char const *, char const *const);

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

#endif //PSU_2017_NMOBJDUMP_OBJDUMP_H
