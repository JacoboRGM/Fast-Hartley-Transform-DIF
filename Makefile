CC = gcc
CFLAGS = -Wall -O2 -Iinclude

# Nombre del ejecutable = nombre de la carpeta actual
OUT = $(notdir $(CURDIR)).exe

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(OBJ) -o $(OUT)

clean:
	del src\*.o 2> NUL
	del $(OUT) 2> NUL

run: all
	.\$(TARGET).exe
