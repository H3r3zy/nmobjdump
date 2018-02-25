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

void *get_data(int fd)
{
	void *data = NULL;

	if (fd == -1)
		return NULL;
	data = mmap(NULL, FILESIZE(fd), PROT_READ, MAP_SHARED, fd, 0);
	return data;
}

static unsigned int powi(int n, unsigned int p) {
	unsigned int ret = 1;

	while (p) {
		ret *= n;
		p--;
	}
	return ret;
}

unsigned int calc_hex_digits(size_t n)
{
	unsigned int digits;
	unsigned int i;

	digits = 0xFFFF;
	i = 4;
	while (digits < n) {
		i++;
		digits += powi(0xF, i);
	}
	return (i);
}

bool is_valid(void *ehdr, int fd)
{
	if ((unsigned long int)FILESIZE(fd) < sizeof(EHdr32))
		return false;
	return (VALIDMAG(ehdr) == true && VALIDVERSION(ehdr) == true) ? true :
		false;
}