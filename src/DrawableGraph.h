#ifndef KONIG_DRAWABLE_GRAPH_H
#define KONIG_DRAWABLE_GRAPH_H

#include <vector>
#include <stdint.h>

#include <GLFW/glfw3.h>

#include "Vertex.h"

namespace konig {

// note that we don't actually need to perform _any_ graph
// operations such as searches, paths, spanning trees, etc
// and 'algotithm' implements a binary search (find). we can
// therefore afford to search using it (for deletions, ex).
// complexity is still on par w/ a binary tree search if using
// list/set w/ pointers to actual data

class ParticleSolver;

class DrawableGraph {
private:
    double last_update;
public:
    // pure vector storage for position computing and drawing
    std::vector<vertex_t> vertex_array;
    std::vector<edge_t> edge_array;

    void *buffer;
    size_t element_count;
    bool dirty;

    bool inited;

    ParticleSolver *solver;
    
    DrawableGraph();
    ~DrawableGraph();

    void step(double dt);
    uint32_t add_vertex();
    uint32_t add_edge(uint32_t vertex_idx1, uint32_t vertex_idx2);
    bool delete_vertex(uint32_t vertex_idx);
    bool delete_edge(uint32_t edge_idx);
};

}

#endif
