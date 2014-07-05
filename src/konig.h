#ifndef KONIG_H
#define KONIG_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
#endif

uint8_t konig_bootstrap(void);
uint8_t konig_shutdown(void);
uint8_t konig_done(void);
uint8_t konig_update(void);
uint8_t konig_draw(void);

uint32_t konig_add_graph(void);
uint32_t konig_graph_add_vertex(uint32_t graph_id);
uint8_t konig_graph_delete_vertex(uint32_t graph_id, uint32_t vertex_id);
uint32_t konig_graph_add_edge(uint32_t graph_id, uint32_t vertex_id, uint32_t vertex_id2);
uint8_t konig_graph_delete_edge(uint32_t edge_id);

#endif
