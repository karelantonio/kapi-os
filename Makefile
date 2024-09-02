.PHONY: all clean

# C Compiler
CC=gcc
CFLAGS=-Wall -nostdlib -I include/ --no-pie -fno-stack-protector

# Cpp Compiler
CPP=g++
CPPFLAGS=-Wall -nostdlib -I include/ --no-pie -fno-stack-protector

# Assembler
NASM=nasm
NASMFLAGS=

# Linker
LD=ld
LDFLAGS=

# Dirs
SRCDIR=src
OBJSDIR=objs

# Files
#SED_SCRIPT="{ s/^$(SRCDIR)/$(OBJSDIR)/g ; s/\.c$$/\.o/g ; s/\.cpp$$/\.o/g ; s/\.s$$/\.o/g }"
#OBJS=$(shell find src/ -type f | grep -P "\.(c|cpp|s)$$" | grep -v mbr.s | sed $(SED_SCRIPT) )
FILES=load-kernel kernel vga
OBJS=$(foreach file,$(FILES),$(OBJSDIR)/$(file).o)

# Color logs
GREEN="\e[30;42m"
RED="\e[30;41m"
BLUE="\e[30;44m"
RESET="\e[0m"


all: bootable.bin
	@echo -e $(GREEN)"  DONE  "$(RESET) Everything done
	@echo
	@echo -e " Now Try:"
	@echo -e "     \e[32m$$\e[0m \e[34mqemu-system-x86_64\e[0m \e[32mbootable.bin\e[0"
	@echo

clean:
	@echo -e $(RED)" CLEAN  "$(RESET) Removing obj files and bootable...
	@rm -f $(OBJSDIR)/* bootable.bin

bootable.bin: $(OBJSDIR)/mbr.bin $(OBJSDIR)/nonbootable.bin
	@echo -e $(BLUE)" BUILD  "$(RESET) Building bootable...
	@cat $^ > $@

$(OBJSDIR)/nonbootable.bin: $(OBJS)
	@echo -e $(BLUE)" BUILD  "$(RESET) Linking...
	@$(LD) $(LDFLAGS) --oformat binary -Ttext 0x1000 -e _entrypoint -m elf_i386 -o $@ $^

$(OBJSDIR)/mbr.bin: $(SRCDIR)/mbr.s
	@echo -e $(BLUE)"ASSEMBLE"$(RESET) Assembling MBR...
	@$(NASM) $(NASMFLAGS) -f bin -o $@ $^

$(OBJSDIR)/%.o: $(SRCDIR)/%.c
	@echo -e $(BLUE)"COMPILE "$(RESET) $^...
	@$(CC) $(CFLAGS) -m32 -c -o $@ $^

$(OBJSDIR)/%.o: $(SRCDIR)/%.cpp
	@echo -e $(BLUE)"COMPILE "$(RESET) $^...
	@$(CPP) $(CPPFLAGS) -m32 -c -o $@ $^

$(OBJSDIR)/%.o: $(SRCDIR)/%.s
	@echo -e $(BLUE)"ASSEMBLE"$(RESET) $^...
	@$(NASM) $(NASMFLAGS) -f elf32 -o $@ $^

