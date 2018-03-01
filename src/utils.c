/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <unistd.h>
#include <stdio.h>
#include "objdump.h"

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

unsigned int calc_int_digits(size_t n)
{
	unsigned int digits;
	unsigned int i;

	digits = 9;
	i = 1;
	while (digits < n) {
		i++;
		digits += powi(10, i);
	}
	return i;
}

bool is_valid(void *ehdr, int fd)
{
	if ((unsigned long int)FILESIZE(fd) < sizeof(EHdr32))
		return false;
	return (VALIDMAG(ehdr) == true && VALIDVERSION(ehdr) == true) ? true :
		false;
}

/*
** Print data in function of a value and a tab
** tab[]: {int id, char *name}
** value == id > print name
*/
void print_with_tab(int value, t_message const *const tab, int size) {
	for (unsigned int i = 0; tab[i].name; i++) {
		if (tab[i].id == value)
			printf("%-*s", size, tab[i].name);
	}

}