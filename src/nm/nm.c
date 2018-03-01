/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>
#include "nm.h"

static const int ERROR_RETURN = 84; // OK

static const int SUCCESS_RETURN = 0; // KO

static const char *const DEFAULT_FILE = "a.out"; // OK

static const t_message MESSAGES[] = { // OK
	{SUCCESS, "Success"},
	{DIRECTORY, "%s: Warning: '%s' is a directory\n"},
	{NOT_RECOGNIZED, "%s: %s: File format not recognized\n"},
	{TRUNCATED, "%s: %s: File truncated\n"},
	{NO_FILE, "%s: '%s': No such file\n"},
	{NO_SYMTAB, "%s: %s: No symbols\n"}
};

static int dump_error(errors error, int return_value, char const *const av0,
	char const *const filename
)
{
	if (error) {
		fprintf(stderr, MESSAGES[error].name, av0, filename);
		return_value = ERROR_RETURN;
	}
	return return_value;
}

static int getSymTabSection(void const *const ehdr, void const *const shdr,
	unsigned int idx
)
{
	unsigned int i = idx;

	while (i < SHNUM(ehdr)) {
		if (SHTYPE(ehdr, shdr, i) == SHT_SYMTAB)
			return i;
		i++;
	}
	return -1;
}

static errors dump_symtab(void const *const ehdr, void const *const shdr) {
	int i = getSymTabSection(ehdr, shdr, 0);

	if (i == -1)
		return NO_SYMTAB;
	while (i != -1) {
		dump_symbols(ehdr, shdr, i);
		i++;
		i = getSymTabSection(ehdr, shdr, i);
	}
	return SUCCESS;
}

static errors manage_file(char const *const filename, int max_idx)
{
	int fd;
	char *ehdr = NULL;
	void *shdr = NULL;

	if (!is_file(filename))
		return DIRECTORY;
	fd = open(filename, O_RDONLY);
	ehdr = get_data(fd);
	if (!ehdr || !is_valid(ehdr, fd))
		return !ehdr ? NO_FILE : NOT_RECOGNIZED;
	shdr = ehdr + SHOFF(ehdr);
	if (is_truncated(ehdr, shdr, FILESIZE(fd)))
		return TRUNCATED;
	if (max_idx > 2)
		printf("\n%s:\n", filename);
	return dump_symtab(ehdr, shdr);
}

int main(int ac, char **av)
{
	int i = 1;
	int r_value = SUCCESS_RETURN;
	errors error;

	if (ac > i) {
		while (i < ac) {
			error = manage_file(av[i], ac);
			r_value = dump_error(error, r_value, av[0], av[i]);
			i++;
		}
	} else {
		error = manage_file(DEFAULT_FILE, ac);
		r_value = dump_error(error, r_value, av[0], DEFAULT_FILE);
	}
	return r_value;
}