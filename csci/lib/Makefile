# Makefile que percorre toda a biblioteca, procurando os códigos fontes .c para compilar

# INCLUDE   - é o diretório que contém os headers
# BUILDIR   - é o diretório onde estarão os binários
# LIBNAME   - nome base da biblioteca do projeto
# LIBTARGET - é o caminho para a biblioteca compilada
# SRCS      - lista com os caminhos para todos .c
# OBJS      - lista com os caminhos para todos .o
INCLUDE = include
BUILDIR = build
LIBNAME = csci
LIBTARGET = lib$(LIBNAME).a
SRCS = $(shell find . -type f -name '*.c' | sed 's|^./||')
OBJS = $(patsubst %.c, $(BUILDIR)/%.o, $(notdir $(SRCS)))

LIBDSADIR     = ../dsa
LIBDSAINCLUDE = $(LIBDSADIR)/include
LIBDSA        = dsa
LIBDSAAR      = $(LIBDSADIR)/lib$(LIBDSA).a

# CCompiler - é o compilador usado
# CFLAGS - são as flags dadas ao compilador durante a compilação
CC = gcc
override CFLAGS += -Wall -Wall -Wextra -Werror -pedantic -ggdb3 -I$(INCLUDE) -I$(LIBDSAINCLUDE) -L$(LIBDSADIR) -l$(LIBDSA) -lm

# ARchive - é o comando arquivador da biblioteca
# ARFLAGS - são as flags dadas ao arquivador
AR = ar
ARFLAGS = rcs

# vpath diretiva que adiciona todos os diretórios com códigos fontes para busca com o padrão %.c
#   - https://www.gnu.org/software/make/manual/html_node/Selective-Search.html
#   - não me pergunte mais nada, eu não sei como funciona
vpath %.c $(shell dirname $(SRCS) | uniq)

all : pre-build build

# Compila todos os .o
$(BUILDIR)/%.o : %.c
	$(CC) -o $@ -c $< $(CFLAGS)

# Preparativos para o build; Garante que o diretório build/ existe
pre-build:
	mkdir -p $(BUILDIR)/
	$(MAKE) -C $(LIBDSADIR)/

build : $(OBJS)
	$(AR) $(ARFLAGS) $(LIBTARGET) $^

# Rode make clean para remover tudo que é gerado pela build
clean:
	rm -rf $(BUILDIR)/ $(LIBTARGET)
	$(MAKE) -C $(LIBDSADIR)/ clean
