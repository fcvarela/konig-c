#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "konig.h"

uint32_t tree(uint32_t parent, uint32_t n) {
    uint32_t vid = konig_graph_add_vertex();
    konig_graph_add_edge(parent, vid);

    if (n <= 0)
        return vid;

    for (int j=0; j<2; j++) {
        tree(vid, n-1);
    }

    return vid;
}

int main(int argc, char **argv) {
    // bootstraps update thread and drawing on main thread
    konig_bootstrap();

    // binary tree
    uint32_t root_vid = konig_graph_add_vertex();
    tree(root_vid, 9);

    // circle
    while (!konig_done()) {
        konig_update();
        konig_draw();
    }

    konig_shutdown();
}
