#ifndef _CSRC_MATRIX_OPER_H_
#define _CSRC_MATRIX_OPER_H_

#include "csci/csrc_matrix.h"

/**
 * @brief
 *
 * @param self
 * @param b
 * @return CsrcMatrix*
 *
 * @note
 *
 *  A complexidade de tempo dessa operação é O(n), onde n é o número de células
 * não zero da matriz b.
 *
 *  A complexidade poderia ser O(min(self, b)) da menor matriz esparsa, mas não
 * implementei assim.
 *
 *  A complexidade de espaço dessa operação é O(1), mesmo que haja a cópia da
 * matriz self e a adição ao espaço das células de b não zero de b que são zero
 * em self porque esse é o retoro da função e não um auxiliar usado
 * internamente.
 *
 * https://cs.stackexchange.com/a/149515
 */
CsrcMatrix *csrc_matrix_add(CsrcMatrix *self, CsrcMatrix *b);

/**
 * @brief
 *
 * @param self
 * @param scalar
 * @return CsrcMatrix*
 *
 * @note
 *
 *  A complexidade de tempo dessa operação é O(n), onde n é o número de células
 * não zero da matriz.
 *
 *  A complexidade de espaço dessa operação é O(1). Observações de
 * csrc_matrix_add quanto a isso se aplicarão para todas as operações que
 * retornam uma cópia.
 */
CsrcMatrix *csrc_matrix_mul_scalar(CsrcMatrix *self, double scalar);

/**
 * @brief
 *
 * @param self
 * @param b
 * @return CsrcMatrix*
 *
 * @note
 *
 *  A complexidade de tempo dessa operação é O(n * m), onde n é o número de
 * células não zero da matriz b e para cada n, m o número de células não zero da
 * coluna da matriz self respectiva a linha de da célula de b.
 *
 *  A complexidade poderia ser O(min(self, b)) da menor matriz esparsa, mas não
 * implementei assim.
 *
 *  A complexidade de espaço dessa operação é O(1).
 */
CsrcMatrix *csrc_matrix_mul(CsrcMatrix *self, CsrcMatrix *b);

/**
 * @brief
 *
 * @param self
 * @param b
 * @return CsrcMatrix*
 *
 * @note
 *
 *  A complexidade de tempo dessa operação é O(n * m), onde n é o número de
 * células não zero da matriz b.
 *
 *  A complexidade poderia ser O(min(self, b)) da menor matriz esparsa, mas não
 * implementei assim.
 *
 *  A complexidade de espaço dessa operação é O(1).
 */
CsrcMatrix *csrc_matrix_dot(CsrcMatrix *self, CsrcMatrix *b);

/**
 * @brief
 *
 * @param self
 * @param i1
 * @param i2
 * @return CsrcMatrix*
 *
 * @note
 *
 *  A complexidade de tempo dessa operação é O(max(l1, l2)), onde l1 e l2 são o número de células não zero das linhas i1 e i2, respectivamente.	
 *
 *  A complexidade de espaço dessa operação é O(1).
 */
CsrcMatrix *csrc_matrix_swap_rows(CsrcMatrix *self, size_t i1, size_t i2);

/**
 * @brief
 *
 * @param self
 * @param j1
 * @param j2
 * @return CsrcMatrix*
 *
 * @note
 *
 *  A complexidade de tempo dessa operação é O(max(c1, c2)), onde c1 e c2 são o número de colunas não zero das linhas j1 e j2, respectivamente.	
 *
 *  A complexidade de espaço dessa operação é O(1).
 */
CsrcMatrix *csrc_matrix_swap_cols(CsrcMatrix *self, size_t j1, size_t j2);

/**
 * @brief
 *
 * @param self
 * @param i1
 * @param j1
 * @param i2
 * @param j2
 * @return CsrcMatrix*
 *
 * @note
 *  A complexidade de tempo dessa operação é O(n), onde n é o número de células
 * não zero da matriz self que estão no intervalo [(i1, j1), (i2, j2)].
 *
 *  A complexidade de espaço dessa operação é O(1).
 */
CsrcMatrix *csrc_matrix_slice(CsrcMatrix *self, size_t i1, size_t j1, size_t i2,
                              size_t j2);

/**
 * @brief
 *
 * @param self
 * @return CsrcMatrix*
 *
 * @note
 *  A complexidade de tempo dessa operação é O(n), onde n é o número de células
 * não zero da matriz.
 *
 * A complexidade de espaço dessa operação é O(1).
 */
CsrcMatrix *csrc_matrix_transpose(CsrcMatrix *self);

/**
 * @brief
 *
 * @param self
 * @param kernel
 * @return CsrcMatrix*
 *
 * @note
 *  A complexidade de tempo dessa operação é O(n * e * k), onde n é o número de
 * células não zero da matriz self, e é o número de células adjacentes à célula
 * de self que é determinado pelo tamanho do kernel e k é o número de células
 * não zero do kernel.
 *
 *  Note que esse algoritmo é otimizado somente para matrizes esparsas, onde se
 * admite a sobreposição entre áreas adjacentes à célula de self que se torna
 * mais custoso quanto mais densa a matriz.
 *
 *  A complexidade de espaço dessa operação é O(1).
 */
CsrcMatrix *csrc_matrix_convolution(CsrcMatrix *self, CsrcMatrix *kernel);

#endif
