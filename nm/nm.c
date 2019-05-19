#include "../elf64.h"

static void display_file(elf64 *e)
{
    const char *type;
    ssize_t sym_size;
    Elf64_Sym *sym = find_section(e, ".symtab", &sym_size);
    const char *sym_name = find_section(e, ".strtab", NULL);
    uint16_t sym_num = sym_size / sizeof(Elf64_Sym);

    puts("Address/Offset   Type        NAME");
    for (int i = 0; i < sym_num; ++i) {
        Elf64_Word idx = sym[i].st_name;
        if (!idx)
            continue;

        switch (ELF64_ST_TYPE(sym[i].st_info)) {
        case STT_NOTYPE:
            type = "STT_NOTYPE ";
            break;
        case STT_OBJECT:
            type = "STT_OBJECT ";
            break;
        case STT_FUNC:
            type = "STT_FUNC   ";
            break;
        case STT_SECTION:
            type = "STT_SECTION";
            break;
        case STT_FILE:
            type = "STT_FILE   ";
            break;
        case STT_COMMON:
            type = "STT_COMMON ";
            break;
        case STT_LOOS:
            type = "STT_LOOS   ";
            break;
        case STT_HIOS:
            type = "STT_HIOS   ";
            break;
        case STT_LOPROC:
            type = "STT_LOPROC ";
            break;
        case STT_HIPROC:
            type = "STT_HIPROC ";
            break;
        }
        printf("%016lx %s %s\n", sym[i].st_value, type, &sym_name[idx]);
    }
}

int main(int argc, char **argv)
{
    const char *file_name = argv[1];

    /* map the file into memory */
    elf64 *e = open_elf64(file_name);

    /* print nm message */
    display_file(e);

    /* free allocated memory */
    close_elf64(e);
}
