# Makefile que percorre todo a biblioteca, procurando todos os códigos fontes .c para compilar

# INCLUDE        - é o diretório que contém os headers
# BUILDIR        - é o diretório onde estarão os binários
# LIBDSADIR   - é o diretório para a biblioteca de tipos comuns.
# LIBDSA      - é a biblioteca de tipos comuns.
INCLUDE          = .
LIBDSADIR     = ../dsa
LIBDSAINCLUDE = $(LIBDSADIR)/include
LIBDSA        = dsa
LIBDSAAR      = $(LIBDSADIR)/lib$(LIBDSA).a
MAIN          = main
VALGRINDOUT   = valgrind-out.txt

# CCompiler - é o compilador usado
# CFLAGS    - são as flags dadas ao compilador durante a compilação
CC = gcc
override CFLAGS += -Wall -Wall -Wextra -Werror -pedantic -ggdb3 -I$(LIBDSAINCLUDE) -I$(LIBENGINEINCLUDE) -lm

# Make - é o GNU Make
MAKE = make

all : pre-build build

# Compila o executável e linka as bibliotecas
main: main.c $(LIBDSAAR)
	$(CC) -o $@ $< -L $(LIBDSADIR)/ -l$(LIBDSA) $(CFLAGS)

# Chama os submakefiles garantindo a compilação das bibliotecas
pre-build:
	$(MAKE) -C $(LIBDSADIR)/

build : main

# Rode make clean para remover tudo que é gerado pela build
clean:
	rm -f $(MAIN) $(VALGRINDOUT)
	$(MAKE) -C $(LIBDSADIR)/ clean

valgrind: all
	rm -f $(VALGRINDOUT)

	valgrind --leak-check=full \
			 --show-leak-kinds=all \
			 --track-origins=yes \
			 --verbose \
			 --log-file=$(VALGRINDOUT) \
			 ./$(MAIN) $(VALARGS)

	@echo "Head to $(VALGRINDOUT)"
