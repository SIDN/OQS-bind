#ifndef __MERKLE_COMMON_H__
#define __MERKLE_COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SAQ_STATUS  int

#define SAQ_SUCCESS 0
#define SAQ_FAILURE 1

/// \brief Hashing callback function used by a Merkle Nodes, Authenticating Paths, and Merkle Streams.
///
/// \param[in] data The data to be hashed.
/// \param[in] data_len The length of the byte region pointed to by data.
/// \param[out] hash The byte region to store the computed hash in.
/// \param[out] hash_len The length of the computed hash. If hash is NULL
///             hash_len will be updated with how large the hash would have been.
///
/// \return SAQ_SUCCESS if hashing was successful; SAQ_FAILURE otherwise.
typedef SAQ_STATUS(SAQ_hash_cb)(unsigned char *data, uint64_t data_len,
                                unsigned char *hash, uint64_t *hash_len);
typedef SAQ_hash_cb *SAQ_hash_cb_ptr;

/// \brief A generic list. It is assumed that each element of a given list
///        points to the same type of data.
typedef struct SAQ_list_node SAQ_list_node_t;

/// \brief A generic list node.
typedef SAQ_list_node_t SAQ_list_t;

struct SAQ_list_node {
    void *data;
    struct SAQ_list_node *next;
};

/// \brief Initalizes an SAQ_list_t.
///
/// \param[in, out] l The list to be initalized.
#define SAQ_list_init(l) do { \
	*l = NULL;            \
} while (0)

/// \brief Fetches the next node in the list.
///
/// \param[in] l The list.
/// \param[out] next The next node in the list. NULL if there is none.
///
/// \return SAQ_SUCCESS if next node was successfully fetched; SAQ_FAILURE otherwise.
SAQ_STATUS
SAQ_list_get_next(SAQ_list_t *n, SAQ_list_node_t **next);

/// \brief Gets the data i steps away from the given SAQ_list_node_t.
///
/// \param[in] l The list.
/// \param[in] i The number of steps away from the current node the data is located.
/// \param[out] out The data from the current position in the list.
///
/// \return A pointer to the data if found; NULL otherwise.
SAQ_STATUS
SAQ_list_get_data(SAQ_list_node_t *n, uint64_t i, void **p);

/// \brief Appends data to a SAQ_list_t.
///
/// \param[in] l The list to append the data, d, to.
/// \param[in] d The data to append to list l.
///
/// \return SAQ_SUCCESS if d was appended to l; SAQ_FAILURE otherwise.
SAQ_STATUS
SAQ_list_append(SAQ_list_t **l, void *d);

/// \brief Destroys the given SAQ_list_t l and optionally frees the data it points to.
///
/// \param[in] l The list to be destroyed.
/// \param[in] free_cb The function to use to free the data the list points to.
///                    If NULL then the data is not freed.
void
SAQ_list_destroy(SAQ_list_t **l, void (*free_cb)(void *));

#endif /* __MERKLE_COMMON_H__ */
