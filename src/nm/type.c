/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <ctype.h>
#include <nm.h>

const unsigned int unknown = '?';

static bool is_undefined(void const *const ehdr,
	void const *const shdr __attribute__((unused)),
	void const *const symbol, unsigned int ret
)
{
	if (STVALUE(ehdr, symbol) == 0 && ret == unknown)
		return true;
	return false;
}

static bool is_common(void const *const ehdr,
	void const *const shdr __attribute__((unused)),
	void const *const symbol, unsigned int ret
)
{
	if (STSHNDX(ehdr, symbol) == SHN_COMMON && ret == unknown)
		return true;
	return false;
}

static bool is_absolute(void const *const ehdr,
	void const *const shdr __attribute__((unused)),
	void const *const symbol, unsigned int ret
)
{
	if (STSHNDX(ehdr, symbol) == SHN_ABS && ret == unknown)
		return true;
	return false;
}

static bool is_bss(void const *const ehdr, void const *const shdr,
	void const *const symbol, unsigned int ret
)
{
	unsigned int idx = STSHNDX(ehdr, symbol);
	unsigned int type = SHTYPE(ehdr, shdr, idx);
	long unsigned int flags = SHFLAGS(ehdr, shdr, idx);
	const char *const sh_name = SECTIONNAME(ehdr, shdr, symbol);

	if (type == SHT_NOBITS && flags == (SHF_ALLOC | SHF_WRITE) &&
		ret == unknown)
		return true;
	if (0 == strncmp(sh_name, ".bss", 4) ||
		0 == strncmp(sh_name, ".tbss", 5))
		return true;
	return false;
}

static bool is_readonly(void const *const ehdr, void const *const shdr,
	void const *const symbol, unsigned int ret
)
{
	unsigned int idx = STSHNDX(ehdr, symbol);
	unsigned int type = SHTYPE(ehdr, shdr, idx);
	long unsigned int flags = SHFLAGS(ehdr, shdr, idx);

	if (type == SHT_PROGBITS && flags == SHF_ALLOC && ret == unknown)
		return true;
	if (flags == 0 && ret == unknown)
		return true;
	return false;
}

static bool is_data(void const *const ehdr, void const *const shdr,
	void const *const symbol, unsigned int ret
)
{
	unsigned int idx = STSHNDX(ehdr, symbol);
	unsigned int type = SHTYPE(ehdr, shdr, idx);
	long unsigned int flags = SHFLAGS(ehdr, shdr, idx);

	if (type == SHT_PROGBITS && flags == (SHF_ALLOC | SHF_WRITE) &&
		ret == unknown)
		return true;
	if ((type & SHT_NOBITS) == 0 && ret == unknown)
		return true;
	return false;
}

static bool is_text(void const *const ehdr, void const *const shdr,
	void const *const symbol, unsigned int ret
)
{
	unsigned int idx = STSHNDX(ehdr, symbol);
	unsigned int type = SHTYPE(ehdr, shdr, idx);
	long unsigned int flags = SHFLAGS(ehdr, shdr, idx);
	char const *const sh_name = SECTIONNAME(ehdr, shdr, symbol);

	if (type == SHT_PROGBITS && flags == (SHF_ALLOC | SHF_EXECINSTR) &&
		ret == unknown)
		return true;
	if (0 == strncmp(sh_name, ".init", 5) ||
		0 == strncmp(sh_name, ".fini", 5) ||
		0 == strncmp(sh_name, ".text", 5))
		return true;
	return false;
}

const type types[] = {{'u', &is_undefined}, {'c', &is_common},
	{'a', &is_absolute}, {'b', &is_bss}, {'r', &is_readonly},
	{'d', &is_data}, {'t', &is_text}, {'?', NULL}};

unsigned int get_type(void const *const ehdr, void const *const shdr,
	void const *const symbol
)
{
	unsigned int ret = '?';

	if (STBIND(ehdr, symbol) == STB_WEAK) {
		ret = STTYPE(ehdr, symbol) == STT_OBJECT ? 'v' : 'w';
		return STVALUE(ehdr, symbol)
			? (unsigned int)toupper(ret)
			: ret;
	}
	if (STSHNDX(ehdr, symbol) == SHN_UNDEF)
		return (STBIND(ehdr, symbol) == STB_GLOBAL) ? 'U' : 'u';
	for (int i = 0; types[i].key != unknown; i++) {
		ret = types[i].func(ehdr, shdr, symbol, ret) ? types[i].key :
			ret;
	}
	return STBIND(ehdr, symbol) == STB_GLOBAL
		? (unsigned int)toupper(ret)
		: ret;
}