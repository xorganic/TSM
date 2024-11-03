CC = gcc
ASM = nasm
CFLAGS = -Wall -O2
ASMFLAGS = -f win64
LDFLAGS = -lwinapi -ljson-c  # Biblioteca JSON pentru config.json

SOURCES_C = main.c \
            modules/shadow_inject.c \
            modules/temp_files.c \
            modules/evasion.c \
            modules/persistence.c \
            modules/privilege_escalation.c \
            modules/utils.c

SOURCES_ASM = asm/shadow_inject.asm \
              asm/evasion.asm \
              asm/persistence.asm \
              asm/privilege_escalation.asm

OBJECTS_C = $(SOURCES_C:.c=.o)
OBJECTS_ASM = $(SOURCES_ASM:.asm=.o)

TARGET = build/TSM.exe

all: $(TARGET)

$(TARGET): $(OBJECTS_C) $(OBJECTS_ASM)
	$(CC) $(CFLAGS) $(OBJECTS_C) $(OBJECTS_ASM) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS_C) $(OBJECTS_ASM)
