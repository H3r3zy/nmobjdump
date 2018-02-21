/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <dirent.h>
#include <stdlib.h>
#include "objdump.h"

bool isFile(const char *name)
{
	DIR *directory = opendir(name);

	if (directory != NULL) {
		closedir(directory);
		return false;
	}
	return true;
}

static bool isNotInMemory(EHdr64 *ehdr, long int f_size, void *test)
{
	if ((char *)test > (char *)ehdr + f_size)
		return true;
	return false;
}

bool isTrunced(EHdr64 *ehdr, SHdr64 *shdr, long int f_size)
{
	int i = 0;
	char *shtab = NULL;

	if (isNotInMemory(ehdr, f_size, shdr))
		return true;
	shtab = (char *)ehdr + shdr[ehdr->e_shstrndx].sh_offset;
	if (isNotInMemory(ehdr, f_size, shtab))
		return true;

	while (i < ehdr->e_shnum) {
		if (isNotInMemory(ehdr, f_size, &shdr[i]))
			return true;
		if (isNotInMemory(ehdr, f_size, &shtab[shdr[i].sh_name]))
			return true;
		i++;
	}
	return false;
}