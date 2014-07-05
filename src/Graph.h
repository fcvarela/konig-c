#ifndef KONIG_GRAPH_H
#define KONIG_GRAPH_H

#include <vector>
#include <stdint.h>

// for pure sequential memory (draw as vbo fast)
typedef struct {
    uint32_t active;
    float x;
    float y;
    float z;
} vertex_t;

// for pure sequential memory (draw as vbo fast)
typedef struct {
    uint32_t active;
    uint32_t vertex_idx1;
    uint32_t vertex_idx2;
} edge_t;

class Graph {
private:
    // pure vector storage for position computing and drawing
    std::vector<vertex_t> vertex_array;
    std::vector<edge_t> edge_array;
public:
    Graph();
    ~Graph();

    uint32_t add_vertex();
    uint32_t add_edge(uint32_t vertex_idx1, uint32_t vertex_idx2);
    bool delete_vertex(uint32_t vertex_idx);
    bool delete_edge(uint32_t edge_idx);
};

#endif
