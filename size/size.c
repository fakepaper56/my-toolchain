#include "../elf64.h"


char *proc_str(const char *str)
{
    char *cp = malloc(20);
    if (!cp) {
        fatal("malloc: %s\n", strerror(errno));
        exit(1);
    }

    memset(cp, ' ', 19);
    cp[20] = '\0';
    memcpy(cp, str, strlen(str));
    return cp;
}

void display_file(elf64 *e)
{
    Elf64_Shdr *shdr = e->shdr;
    const char *shdr_name = e->shdr_name;
    const int sh_num = e->shdr_num;
    size_t total_size = 0;

    printf("%29s%10s\n", "ADDR", "SIZE");
    for (int i = 1; i < sh_num; ++i) {
        int idx = shdr[i].sh_name;
        const char *name = &shdr_name[idx];

        // skip string table
        if (!strcmp(name, ".shstrtab"))
            continue;

        // print address and size of each section
        char *new_name = proc_str(name);
        printf("%s%10lu%10lu\n", new_name, shdr[i].sh_addr, shdr[i].sh_size);
        free(new_name);

        // caculate the total size
        total_size += shdr[i].sh_size;
    }

    char *new_str = proc_str("Total:");
    printf("%s%10lu\n\n", new_str, total_size);
    free(new_str);
}

int main(int argc, char **argv)
{
    ssize_t size = -1;
    const char *file_name = argv[1];

    elf64 *e = open_elf64(file_name);
    display_file(e);
    printf("%d\n", e->shdr_num);
    close_elf64(e);
}
