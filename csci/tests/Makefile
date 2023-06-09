ifndef TEST
$(error TEST is not set)
endif

BASE_DIR = 

LIBDSADIR     = ../dsa
LIBDSAINCLUDE = $(LIBDSADIR)/include
LIBDSA        = dsa
LIBDSAAR      = $(LIBDSADIR)/lib$(LIBDSA).a

LIBCSCIDIR     = ../lib
LIBCSCIINCLUDE = $(LIBCSCIDIR)/include
LIBCSCI        = csci
LIBCSCIAR      = $(LIBCSCIDIR)/lib$(LIBCSCI).a

MAIN          = $(TEST)/main
VALGRINDOUT   = $(TEST)/valgrind-out.txt

# CCompiler - é o compilador usado
# CFLAGS    - são as flags dadas ao compilador durante a compilação
CC = gcc
override CFLAGS += -Wall -Wall -Wextra -Werror -pedantic -ggdb3 -I$(LIBDSAINCLUDE) -I$(LIBCSCIINCLUDE) -lm

# Make - é o GNU Make
MAKE = make

all : pre-build build
	echo $(shell pwd)

# Compila o executável e linka as bibliotecas
main: $(LIBDSAAR) $(LIBCSCIAR)
	$(CC) -o $(MAIN) $(TEST)/main.c -L $(LIBCSCIDIR)/ -l$(LIBCSCI) -L $(LIBDSADIR)/ -l$(LIBDSA) $(CFLAGS)

# Chama os submakefiles garantindo a compilação das bibliotecas
pre-build:
	$(MAKE) -C $(LIBDSADIR)/
	$(MAKE) -C $(LIBCSCIDIR)/

build : main

# Rode make clean para remover tudo que é gerado pela build
clean:
	rm -f $(MAIN) $(VALGRINDOUT)
	$(MAKE) -C $(LIBDSADIR)/ clean
	$(MAKE) -C $(LIBCSCIDIR)/ clean

valgrind: all
	rm -f $(VALGRINDOUT)

	valgrind --leak-check=full \
			 --show-leak-kinds=all \
			 --track-origins=yes \
			 --verbose \
			 --log-file=$(VALGRINDOUT) \
			 ./$(MAIN) $(VALARGS)

	@echo "Head to $(VALGRINDOUT)"
