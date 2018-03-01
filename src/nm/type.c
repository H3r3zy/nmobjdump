/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <ctype.h>
#include <nm.h>

const unsigned int UNKNOWN = '?';

static const type TYPES[] = {
	{'u', &is_undefined},
	{'c', &is_common},
	{'a', &is_absolute},
	{'b', &is_bss},
	{'r', &is_readonly},
	{'d', &is_data},
	{'t', &is_text},
	{'?', NULL}
};

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
	for (int i = 0; TYPES[i].key != UNKNOWN; i++) {
		ret = TYPES[i].func(ehdr, shdr, symbol, ret) ? TYPES[i].key :
			ret;
	}
	return STBIND(ehdr, symbol) == STB_GLOBAL
		? (unsigned int)toupper(ret)
		: ret;
}