/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#ifndef PSU_2017_NMOBJDUMP_NM_H
#define PSU_2017_NMOBJDUMP_NM_H

#include "message.h"
#include "elf_file.h"

extern const unsigned int UNKNOWN;

void dump_symbols(void const *const ehdr, void const *const shdr, int i);
unsigned int get_type(void const *const ehdr, void const *const shdr,
	void const *const symbol);

/*
** Type gestion
*/

typedef struct {
	unsigned int key;
	bool (*func)(void const *const, void const *const,
		void const *const, unsigned int);
} type;

bool is_undefined(void const *const ehdr,
	void const *const shdr __attribute__((unused)),
	void const *const symbol, unsigned int ret);

bool is_common(void const *const ehdr,
	void const *const shdr __attribute__((unused)),
	void const *const symbol, unsigned int ret);

bool is_absolute(void const *const ehdr,
	void const *const shdr __attribute__((unused)),
	void const *const symbol, unsigned int ret);

bool is_bss(void const *const ehdr, void const *const shdr,
	void const *const symbol, unsigned int ret);

bool is_readonly(void const *const ehdr, void const *const shdr,
	void const *const symbol, unsigned int ret);

bool is_data(void const *const ehdr, void const *const shdr,
	void const *const symbol, unsigned int ret);

bool is_text(void const *const ehdr, void const *const shdr,
	void const *const symbol, unsigned int ret);

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
