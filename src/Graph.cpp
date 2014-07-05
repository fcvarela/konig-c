#include <stdlib.h>

#include "Graph.h"

Graph::Graph() {

}

Graph::~Graph() {

}

uint32_t Graph::add_vertex() {
    vertex_t newvertex;

    newvertex.active = 1;

    // randomize starting position
    newvertex.x = (float)(rand()) / (float)(RAND_MAX);
    newvertex.y = (float)(rand()) / (float)(RAND_MAX);
    newvertex.z = (float)(rand()) / (float)(RAND_MAX);

    this->vertex_array.push_back(newvertex);
    size_t vas = this->vertex_array.size();
    
    return vas;
}

uint32_t Graph::add_edge(uint32_t vertex_idx1, uint32_t vertex_idx2) {
    edge_t newedge;

    newedge.active = 1;
    newedge.vertex_idx1 = vertex_idx1;
    newedge.vertex_idx2 = vertex_idx2;

    return true;
}

bool Graph::delete_vertex(uint32_t vertex_idx) {
    this->vertex_array[vertex_idx].active = 0;
    return true;
}

bool Graph::delete_edge(uint32_t edge_idx) {
    this->edge_array[edge_idx].active = 0;
    return true;
}
