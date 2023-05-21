#ifndef _CSCI_CSRC_MATRIX_H_
#define _CSCI_CSRC_MATRIX_H_

#include "csci/cell.h"
#include "csci/index.h"

typedef struct CsrcMatrix CsrcMatrix;

Index **_csrc_matrix_rows(CsrcMatrix *self);

Index **_csrc_matrix_cols(CsrcMatrix *self);

Cell *_csrc_matrix_get_r(CsrcMatrix *self, size_t i, size_t j);

/**
 * @brief
 *
 * @param n
 * @param m
 * @return CsrcMatrix*
 *
 * @note
 *
 *  A complexidade de tempo dessa operação é O(1) amortizada, dado que a
 * operação mais custosa encontra-se na função vector_construct, em
 * dsa/vector.c, que seria O(n) onde n é o tamanho inicial do vetor que é
 * constante e definido em tempo de compilação.
 *
 *  A complexidade de espaço dessa operação é O(1) amortizada, dado que apenas o
 * vector aloca seu espaço inicial, que seria O(n) onde n é o tamanho inicial do
 * vetor que é constante e definido em tempo de compilação.
 *
 * https://stackoverflow.com/a/249695/12511877
 */
CsrcMatrix *csrc_matrix_constructor_z(size_t n, size_t m);

/**
 * @brief
 *
 * @param self
 *
 * @note
 *
 *  Essa função é uma variante da função csrc_matrix_constructor_z, que constrói
 * uma matriz identidade de tamanho n.
 *
 *  A complexidade de tempo dessa operação é O(n), onde n é o tamanho da
 * diagonal da matriz identidade. Mesmas observaçães do csrc_matrix_set se aplicam.
 *
 *  A complexidade de espaço dessa operação é O(1). Mesmas observações do
 * constructor se aplicam.
 */
CsrcMatrix *csrc_matrix_indentity(size_t n);

/**
 * @brief
 *
 * @param self
 * @param i
 * @param j
 * @param value
 *
 * @note
 *  A complexidade de tempo dessa operação é O(n + m), onde n é o número de células não zero na linha i e m é o número de células não zero na coluna j. Isso é porque é necessário fazer as referências next e previous para as linhas e as colunas.
 *
 *  A complexidade de espaço dessa operação é O(1).
 */
void csrc_matrix_set(CsrcMatrix *self, size_t i, size_t j, double value);

/**
 * @brief
 *
 * @param self
 * @param i
 * @param j
 * @return double
 *
 * @note
 *   A complexidade de tempo dessa operação é O(n), onde n é o número de células
 * diferentes de zero na mesma linha. A princípio é feita uma busca linear,
 * O(log n), no indice de linhas e então uma busca linear, O(n), pela célula
 * desejada. Como O(n) > O(log n), a complexidade de tempo é O(n).
 *
 *  A complexidade de espaço dessa operação é O(1).
 */
double csrc_matrix_get(CsrcMatrix *self, size_t i, size_t j);

/**
 * @brief
 *
 * @param self
 * @param i
 * @return Cell*
 *
 * @note
 *   A complexidade de tempo dessa operação é O(log n), onde n é o número de
 * linhas da matriz que possuem ao menos uma célula diferente de zero. Isso se
 * deve ao fato das referências para o começo das linhas e das colunas serem
 * armazenadas em um vetor dinâmico, ordenado de acordo com que hajam células.
 *
 *  A complexidade de espaço dessa operação é O(1).
 */
Cell *csrc_matrix_get_row(CsrcMatrix *self, size_t i);

/**
 * @brief
 *
 * @param self
 * @param j
 * @return Cell*
 *
 * @note
 *   A complexidade de tempo dessa operação é O(log n), onde n é o número de
 * colunas da matriz que possuem ao menos uma célula diferente de zero. Isso se
 * deve ao fato das referências para o começo das linhas e das colunas serem
 * armazenadas em um vetor dinâmico, ordenado de acordo com que hajam células.
 *
 *  A complexidade de espaço dessa operação é O(1).
 */
Cell *csrc_matrix_get_col(CsrcMatrix *self, size_t j);

size_t csrc_matrix_shape_n(CsrcMatrix *self);

size_t csrc_matrix_shape_m(CsrcMatrix *self);

/**
 * @brief
 *
 * @param self
 * @param b
 * @return int
 *
 * @note
 *   A complexidade de tempo dessa operação é O(n), onde n é o número de células
 * diferentes de zero da matriz.
 *
 *  A complexidade de espaço dessa operação é O(1).
 */
int csrc_matrix_compar(CsrcMatrix *self, CsrcMatrix *b);

/**
 * @brief
 *
 * @param self
 * @param b
 * @return int
 *
 * @note
 *   A complexidade de tempo dessa operação é O(n), onde n é o número de células
 * diferentes de zero da matriz.
 *
 *  A complexidade de espaço dessa operação é O(1), mesmo que ela retorne uma
 * cópia profunda da matriz.
 *
 * https://cs.stackexchange.com/a/149515
 */
CsrcMatrix *csrc_matrix_copy(CsrcMatrix *self);

void csrc_matrix_clear(CsrcMatrix *self);

/**
 * @brief
 *
 * @param self
 *
 * @note
 *   A complexidade de tempo dessa operação é O(n), onde n é o número de células
 * diferentes de zero da matriz. Também há de se levar em consideração destruir
 * os vetores dos índices é O(N + M), onde N é o número de linhas da matriz que
 * tem pelo menos uma célula não nula; idem, M é o número de colunas.
 *
 *  A complexidade de espaço dessa operação é O(1).
 */
void csrc_matrix_destructor(CsrcMatrix *self);

#endif