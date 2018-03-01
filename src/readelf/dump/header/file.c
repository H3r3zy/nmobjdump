/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <stdio.h>
#include <message.h>
#include "readelf.h"

/*
** EI_OSABI
**
** ELFOSABI_NONE       Same as ELFOSABI_SYSV
** ELFOSABI_SYSV       UNIX System V ABI.
** ELFOSABI_HPUX       HP-UX ABI.
** ELFOSABI_NETBSD     NetBSD ABI.
** ELFOSABI_LINUX      Linux ABI.
** ELFOSABI_SOLARIS    Solaris ABI.
** ELFOSABI_IRIX       IRIX ABI.
** ELFOSABI_FREEBSD    FreeBSD ABI.
** ELFOSABI_TRU64      TRU64 UNIX ABI.
** ELFOSABI_ARM        ARM architecture ABI.
** ELFOSABI_STANDALONE Stand-alone (embedded) ABI.
*/

static const t_message OS_ABI[] = {
	{ELFOSABI_SYSV, "Unix - System V"},
	{ELFOSABI_HPUX, "HP-UX - ABI"},
	{ELFOSABI_NETBSD, "NetBSD - ABI"},
	{ELFOSABI_LINUX, "Linux - ABI"},
	{ELFOSABI_SOLARIS, "Solaris - ABI"},
	{ELFOSABI_IRIX, "IRIX - ABI"},
	{ELFOSABI_FREEBSD, "FreeBSD - ABI"},
	{ELFOSABI_TRU64, "TRU64 UNIX - ABI"},
	{ELFOSABI_ARM, "ARM - ABI"},
	{ELFOSABI_STANDALONE, "Stand-alone - ABI"},
	{-1, NULL}
};

/*
** e_type
**
** ET_NONE     An unknown type.
** ET_REL      A relocatable file.
** ET_EXEC     An executable file.
** ET_DYN      A shared object.
** ET_CORE     A core file.
**
*/

static const t_message TYPES[] = {
	{ET_NONE, "NONE (Unknown type)"},
	{ET_REL, "REL (Relocatable file)"},
	{ET_EXEC, "EXEC (Executable file)"},
	{ET_DYN, "DYN (Shared object)"},
	{ET_CORE, "CORE (Core file)"},
	{-1, NULL}
};

/*
** e_machine
**
** EM_NONE     An unknown machine.
** EM_M32      AT&T WE 32100.
** EM_SPARC    Sun Microsystems SPARC.
** EM_386      Intel 80386.
** EM_68K      Motorola 68000.
** EM_88K      Motorola 88000.
** EM_860      Intel 80860.
** EM_MIPS     MIPS RS3000 (big-endian only).
** EM_PARISC   HP/PA.
** EM_SPARC32PLUS
**             SPARC with enhanced instruction set.
** EM_PPC      PowerPC.
** EM_PPC64    PowerPC 64-bit.
** EM_S390     IBM S/390
** EM_ARM      Advanced RISC Machines
** EM_SH       Renesas SuperH
** EM_SPARCV9  SPARC v9 64-bit.
** EM_IA_64    Intel Itanium
** EM_X86_64   AMD x86-64
** EM_VAX      DEC Vax.
**
*/

static const t_message MACHINES[] = {
	{EM_NONE, "Unknown machine"},
	{EM_M32, "AT&T WE 32100"},
	{EM_SPARC, "Sun Microsystems SPARC"},
	{EM_386, "Intel 80386"},
	{EM_68K, "Motorola 68000"},
	{EM_88K, "Motorola 88000"},
	{EM_860, "Intel 80860"},
	{EM_MIPS, "MIPS RS3000"},
	{EM_PARISC, "HP/PA"},
	{EM_SPARC32PLUS, "SPARC"},
	{EM_PPC, "PowerPC"},
	{EM_PPC64, "PowerPPC 64"},
	{EM_S390, "IBM S/390"},
	{EM_ARM, "Advanced RISC Machines"},
	{EM_SH, "Renesas SuperH"},
	{EM_SPARCV9, "SPARC v9 64"},
	{EM_IA_64, "Interl Itanium"},
	{EM_X86_64, "Advanced Micro Deviced X86-64"},
	{EM_VAX, "DEC Vax"},
	{-1, NULL}
};

/*
**  Entry point address:               0x400700
**  Start of program headers:          64 (bytes into file)
**  Start of section headers:          16640 (bytes into file)
**  Flags:                             0x0
**  Size of this header:               64 (bytes)
**  Size of program headers:           56 (bytes)
**  Number of program headers:         9
**  Size of section headers:           64 (bytes)
**  Number of section headers:         31
**  Section header string table index: 28
**/
static void dump_header_part_2(void const *const ehdr)
{
	printf("\n  Entry point address:               0x%lx", ENTRY(ehdr));
	printf("\n  Start of program headers:          %li (bytes into file)",
		PHOFF(ehdr));
	printf("\n  Start of section headers:          %li (bytes info file)",
		SHOFF(ehdr));
	printf("\n  Flags:                             0x%x", FLAGS(ehdr));
	printf("\n  Size of this header:               %li (bytes)",
		SIZEOFEHDR(ehdr));
	printf("\n  Size of program headers:           %li (bytes)",
		SIZEOFPHDR(ehdr));
	printf("\n  Number of program headers:         %i", PHNUM(ehdr));
	printf("\n  Size of section headers:           %li(bytes)",
		SIZEOFSHDR(ehdr));
	printf("\n  Number of section headers:         %i", SHNUM(ehdr));
	printf("\n  Section header string table index: %i\n", SHSTRNDX(ehdr));
}

/*
** ELF Header:
**  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
**  Class:                             ELF64
**  Data:                              2's complement, little endian
**  Version:                           1 (current)
**  OS/ABI:                            UNIX - System V
**  ABI Version:                       0
**  Type:                              EXEC (Executable file)
**  Machine:                           Advanced Micro Devices X86-64
**  Version:                           0x1
*/
void dump_header(void const *const ehdr)
{
	printf("ELF Header:\n");
	printf("  Magic:   ");
	for (unsigned int i = 0; i < 16; i++) {
		printf("%02x ", IDENT(ehdr, i));
	}
	printf("\n  Class:                             %s", (IS64(ehdr))
		? ("ELF64") : ("ELF32"));
	printf("\n  Data:                              %s", DATAINFO(ehdr));
	printf("\n  Version:                           %s", VERSIONINFO(ehdr));
	printf("\n  OS/ABI:                            ");
	print_with_tab(IDENT(ehdr, EI_OSABI), OS_ABI, 0);
	printf("\n  ABI Version:                       %i", IDENT(ehdr,
		EI_ABIVERSION));
	printf("\n  Type:                              ");
	print_with_tab(TYPE(ehdr), TYPES, 0);
	printf("\n  Machine:                           ");
	print_with_tab(MACHINE(ehdr), MACHINES, 0);
	printf("\n  Version:                           0x%x", VERSION(ehdr));
	dump_header_part_2(ehdr);
}
