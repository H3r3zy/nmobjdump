/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#ifndef PSU_2017_NMOBJDUMP_ELF_FILE_H
#define PSU_2017_NMOBJDUMP_ELF_FILE_H

#include <string.h>
#include <elf.h>
#include "bool.h"

/*
** Elf_Ehdr
*/

typedef Elf32_Ehdr EHdr32;

typedef Elf64_Ehdr EHdr64;

/*
** Elf_Sddr
*/

typedef Elf32_Shdr SHdr32;

typedef Elf64_Shdr SHdr64;

/*
** Elf_Sym
*/

typedef Elf32_Sym Sym32;

typedef Elf64_Sym Sym64;

/*
** Verif
*/

bool is_valid(void *, int);

bool is_truncated(void *, void *, long int);

bool is_file(const char *);

void *get_data(int);

/*
** Verification
*/

#define VALIDMAG(header) \
(((EHdr64 *)(header))->e_ident[EI_MAG0] == ELFMAG0 && \
((EHdr64 *)(header))->e_ident[EI_MAG1] == ELFMAG1 && \
((EHdr64 *)(header))->e_ident[EI_MAG2] == ELFMAG2 && \
((EHdr64 *)(header))->e_ident[EI_MAG3] == ELFMAG3 ? true : false)

#define VALIDVERSION32(header) \
(((EHdr32 *)(header))->e_version == EV_CURRENT ? true : false)

#define VALIDVERSION64(header) \
(((EHdr64 *)(header))->e_version == EV_CURRENT ? true : false)

#define VALIDVERSION(ehdr) \
((IS32(ehdr)) ? \
(VALIDVERSION32(ehdr)) : \
(VALIDVERSION64(ehdr)))

#define IS32(header) \
(((EHdr32 *)(header))->e_ident[EI_CLASS] & ELFCLASS32 ? (true) : (false))

#define IS64(header) \
(((EHdr64 *)(header))->e_ident[EI_CLASS] & ELFCLASS64 ? (true) : (false))

#define FILESIZE(fd)        \
lseek(fd, 0, SEEK_END)

#define CONTENT(data, offset)        \
(((char *) (data)) + (offset))

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

/*
** SHDR
*/

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

#define SHLINK(ehdr, shdr, idx) \
((IS32(ehdr)) ? \
(((SHdr32 *)(shdr))[idx].sh_link) : \
(((SHdr64 *)(shdr))[idx].sh_link))

/*
** Elf_Sym
*/

#define STVALUE(ehdr, symbol) \
((IS32(ehdr)) ? \
(((Sym32 *)(symbol))->st_value) : \
(((Sym64 *)(symbol))->st_value))

#define STNAME(ehdr, symbol) \
((IS32(ehdr)) ? \
(((Sym32 *)(symbol))->st_name) : \
(((Sym64 *)(symbol))->st_name))

#define STTYPE(ehdr, symbol) \
((IS32(ehdr)) ? \
(ELF32_ST_TYPE(((Sym32 *)(symbol))->st_info)) : \
(ELF64_ST_TYPE(((Sym64 *)(symbol))->st_info)))

#define STBIND(ehdr, symbol) \
((IS32(ehdr)) ? \
(ELF32_ST_BIND(((Sym32 *)(symbol))->st_info)) : \
(ELF64_ST_BIND(((Sym64 *)(symbol))->st_info)))

#define STNEXT(ehdr, symbol) \
((IS32(ehdr)) ? \
((symbol) + sizeof(Sym32)) : \
((symbol) + sizeof(Sym64)))

#define STSIZE(ehdr, symbol) \
((IS32(ehdr)) ? \
(((Sym32 *)(symbol))->st_size) : \
(((Sym64 *)(symbol))->st_size))

#define STSHNDX(ehdr, symbol) \
((IS32(ehdr)) ? \
(((Sym32 *)(symbol))->st_shndx) : \
(((Sym64 *)(symbol))->st_shndx))

#define STINFO(ehdr, symbol) \
((IS32(ehdr)) ? \
(((Sym32 *)(symbol))->st_info) : \
(((Sym64 *)(symbol))->st_info))

#define SECTIONNAME(ehdr, shdr, symbol) \
(&(((char *)(ehdr) + SHOFFSET(ehdr, shdr, SHSTRNDX(ehdr))) \
[SHNAME(ehdr, shdr, STSHNDX(ehdr, symbol))]))

#endif //PSU_2017_NMOBJDUMP_ELF_FILE_H
