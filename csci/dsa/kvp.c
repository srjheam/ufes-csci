#include "dsa/kvp.h"

kvp *kvp_constructor(size_t smemb_key, size_t smemb_value, void *key, void *value) {
    kvp *pair = malloc(sizeof *pair);

    pair->smemb_key = smemb_key;
    pair->smemb_value = smemb_value;

    pair->key = malloc(smemb_key);
    pair->value = malloc(smemb_value);

    memcpy(pair->key, key, smemb_key);
    memcpy(pair->value, value, smemb_value);

    return pair;
}

void *kvp_getkey(kvp *pair) {
    return pair->key;
}

void *kvp_getvalue(kvp *pair) {
    return pair->value;
}

void *kvp_setvalue(kvp *pair, void *value) {
    void *ov = pair->value;
    pair->value = value;
    return ov;
}

void kvp_destructor(kvp *pair) {
    free(pair->key);
    free(pair->value);

    free(pair);
}
