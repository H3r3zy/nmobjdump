/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#ifndef PSU_2017_NMOBJDUMP_NM_H
#define PSU_2017_NMOBJDUMP_NM_H

#include <elf.h>
#include "message.h"
#include "elf_file.h"

/*
** Errors
*/

typedef enum errors {
	SUCCESS = 0,
	DIRECTORY = 1,
	NOT_RECOGNIZED = 2,
	TRUNCATED = 3,
	NO_FILE = 4,
	NO_SYMTAB = 5,
} errors;

#endif //PSU_2017_NMOBJDUMP_NM_H
