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
#include <elf.h>
#include <ctype.h>
#include "nm.h"

const int error_return = 84;

const int success_return = 0;

const char *const default_file = "a.out";

const t_message messages[] = {{SUCCESS, "Success"},
	{DIRECTORY, "%s: Warning: '%s' is a directory\n"},
	{NOT_RECOGNIZED, "%s: %s: File format not recognized\n"},
	{TRUNCATED, "%s: %s: File truncated\n"},
	{NO_FILE, "%s: '%s': No such file\n"},
	{NO_SYMTAB, "%s: %s: No symbols\n"}};

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

bool displayable(void *ehdr, void *symbol)
{
	int type = STTYPE(ehdr, symbol);

	if (type == STT_FILE)
		return false;
	if ((STVALUE(ehdr, symbol) && STSIZE(ehdr, symbol)) ||
		STNAME(ehdr, symbol))
		return true;
	return false;
}

static int dump_type(void *const ehdr, void *const shdr, void *const symbol)
{
	int ret = '?';

	if (STSHNDX(ehdr, symbol) == SHN_UNDEF)
		return 'u';
	if (STBIND(ehdr, symbol) == STB_WEAK) {
		ret = STTYPE(ehdr, symbol) == STT_OBJECT ? 'v' : 'w';
		ret = STVALUE(ehdr, symbol) ? toupper(ret) : ret;
		return ret;
	}
	ret = ISUNDEFINED(ehdr, symbol, ret);
	ret = ISCOMMON(ehdr, symbol, ret);
	ret = ISABSOLUTE(ehdr, symbol, ret);
	ret = ISBSS(ehdr, shdr, symbol, ret);
	ret = ISREADONLY(ehdr, shdr, symbol, ret);
	ret = ISDATA(ehdr, shdr, symbol, ret);
	ret = ISTEXT(ehdr, shdr, symbol, ret);
	if (STBIND(ehdr, symbol) == STB_GLOBAL)
		return toupper(ret);
	return ret;
}

void dump_symbol(void *const ehdr, void *const shdr, int i)
{
	void *symbol = (void *)((char *)ehdr + SHOFFSET(ehdr, shdr, i));
	void *end = (void *)((char *)symbol + SHSIZE(ehdr, shdr, i));
	int link = SHLINK(ehdr, shdr, i);
	long unsigned int value = 0;
	char *strtab = (char *)ehdr + SHOFFSET(ehdr, shdr, link);

	while (symbol < end) {
		if (displayable(ehdr, symbol) == true) {
			value = STVALUE(ehdr, symbol);
			if (IS64(ehdr) == true && value != 0)
				printf("%016lx ", value);
			else if (IS32(ehdr) == true && value != 0)
				printf("%08lx ", value);
			else if (IS64(ehdr) == true)
				printf("                 ");
			else
				printf("         ");
			printf("%c", dump_type(ehdr, shdr, symbol));
			printf(" %s\n", &strtab[STNAME(ehdr, symbol)]);
		}
		symbol = STNEXT(ehdr, symbol);
	}
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
		dump_symbol(ehdr, shdr, i);
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