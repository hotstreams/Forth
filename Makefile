ASM = nasm
FLAGS = -f elf64 -g -I src/
LINKER = ld

SOURCES = src/forth.asm
INCS = src/functions.inc src/words.inc src/macroses.inc
OBJECTS = obj/forth.o

EXECUTABLE = forth

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(LINKER) $(OBJECTS) -o $@

$(OBJECTS): $(SOURCES) $(INCS)
	$(ASM) $(FLAGS) $(SOURCES) -o $@

clean:
	find ./obj -type f -name "*.o" -delete
	rm $(EXECUTABLE)
