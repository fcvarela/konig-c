#include <stdint.h>


// zero values mean deleted and waiting for periodic reallocation (shrink, etc)
// we need underlying array storage types to make sure contents are in chunks
// of sequential memory. that means they can be drawn efficiently
typedef struct {
    uint64_t id;
    uint64_t *adjacency_list;
} konig_vertex_t;

typedef struct {
    uint64_t id;
    konig_vertex_t *vertices;
} konig_graph_t;