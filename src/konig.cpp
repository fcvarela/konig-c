#include <stdint.h>
#include <stdlib.h>

#include <map>

#include "Graph.h"
#include "GraphRenderer.h"

using namespace konig;

// global graph list for now
std::map<uint32_t, Graph*> konig_graph_list;

// global renderer
GraphRenderer *konig_renderer;

// global object counter for now
uint32_t konig_graphcount = 0;

// C interface to manipulate graph
#ifdef __cplusplus
extern "C" {
#endif

uint8_t konig_bootstrap(void) {
    // seed the prng
    unsigned seed = (unsigned)time(0);
    fprintf(stderr, "Seeding prng: %u\n", seed);
    srand(seed);

    // setup the renderer
    konig_renderer = new GraphRenderer();

    return 1;
}

void konig_shutdown(void) {

}

uint8_t konig_done(void) {
    return 0;

}

uint8_t konig_update(void) {
    return 1;
}

uint8_t konig_draw(void) {
    return 1;
}

uint32_t konig_add_graph(void) {
    konig_graph_list[++konig_graphcount] = new Graph();
    return konig_graphcount;
}

uint32_t konig_graph_add_vertex(uint32_t graph_idx) {
    return konig_graph_list[graph_idx]->add_vertex();
}

uint8_t konig_graph_delete_vertex(uint32_t graph_idx, uint32_t vertex_idx) {
    return konig_graph_list[graph_idx]->delete_vertex(vertex_idx);
}

uint32_t konig_graph_add_edge(uint32_t graph_idx, uint32_t vertex_idx1, uint32_t vertex_idx2) {
    return konig_graph_list[graph_idx]->add_edge(vertex_idx1, vertex_idx2);
}

uint8_t konig_graph_delete_edge(uint32_t graph_idx, uint32_t edge_idx) {
    return konig_graph_list[graph_idx]->delete_edge(edge_idx);
}

#ifdef __cplusplus
}
#endif
