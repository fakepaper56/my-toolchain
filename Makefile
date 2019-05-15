CC = gcc
OBJS = size/size.o nm/nm.o elf64.o

all: size/size nm/nm

clean:
	rm -f size/size $(OBJS)

size/size: size/size.o elf64.o
	gcc -o size/size $^

nm/nm: nm/nm.o elf64.o
	gcc -o nm/nm $^

%.o: %.c
	gcc -c -o $@ $<
