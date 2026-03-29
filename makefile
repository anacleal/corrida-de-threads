CC = gcc
CFLAGS = -Wall -Wextra -pthread -O3
TARGET = thread_run

SRC = main.c corrida_de_threads.c
OBJ = $(SRC:.c=.o)
HEADER = corrida_de_threads.h

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para rodar (adicionei o '5' como exemplo de argumento)
run: $(TARGET)
	./$(TARGET) 5

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean run