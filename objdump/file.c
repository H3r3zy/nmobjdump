/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <dirent.h>
#include <stdio.h>
#include "objdump.h"

bool is_file(const char *name)
{
	DIR *directory = opendir(name);

	if (directory != NULL) {
		closedir(directory);
		return false;
	}
	return true;
}

static bool is_not_in_memory(void *ehdr, long int f_size, void *test)
{
	if ((char *)test > (char *)ehdr + f_size)
		return true;
	return false;
}

bool is_truncated(void *ehdr, void *shdr, long int f_size)
{
	int i = 0;
	char *shtab = NULL;

	if (is_not_in_memory(ehdr, f_size, shdr))
		return true;
	shtab = (char *)(ehdr + SHOFFSET(ehdr, shdr, SHSTRNDX(ehdr)));
	if (is_not_in_memory(ehdr, f_size, shtab))
		return true;
	while (i <= SHNUM(ehdr)) {
		if (IS32(ehdr) &&
			is_not_in_memory(ehdr, f_size, &((SHdr32 *)shdr)[i]))
			return true;
		if (IS64(ehdr) &&
			is_not_in_memory(ehdr, f_size, &((SHdr64 *)shdr)[i]))
			return true;
		if (is_not_in_memory(ehdr, f_size,
			&shtab[SHNAME(ehdr, shdr, i)]))
			return true;
		if (is_not_in_memory(ehdr, f_size,
			(char *)ehdr + (SHOFFSET(ehdr, shdr, i)) +
				SHSIZE(ehdr, shdr, i)))
			return true;
		i++;
	}
	return false;
}