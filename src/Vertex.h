#ifndef KONIG_VERTEX_H
#define KONIG_VERTEX_H

namespace konig {

// for pure sequential memory (draw as vbo fast)
typedef struct {
    uint32_t active;
    float x;
    float y;
    float z;
    float vx;
    float vy;
    float vz;
    float dummy;
} vertex_t;

// for pure sequential memory (draw as vbo fast)
typedef struct {
    uint32_t active;
    uint32_t vertex_idx1;
    uint32_t vertex_idx2;
} edge_t;

}

#endif
