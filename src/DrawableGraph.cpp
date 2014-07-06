#include <stdlib.h>

#include "DrawableGraph.h"

namespace konig {

DrawableGraph::DrawableGraph() {
    this->inited = false;
    this->last_update = glfwGetTime();
    this->dirty = false;

    solver = new ParticleSolver();

    glGenBuffers(1, &this->vbo);
}

DrawableGraph::~DrawableGraph() {

}

void DrawableGraph::step(double dt) {
    // are we dirty?
    if (glfwGetTime() - this->last_update > 0.1 && this->dirty) {
        size_t byte_size = this->vertex_array.size() * sizeof(this->vertex_array[0]);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferData(GL_ARRAY_BUFFER, byte_size, &this->vertex_array[0], GL_DYNAMIC_DRAW);
        this->buffer = &this->vertex_array[0];
        this->element_count = this->vertex_array.size();
        this->inited = true;
        this->dirty = false;
    }

    // physical simulation step
    for (size_t i=0; i<this->vertex_array.size(); i++) {
        if (!this->vertex_array[i].active)
            continue;

        this->vertex_array[i].x += this->vertex_array[i].vx * dt;
        this->vertex_array[i].y += this->vertex_array[i].vy * dt;
        this->vertex_array[i].z += this->vertex_array[i].vz * dt;
    }

    // update vbo w/ simulation step
    size_t byte_size = this->vertex_array.size() * sizeof(this->vertex_array[0]);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, byte_size, &this->vertex_array[0]);
}

uint32_t DrawableGraph::add_vertex() {
    vertex_t newvertex;

    newvertex.active = 1;

    // randomize starting position (-1 to 1)
    newvertex.x = (float)(rand()) / (float)(RAND_MAX/2.0) - 1.0;
    newvertex.y = (float)(rand()) / (float)(RAND_MAX/2.0) - 1.0;
    newvertex.z = (float)(rand()) / (float)(RAND_MAX/2.0) - 1.0;

    newvertex.vx = ((float)(rand()) / (float)(RAND_MAX/2.0) - 1.0) / 5.0;
    newvertex.vy = ((float)(rand()) / (float)(RAND_MAX/2.0) - 1.0) / 5.0;
    newvertex.vz = ((float)(rand()) / (float)(RAND_MAX/2.0) - 1.0) / 5.0;

    this->vertex_array.push_back(newvertex);

    this->last_update = glfwGetTime();
    this->dirty = true;

    return this->vertex_array.size() - 1;
}

uint32_t DrawableGraph::add_edge(uint32_t vertex_idx1, uint32_t vertex_idx2) {
    edge_t newedge;

    newedge.active = 1;
    newedge.vertex_idx1 = vertex_idx1;
    newedge.vertex_idx2 = vertex_idx2;

    return true;
}

bool DrawableGraph::delete_vertex(uint32_t vertex_idx) {
    this->vertex_array[vertex_idx].active = 0;
    return true;
}

bool DrawableGraph::delete_edge(uint32_t edge_idx) {
    this->edge_array[edge_idx].active = 0;
    return true;
}

}