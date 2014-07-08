#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <konig.h>

int main(int argc, char **argv) {
    // bootstraps update thread and drawing on main thread
    konig_bootstrap();

    size_t ring_size = 100;

    uint32_t graph_id = konig_add_graph();
    for (uint32_t i=0; i<ring_size; i++) {
        konig_graph_add_vertex(graph_id);
    }

    for (uint32_t i=0; i<ring_size; i++) {
        konig_graph_add_edge(graph_id, i, (i+1)%ring_size);
        fprintf(stderr, "%d %d\n", i, (i+1)%ring_size);
    }

    while (!konig_done()) {
        konig_update();
        konig_draw();
    }

    konig_shutdown();
}
