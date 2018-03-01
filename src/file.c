/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include "objdump.h"

bool is_file(const char *const name)
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
	int i = SHNUM(ehdr) - 1;

	if (is_not_in_memory(ehdr, f_size, shdr))
		return true;
	if (IS32(ehdr) && is_not_in_memory(ehdr, f_size,
		(char *)&((SHdr32 *)shdr)[i] + sizeof(SHdr32)))
		return true;
	if (IS64(ehdr) && is_not_in_memory(ehdr, f_size,
		(char *)&((SHdr64 *)shdr)[i] + sizeof(SHdr64)))
		return true;
	if ((unsigned int)SHOFFSET(ehdr, shdr, i) +
		(unsigned int)SHSIZE(ehdr, shdr, i) > f_size &&
		SHTYPE(ehdr, shdr, i) != SHT_NOBITS)
		return true;
	return false;
}


void *get_data(int fd)
{
	void *data = NULL;

	if (fd == -1)
		return NULL;
	data = mmap(NULL, FILESIZE(fd), PROT_READ, MAP_SHARED, fd, 0);
	return data;
}