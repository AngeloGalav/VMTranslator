CC = gcc

RMV = rm -f ./*.o

FLAGS = -lpthread -lXrandr -lXi -ldl
CFLAGS = $(FLAGS) -Wall -O0

# nome eseguibile
EXEC_NAME = VMTranslator

.PHONY : all clean

all : $(EXEC_NAME)

SRC = $(wildcard ./*.c) # Troviamo tutti i file con estensione in c
OBJ = $(SRC:.c=.o) # considers the files with a suffix 

$(EXEC_NAME) : $(OBJ)
	@echo "** Building main executable, aka $(EXEC_NAME) ..."
	$(CC) -o $@ $(OBJ) $(CFLAGS)

%.o: %.c
	@echo "** Building obj files..."
	$(CC) -c $< -o $@ $(CFLAGS)

clean :
	@echo "** Removing object files..."
	$(RMV)