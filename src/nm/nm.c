/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>
#include "nm.h"

const int error_return = 84;

const int success_return = 0;

const char *const default_file = "a.out";

const t_message messages[] = {
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
		fprintf(stderr, messages[error].name, av0, filename);
		return_value = error_return;
	}
	return return_value;
}

unsigned int getSymTabSection(void *const ehdr, void *const shdr,
	unsigned int idx
)
{
	unsigned int i = idx;

	while (i < SHNUM(ehdr)) {
		if (SHTYPE(ehdr, shdr, i) == SHT_SYMTAB)
			return i;
		i++;
	}
	return NO_SYMTAB;
}

static errors manage_file(char const *const filename, int max_idx)
{
	int fd;
	char *data = NULL;
	char *ehdr = NULL;
	void *shdr = NULL;

	if (!is_file(filename))
		return DIRECTORY;
	fd = open(filename, O_RDONLY);
	data = get_data(fd);
	if (!data)
		return NO_FILE;
	ehdr = data;
	if (!is_valid(ehdr, fd))
		return NOT_RECOGNIZED;
	shdr = data + SHOFF(ehdr);
	if (is_truncated(ehdr, shdr, FILESIZE(fd)))
		return TRUNCATED;
	unsigned int i = 0;
	if (max_idx > 2)
		printf("\n%s:\n", filename);
	i = getSymTabSection(ehdr, shdr, i);
	if (i == NO_SYMTAB)
		return NO_SYMTAB;
	while (i != NO_SYMTAB) {
		dump_symbols(ehdr, shdr, i);
		i++;
		i = getSymTabSection(ehdr, shdr, i);
	}
	return SUCCESS;
}

int main(int ac, char **av)
{
	int i = 1;
	int r_value = success_return;
	errors error;

	if (ac > i) {
		while (i < ac) {
			error = manage_file(av[i], ac);
			r_value = dump_error(error, r_value, av[0], av[i]);
			i++;
		}
	} else {
		error = manage_file(default_file, ac);
		r_value = dump_error(error, r_value, av[0], default_file);
	}
	return r_value;
}