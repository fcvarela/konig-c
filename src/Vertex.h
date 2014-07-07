#ifndef KONIG_VERTEX_H
#define KONIG_VERTEX_H

namespace konig {

// for pure sequential memory (draw as vbo fast)
// aligned to 16 bytes for opencl null padding
typedef struct {
    float pos[4];
    float vel[4];
} vertex_t;

// for pure sequential memory (draw as vbo fast)
typedef struct {
    uint32_t active;
    uint32_t vertex_idx1;
    uint32_t vertex_idx2;
} edge_t;

}

#endif
