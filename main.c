#include <konig.h>

int main(int argc, char **argv) {
    // bootstraps update thread and drawing on main thread
    konig_bootstrap();

    uint32_t graph_id = konig_add_graph();
    for (uint32_t i=0; i<pow(2, 10); i++) {
        konig_graph_add_vertex(graph_id);
    }

    // for (uint32_t i=0; i<10e4-1; i++) {
    //     konig_graph_add_edge(graph_id, i, i+1);
    // }

    while (!konig_done()) {
        konig_update();
        konig_draw();
    }

    konig_shutdown();
}
