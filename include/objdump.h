/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#ifndef PSU_2017_NMOBJDUMP_OBJDUMP_H
#define PSU_2017_NMOBJDUMP_OBJDUMP_H

#include <elf.h>

typedef struct {
	int id;
	char *name;
} t_message;

typedef enum bool {
	false = 0,
	true = 1,
	undefined = 2
} bool;

typedef Elf32_Ehdr EHdr32;
typedef Elf64_Ehdr EHdr64;
typedef Elf32_Shdr SHdr32;
typedef Elf64_Shdr SHdr64;
typedef void * Header;

#define VALIDMAG(header) \
(((EHdr64 *)(header))->e_ident[EI_MAG0] == ELFMAG0 && \
((EHdr64 *)(header))->e_ident[EI_MAG1] == ELFMAG1 && \
((EHdr64 *)(header))->e_ident[EI_MAG2] == ELFMAG2 && \
((EHdr64 *)(header))->e_ident[EI_MAG3] == ELFMAG3 ? true : false)

#define VALIDVERSION32(header) \
(((EHdr32 *)(header))->e_version == EV_CURRENT ? true : false)

#define VALIDVERSION64(header) \
(((EHdr64 *)(header))->e_version == EV_CURRENT ? true : false)

#define IS32(header) \
(((EHdr32 *)(header))->e_ident[EI_CLASS] & ELFCLASS32 ? (true) : (false))

#define IS64(header) \
(((EHdr64 *)(header))->e_ident[EI_CLASS] & ELFCLASS64 ? (true) : (false))

#define CONTENT(data, offset)	\
(((char *) (data)) + (offset))

#define FILESIZE(fd)	\
lseek(fd, 0, SEEK_END)

#define SHTAB(data, shdr, ehdr) \
((char *)(data) + (shdr)[(ehdr)->e_shstrndx].sh_offset)

unsigned int calc_hex_digits(long int n);
void dump_sections(void *, SHdr64 *, char const *, int);
bool isFile(const char *);
bool isTrunced(EHdr64 *, SHdr64 *, long int);
void dump_flag(long int);
long int flag_gestion(EHdr64 *, SHdr64 *, char const *);
void dump_header(EHdr64 *, SHdr64 *, char const *, char const * const);
bool isValid(EHdr64 *ehdr, int fd);
void *getData(int fd);

/*
** Errors
*/
typedef enum errors {
	SUCCESS = 0,
	DIRECTORY = 1,
	NOT_RECOGNIZED = 2,
	TRUNCATED = 3,
	NO_FILE = 4
} errors;

#endif //PSU_2017_NMOBJDUMP_OBJDUMP_H
