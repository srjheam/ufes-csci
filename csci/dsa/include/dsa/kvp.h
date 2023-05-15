#ifndef _KVP_H_
#define _KVP_H_

#include "dsa/common.h"

typedef struct kvp {
    byte *key;
    byte *value;

    size_t smemb_key;
    size_t smemb_value;
} kvp;

kvp *kvp_constructor(size_t smemb_key, size_t smemb_value, void *chave, void *valor);

void *kvp_getkey(kvp *pair);

void *kvp_getvalue(kvp *pair);

void *kvp_setvalue(kvp *pair, void *value);

void kvp_destructor(kvp *pair);

#endif
