CC = gcc
OBJS = size/size.o nm/nm.o elf64.o
TARGETS = size/size nm/nm
all: $(TARGETS)

clean:
	rm -f $(TARGETS) $(OBJS)

size/size: size/size.o elf64.o
	gcc -o size/size $^

nm/nm: nm/nm.o elf64.o
	gcc -o nm/nm $^

%.o: %.c
	gcc -c -o $@ $<
