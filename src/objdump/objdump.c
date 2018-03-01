/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <elf.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <objdump.h>

static const int ERROR_RETURN = 84;

static const int SUCCESS_RETURN = 0;

static const char *const DEFAULT_FILE = "a.out";

static const t_message MESSAGES[] = {{SUCCESS, "Success"},
	{DIRECTORY, "%s: Warning: '%s' is a directory\n"},
	{NOT_RECOGNIZED, "%s: %s: File format not recognized\n"},
	{TRUNCATED, "%s: %s: File truncated\n"},
	{NO_FILE, "%s: '%s': No such file\n"}};

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

static errors manage_file(char const *const filename)
{
	int fd;
	char *data = NULL;
	char *ehdr = NULL;
	ptr shdr = NULL;

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
	dump_header(ehdr, shdr, (ptr)SHTAB(data, shdr, ehdr), filename);
	dump_sections(data, shdr, (ptr)SHTAB(data, shdr, ehdr), SHNUM(ehdr));
	return SUCCESS;
}

int main(int ac, char **av)
{
	int i = 1;
	int r_value = SUCCESS_RETURN;
	errors error;

	if (ac > i) {
		while (i < ac) {
			error = manage_file(av[i]);
			r_value = dump_error(error, r_value, av[0], av[i]);
			i++;
		}
	} else {
		error = manage_file(DEFAULT_FILE);
		r_value = dump_error(error, r_value, av[0], DEFAULT_FILE);
	}
	return (r_value);
}
