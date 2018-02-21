/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include "objdump.h"

void *getData(int fd)
{
	void *data = NULL;

	if (fd == -1)
		return NULL;
	data = mmap(NULL, FILESIZE(fd), PROT_READ, MAP_SHARED, fd, 0);
	return data;
}

unsigned int calc_hex_digits(long int n)
{
	unsigned int digits;

	digits = sizeof(n);
	while (digits > 0 && !((0xf << ((digits - 1) * 4)) & n))
		digits--;
	return (digits);
}

bool isValid(EHdr64 *ehdr, int fd)
{
	if ((unsigned long int)FILESIZE(fd) < sizeof(EHdr64))
		return false;
	return (VALIDMAG(ehdr) == true && VALIDVERSION64(ehdr) == true) ?
		true : false;
}