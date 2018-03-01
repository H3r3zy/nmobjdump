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
** Elf_Shdr
*/

typedef Elf32_Shdr SHdr32;

typedef Elf64_Shdr SHdr64;

/*
** Elf_Phdr
*/

typedef Elf32_Phdr PHdr32;

typedef Elf64_Phdr PHdr64;

/*
** Elf_Sym
*/

typedef Elf32_Sym Sym32;

typedef Elf64_Sym Sym64;

/*
** Elf_Rel
*/

typedef Elf32_Rel Rel32;

typedef Elf64_Rel Rel64;

/*
** Elf_Rela
*/

typedef Elf32_Rela Rela32;

typedef Elf64_Rela Rela64;

/*
** Elf_Nhdr
*/

typedef Elf32_Nhdr NHdr32;

typedef Elf64_Nhdr NHdr64;

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

#define IDENT(ehdr, idx) \
(IS32(ehdr) ? \
(((EHdr32 *)(ehdr))->e_ident[idx]) : \
(((EHdr64 *)(ehdr))->e_ident[idx]))

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

#define VERSION(ehdr) \
((IS32(ehdr)) ? \
(((EHdr32 *)(ehdr))->e_version) : \
(((EHdr64 *)(ehdr))->e_version))

#define PHOFF(ehdr) \
((IS32(ehdr)) ? \
(((EHdr32 *)(ehdr))->e_phoff) : \
(((EHdr64 *)(ehdr))->e_phoff))

#define FLAGS(ehdr) \
((IS32(ehdr)) ? \
(((EHdr32 *)(ehdr))->e_flags) : \
(((EHdr64 *)(ehdr))->e_flags))

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

#define SIZEOFSHDR(ehdr) \
((IS32(ehdr)) ? \
(sizeof(SHdr32)) : \
(sizeof(SHdr64)))

#define SHENTSIZE(ehdr, shdr, idx) \
((IS32(ehdr)) ? \
(((SHdr32 *)(shdr))[idx].sh_entsize) : \
(((SHdr64 *)(shdr))[idx].sh_entsize))

#define SHINFO(ehdr, shdr, idx) \
((IS32(ehdr)) ? \
(((SHdr32 *)(shdr))[idx].sh_info) : \
(((SHdr64 *)(shdr))[idx].sh_info))

#define SHADDRALIGN(ehdr, shdr, idx) \
((IS32(ehdr)) ? \
(((SHdr32 *)(shdr))[idx].sh_addralign) : \
(((SHdr64 *)(shdr))[idx].sh_addralign))

/*
** PHDR
*/

#define SIZEOFPHDR(ehdr) \
((IS32(ehdr)) ? \
(sizeof(PHdr32)) : \
(sizeof(PHdr64)))

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

#define STOTHER(ehdr, symbol) \
((IS32(ehdr)) ? \
(((Sym32 *)(symbol))->st_other) : \
(((Sym64 *)(symbol))->st_other))

#define SECTIONNAME(ehdr, shdr, symbol) \
(&(((char *)(ehdr) + SHOFFSET(ehdr, shdr, SHSTRNDX(ehdr))) \
[SHNAME(ehdr, shdr, STSHNDX(ehdr, symbol))]))

/*
** Elf_Rel
*/

#define RELOFFSET(ehdr, rel) \
((IS32(ehdr)) ? \
(((Rel32 *)(rel))->r_offset) : \
(((Rel64 *)(rel))->r_offset))

#define RELINFO(ehdr, rel) \
((IS32(ehdr)) ? \
(((Rel32 *)(rel))->r_info) : \
(((Rel64 *)(rel))->r_info))

#define RELSIZEOF(ehdr) \
((IS32(ehdr)) ? \
(sizeof(Rel32)) : \
(sizeof(Rel64)))

#define RELTYPE(ehdr, info) \
((IS32(ehdr)) ? \
(ELF32_R_TYPE(info)) : \
(ELF64_R_TYPE(info)))

/*
** Elf_Rela
*/

#define RELAOFFSET(ehdr, rel) \
((IS32(ehdr)) ? \
(((Rela32 *)(rel))->r_offset) : \
(((Rela64 *)(rel))->r_offset))

#define RELAINFO(ehdr, rel) \
((IS32(ehdr)) ? \
(((Rela32 *)(rel))->r_info) : \
(((Rela64 *)(rel))->r_info))

#define RELAADDEND(ehdr, rel) \
((IS32(ehdr)) ? \
(((Rela32 *)(rel))->r_addend) : \
(((Rela64 *)(rel))->r_addend))

#define RELASIZEOF(ehdr) \
((IS32(ehdr)) ? \
(sizeof(Rela32)) : \
(sizeof(Rela64)))

/*
** Elf_Rel / Elf_Rela
*/


#define RSYM(ehdr, info) \
((IS32(ehdr)) ? \
(ELF32_R_SYM(info)) : \
(ELF64_R_SYM(info)))

#define RINFO(ehdr, shdr, i, rel) \
((SHTYPE(ehdr, shdr, i) == SHT_RELA) ? \
(RELAINFO(ehdr, rel)) : \
(RELINFO(ehdr, rel)))

#define RSIZEOF(ehdr, shdr, i) \
((SHTYPE(ehdr, shdr, i) == SHT_RELA) ? \
(RELASIZEOF(ehdr)) : \
(RELSIZEOF(ehdr)))

#define ROFFSET(ehdr, shdr, i, rel) \
((SHTYPE(ehdr, shdr, i) == SHT_RELA) ? \
(RELAOFFSET(ehdr, rel)) : \
(RELOFFSET(ehdr, rel)))

#define RADDEND(ehdr, shdr, i, rel) \
((SHTYPE(ehdr, shdr, i) == SHT_RELA) ? \
(RELAADDEND(ehdr, rel)): \
(0))

/*
** Elf_Phdr
*/

#define PHTYPE(ehdr, phdr, i) \
((IS32(ehdr)) ? \
(((PHdr32 *)(phdr))[i].p_type) : \
(((PHdr64 *)(phdr))[i].p_type))

#define PHOFFSET(ehdr, phdr, i) \
((IS32(ehdr)) ? \
(((PHdr32 *)(phdr))[i].p_offset) : \
(((PHdr64 *)(phdr))[i].p_offset))

#define PHFLAGS(ehdr, phdr, i) \
((IS32(ehdr)) ? \
(((PHdr32 *)(phdr))[i].p_flags) : \
(((PHdr64 *)(phdr))[i].p_flags))

#define PHVADDR(ehdr, phdr, i) \
((IS32(ehdr)) ? \
(((PHdr32 *)(phdr))[i].p_vaddr) : \
(((PHdr64 *)(phdr))[i].p_vaddr))

#define PHPADDR(ehdr, phdr, i) \
((IS32(ehdr)) ? \
(((PHdr32 *)(phdr))[i].p_paddr) : \
(((PHdr64 *)(phdr))[i].p_paddr))

#define PHFILESZ(ehdr, phdr, i) \
((IS32(ehdr)) ? \
(((PHdr32 *)(phdr))[i].p_filesz) : \
(((PHdr64 *)(phdr))[i].p_filesz))

#define PHMEMSZ(ehdr, phdr, i) \
((IS32(ehdr)) ? \
(((PHdr32 *)(phdr))[i].p_memsz) : \
(((PHdr64 *)(phdr))[i].p_memsz))

#define PHALIGN(ehdr, phdr, i) \
((IS32(ehdr)) ? \
(((PHdr32 *)(phdr))[i].p_align) : \
(((PHdr64 *)(phdr))[i].p_align))

/*
** Elf_Nhdr
*/

#define NSIZEOF(ehdr) \
((IS32(ehdr)) ? \
(sizeof(NHdr32)) : \
(sizeof(NHdr64)))

#define NNAMESZ(ehdr, note) \
((IS32(ehdr)) ? \
(((NHdr32 *)(note))->n_namesz) : \
(((NHdr64 *)(note))->n_namesz))

#define NDESCSZ(ehdr, note) \
((IS32(ehdr)) ? \
(((NHdr32 *)(note))->n_descsz) : \
(((NHdr64 *)(note))->n_descsz))

#define NTYPE(ehdr, note) \
((IS32(ehdr)) ? \
(((NHdr32 *)(note))->n_type) : \
(((NHdr64 *)(note))->n_type))

#endif //PSU_2017_NMOBJDUMP_ELF_FILE_H
