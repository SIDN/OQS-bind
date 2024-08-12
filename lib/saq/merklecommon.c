#include <saq/merklecommon.h>

SAQ_STATUS
SAQ_list_get_next(SAQ_list_t *n, SAQ_list_node_t **next) {
    if (n == NULL || next == NULL) {
        return SAQ_FAILURE;
    }
    *next = n->next;
    return SAQ_SUCCESS;
}

SAQ_STATUS
SAQ_list_get_data(SAQ_list_node_t *n, uint64_t i, void **out) {
    if (n == NULL || out == NULL) {
        return SAQ_FAILURE;
    }
    uint64_t j = 0;
    while (n != NULL && j < i) {
        if (SAQ_list_get_next(n, &n) != SAQ_SUCCESS) {
            *out = NULL;
            return SAQ_FAILURE;
        }
        j++;
    }
    if (j != i || n == NULL) {
        *out = NULL;
        return SAQ_FAILURE;
    }
    *out = n->data;
    return SAQ_SUCCESS;
}

SAQ_STATUS
SAQ_list_append(SAQ_list_t **l, void *d) {
    SAQ_list_node_t *n = malloc(sizeof(SAQ_list_node_t));
    n->data = d;
    n->next = NULL;
    if (*l == NULL) {
        *l = n;
        return SAQ_SUCCESS;
    }
    SAQ_list_node_t *c = *l;
    while (c != NULL) {
        SAQ_list_node_t *next;
        if (SAQ_list_get_next(c, &next) != SAQ_SUCCESS) {
            return SAQ_FAILURE;
        }
        if (next == NULL) {
            c->next = n;
            return SAQ_SUCCESS;
        }
        c = next;
    }
    return SAQ_FAILURE;
}

void
SAQ_list_destroy(SAQ_list_t **l, void (*free_cb)(void *)) {
    if (l == NULL || *l == NULL) {
        return;
    }
    SAQ_list_node_t *c = *l;
    while (c != NULL) {
        SAQ_list_node_t *n;
        SAQ_list_get_next(c, &n);
        if (free_cb != NULL) {
            free_cb(c->data);
        }
        free(c);
        c = n;
    }
    *l = NULL;
}
