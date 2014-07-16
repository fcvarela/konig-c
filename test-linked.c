#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <konig.h>

uint32_t graph_id = 0;

uint32_t tree(uint32_t parent, uint32_t n) {
    uint32_t vid = konig_graph_add_vertex(graph_id);
    uint32_t eid = konig_graph_add_edge(graph_id, parent, vid);

    if (n > 0) {
        for (int j=0; j<2; j++) {
            uint32_t v2 = tree(vid, n-1);
        }
    }

    return vid;
}

int main(int argc, char **argv) {
    // bootstraps update thread and drawing on main thread
    konig_bootstrap();

    // binary tree
    graph_id = konig_add_graph();
    uint32_t root_vid = konig_graph_add_vertex(graph_id);
    uint32_t last_vid = tree(root_vid, 10);

    // circle
    while (!konig_done()) {
        konig_update();
        konig_draw();
    }

    konig_shutdown();
}
