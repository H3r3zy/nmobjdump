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

unsigned int calc_hex_digits(long int n);
void dump_sections(void *, void *, char const *, int);
bool isFile(const char *);
bool isTrunced(void *, void *, long int);
void dump_flag(long int);
long int flag_gestion(void *, void *, char const *);
void dump_header(void *, void *, char const *, char const * const);
bool isValid(void *, int);
void *getData(int);

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

/*
** Elf Value
*/

#define SIZEOFEHDR(ehdr) \
((IS32((void *)(ehdr))) ? \
(sizeof(EHdr32)) : \
(sizeof(EHdr64)))

#define SHNUM(ehdr) \
((IS32((void *)(ehdr))) ? \
(((EHdr32 *)(ehdr))->e_shnum) : \
(((EHdr64 *)(ehdr))->e_shnum))

#define SHOFF(ehdr) \
((IS32(ehdr)) ? \
(((EHdr32 *)(ehdr))->e_shoff) : \
(((EHdr64 *)(ehdr))->e_shoff))

#define PHNUM(ehdr) \
((IS32((void *)(ehdr))) ? \
(((EHdr32 *)(ehdr))->e_phnum) : \
(((EHdr64 *)(ehdr))->e_phnum))

#define TYPE(ehdr) \
((IS32((void *)(ehdr))) ? \
(((EHdr32 *)(ehdr))->e_type) : \
(((EHdr64 *)(ehdr))->e_type))

#define MACHINE(ehdr) \
((IS32((void *)(ehdr))) ? \
(((EHdr32 *)(ehdr))->e_machine) : \
(((EHdr64 *)(ehdr))->e_machine))

#define ENTRY(ehdr) \
((IS32((void *)(ehdr))) ? \
(((EHdr32 *)(ehdr))->e_entry) : \
(((EHdr64 *)(ehdr))->e_entry))

#define SHSTRNDX(ehdr) \
((IS32(ehdr)) ? \
(((EHdr32 *)(ehdr))->e_shstrndx) : \
(((EHdr64 *)(ehdr))->e_shstrndx))

#define SHTAB(data, shdr, ehdr) \
((IS32((void *)(ehdr))) ? \
(long int)((char *)(data) + ((SHdr32 *)(shdr))[SHSTRNDX(ehdr)].sh_offset) : \
(long int)((char *)(data) + ((SHdr64 *)(shdr))[SHSTRNDX(ehdr)].sh_offset))

#define SHNAME(ehdr, shdr, idx) \
((IS32((void *)(ehdr))) ? \
(((SHdr32 *)(shdr))[idx].sh_name) : \
(((SHdr64 *)(shdr))[idx].sh_name))

#define SHOFFSET(ehdr, shdr, idx) \
((IS32((void *)(ehdr))) ? \
(((SHdr32 *)(shdr))[(unsigned int)(idx)].sh_offset) : \
(((SHdr64 *)(shdr))[(unsigned int)(idx)].sh_offset))

#define SHSIZE(ehdr, shdr, idx) \
((IS32((void *)(ehdr))) ? \
(((SHdr32 *)(shdr))[idx].sh_size) : \
(((SHdr64 *)(shdr))[idx].sh_size))

#define SHADDR(ehdr, shdr, idx) \
((IS32((void *)(ehdr))) ? \
(((SHdr32 *)(shdr))[idx].sh_addr) : \
(((SHdr64 *)(shdr))[idx].sh_addr))

#define SHTYPE(ehdr, shdr, idx) \
((IS32((ehdr))) ? \
(((SHdr32 *)(shdr))[idx].sh_type) : \
(((SHdr64 *)(shdr))[idx].sh_type))

#define SHFLAGS(ehdr, shdr, idx) \
((IS32((ehdr))) ? \
(((SHdr32 *)(shdr))[idx].sh_flags) : \
(((SHdr64 *)(shdr))[idx].sh_flags))

#endif //PSU_2017_NMOBJDUMP_OBJDUMP_H
