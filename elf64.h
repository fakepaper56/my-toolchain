#ifndef INCLUDE_ELF64_H
#define INCLUDE_ELF64_H

#include <elf.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct {
    void *file;
    ssize_t size;
    Elf64_Shdr *shdr;
    uint16_t shdr_num;
    const char *shdr_name;
} elf64;

elf64 *open_elf64(const char *file_name);
void close_elf64(elf64 *e);
void *find_section(elf64 *e, const char *section_name, ssize_t *size);

#define fatal(...) fprintf(stderr, __VA_ARGS__)

#endif /* INCLUDE_ELF64_H */
