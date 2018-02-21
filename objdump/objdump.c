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

const int error_return = 84;

const int success_return = 0;

const char *const default_file = "a.out";

const t_message messages[] = {{SUCCESS, "Success"},
	{DIRECTORY, "%s: Warning: '%s' is a directory\n"},
	{NOT_RECOGNIZED, "%s: %s: File format not recognized\n"},
	{TRUNCATED, "%s: %s: File truncated\n"},
	{NO_FILE, "%s: '%s': No such file\n"}};

static int dump_error(errors error, int return_value, char const *const av0,
	char const *const filename
)
{
	if (error) {
		printf(messages[error].name, av0, filename);
		return_value = error_return;
	}
	return return_value;
}

static errors manage_file(char const *const filename)
{
	int fd;
	char *data = NULL;
	EHdr64 *ehdr = NULL;
	SHdr64 *shdr = NULL;

	if (!isFile(filename))
		return DIRECTORY;
	fd = open(filename, O_RDONLY);
	data = getData(fd);
	if (!data)
		return NO_FILE;
	ehdr = (EHdr64 *)data;
	if (!isValid(ehdr, fd))
		return NOT_RECOGNIZED;
	shdr = (SHdr64 *)(data + ehdr->e_shoff);
	if (isTrunced(ehdr, shdr, FILESIZE(fd)))
		return TRUNCATED;
	dump_header(ehdr, shdr, SHTAB(data, shdr, ehdr), filename);
	dump_sections(data, shdr, SHTAB(data, shdr, ehdr), ehdr->e_shnum);
	return SUCCESS;
}

int main(int ac, char **av)
{
	int i = 1;
	int r_value = success_return;
	errors error;

	if (ac > i) {
		while (i < ac) {
			error = manage_file(av[i]);
			r_value = dump_error(error, r_value, av[0], av[i]);
			i++;
		}
	} else {
		error = manage_file(default_file);
		r_value = dump_error(error, r_value, av[0], default_file);
	}
	return (r_value);
}
