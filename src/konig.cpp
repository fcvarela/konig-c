#include <stdint.h>
#include <stdlib.h>

#include <map>

#include "Graph.h"

// global graph list for now
std::map<uint32_t, Graph*> konig_graph_list;

// global object counter for now
uint32_t konig_graphcount = 0;

// C interface to manipulate graph
extern "C" uint8_t konig_bootstrap(void) {
    // seed the prng
    unsigned seed = (unsigned)time(0);
    fprintf(stderr, "Seeding prng: %u\n", seed);
    srand(seed);

    return 1;
}

extern "C" void konig_shutdown(void) {

}

extern "C" uint8_t konig_done(void) {
    return 0;

}

extern "C" uint8_t konig_update(void) {
    return 1;
}

extern "C" uint8_t konig_draw(void) {
    return 1;
}

extern "C" uint32_t konig_add_graph(void) {
    konig_graph_list[++konig_graphcount] = new Graph();
    return konig_graphcount;
}

extern "C" uint32_t konig_graph_add_vertex(uint32_t graph_idx) {
    return konig_graph_list[graph_idx]->add_vertex();
}

extern "C" uint8_t konig_graph_delete_vertex(uint32_t graph_idx, uint32_t vertex_idx) {
    return konig_graph_list[graph_idx]->delete_vertex(vertex_idx);
}

extern "C" uint32_t konig_graph_add_edge(uint32_t graph_idx, uint32_t vertex_idx1, uint32_t vertex_idx2) {
    return konig_graph_list[graph_idx]->add_edge(vertex_idx1, vertex_idx2);
}

extern "C" uint8_t konig_graph_delete_edge(uint32_t graph_idx, uint32_t edge_idx) {
    return konig_graph_list[graph_idx]->delete_edge(edge_idx);
}
