#include <stdint.h>
#include <stdlib.h>

#include "gl.h"

#include "DrawableGraph.h"
#include "GraphRenderer.h"
#include "GraphRPCService.h"

// global graph list for now
DrawableGraph *konig_graph = NULL;

// global renderer
GraphRenderer *konig_renderer = NULL;
google::protobuf::Service *konig_rpc_service = NULL;

// global object counter for now
uint32_t konig_graphcount = 0;

// C interface to manipulate graph
#ifdef __cplusplus
extern "C" {
#endif

uint8_t konig_bootstrap(void) {
    // seed the prng
    unsigned seed = (unsigned)time(0);
    srand(seed);

    // setup the renderer
    konig_renderer = GraphRenderer::instance();

    // graph
    konig_graph = new DrawableGraph();

    // setup the rpc server
    konig_rpc_service = new GraphRPCService();

    return 1;
}

void konig_shutdown(void) {
    delete konig_renderer;
}

uint8_t konig_done(void) {
    return konig_renderer->done();
}

uint8_t konig_update(void) {
    // get dt
    // step graph
    // step solver
    // step renderer
    return konig_renderer->update(konig_graph);
}

uint8_t konig_draw(void) {
    return konig_renderer->draw(konig_graph);
}

uint32_t konig_graph_add_vertex() {
    return konig_graph->add_vertex();
}

uint8_t konig_graph_delete_vertex(uint32_t vertex_idx) {
    return konig_graph->delete_vertex(vertex_idx);
}

uint32_t konig_graph_add_edge(uint32_t vertex_idx1, uint32_t vertex_idx2) {
    return konig_graph->add_edge(vertex_idx1, vertex_idx2);
}

uint8_t konig_graph_delete_edge(uint32_t edge_idx) {
    return konig_graph->delete_edge(edge_idx);
}

#ifdef __cplusplus
}
#endif
