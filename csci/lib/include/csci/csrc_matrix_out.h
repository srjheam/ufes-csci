#ifndef _CSCI_CSRC_MATRIX_OUT_H_
#define _CSCI_CSRC_MATRIX_OUT_H_

#include "csci/csrc_matrix.h"

/**
 * @brief
 *
 * @param self
 *
 * @note
 *  A complexidade de tempo dessa operação é O(n), onde n é o número de células
 * não zero da matriz.
 *
 * A complexidade de espaço dessa operação é O(1).
 */
void csrc_matrix_print_sparse(CsrcMatrix *self);

/**
 * @brief
 *
 * @param self
 *
 * @note
 *  A complexidade de tempo dessa operação é O(n * m), onde n é o número de
 * linhas da matriz e m é o número de colunas da matriz; ou seja, o número de
 * células da matriz, incluindo zeros.
 *
 * A complexidade de espaço dessa operação é O(1).
 */
void csrc_matrix_print_dense(CsrcMatrix *self);

/**
 * @brief
 *
 * @param self
 * @param path
 *
 * @note
 *  A complexidade de tempo dessa operação é O(n), onde n é o número de células
 * não zero da matriz.
 *
 * A complexidade de espaço dessa operação é O(1).
 */
void csrc_matrix_save(CsrcMatrix *self, char *path);

/**
 * @brief
 *
 * @param path
 * @return CsrcMatrix*
 *
 * @note
 *  A complexidade de tempo dessa operação é O(n), onde n é o número de células
 * não zero da matriz.
 *
 * A complexidade de espaço dessa operação é O(1).
 */
CsrcMatrix *csrc_matrix_load(char *path);

/**
 * @brief
 *
 * @param self
 * @param path
 *
 * @note
 *  A complexidade de tempo dessa operação é O(n), onde n é o número de células
 * não zero da matriz.
 *
 * A complexidade de espaço dessa operação é O(1).
 */
CsrcMatrix *csrc_matrix_read();

#endif
