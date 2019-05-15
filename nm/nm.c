#include "../elf64.h"
static void display_file(elf64 *e)
{
	ssize_t sym_size;	
	Elf64_Sym *sym = find_section(e, ".symtab", &sym_size);
	const char *name = find_section(e, ".strtab", NULL);
	uint16_t sym_num = sym_size / sizeof(Elf64_Sym);

	for (int i = 0; i < sym_num; ++i) {
		int idx = sym[i].st_name;
		if (!idx)
			continue;

		if (sym[i].st_info & STT_FILE)
			continue;
		if (sym[i].st_value) {
			printf("%016lx %s\n", sym[i].st_value, &name[idx]);
		} else {
			printf("%16c %s\n", ' ', &name[idx]);
		}
	}
}

int main(int argc, char **argv) {
	const char *file_name = argv[1];
	
	/* map the file into memory */
	elf64 *e = open_elf64(file_name);
	
	/* print nm message */
	display_file(e);
	
	/* free allocated memory */
	close_elf64(e);
}
