/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
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

static bool isNotInMemory(void *ehdr, long int f_size, void *test)
{
	if ((char *)test > (char *)ehdr + f_size)
		return true;
	return false;
}

bool isTrunced(void *ehdr, void *shdr, long int f_size)
{
	int i = 0;
	char *shtab = NULL;

	if (isNotInMemory(ehdr, f_size, shdr))
		return true;
	shtab = (char *)(ehdr + SHOFFSET(ehdr, shdr, SHSTRNDX(ehdr)));
	if (isNotInMemory(ehdr, f_size, shtab))
		return true;
	while (i < SHNUM(ehdr)) {
		if (IS32(ehdr) && isNotInMemory(ehdr, f_size, &((SHdr32 *)shdr)[i]))
			return true;
		if (IS64(ehdr) && isNotInMemory(ehdr, f_size, &((SHdr64 *)shdr)[i]))
			return true;
		if (isNotInMemory(ehdr, f_size, &shtab[SHNAME(ehdr, shdr, i)]))
			return true;
		i++;
	}
	return false;
}