#include <stdlib.h>

#include "DrawableGraph.h"

namespace konig {

DrawableGraph::DrawableGraph() {
    this->inited = false;
    this->last_update = glfwGetTime();
    this->dirty = false;

    solver = new ParticleSolver();

    glGenBuffers(1, &this->vbo_in);
    glGenBuffers(1, &this->vbo_out);
}

DrawableGraph::~DrawableGraph() {

}

void DrawableGraph::step(double dt) {
    // are we dirty?
    if (glfwGetTime() - this->last_update > 0.1 && this->dirty) {
        // copy from out into vertex_array!!!
        size_t byte_size = this->vertex_array.size() * sizeof(this->vertex_array[0]);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo_in);
        glBufferData(GL_ARRAY_BUFFER, byte_size, &this->vertex_array[0], GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, this->vbo_out);
        glBufferData(GL_ARRAY_BUFFER, byte_size, &this->vertex_array[0], GL_DYNAMIC_DRAW);
        
        this->buffer = &this->vertex_array[0];
        this->inited = true;
        this->dirty = false;
        this->element_count = this->vertex_array.size();
    }

    if (!this->inited)
        return;

    solver->step(this->vbo_in, this->vbo_out, element_count, dt);

    // swap the vbos
    GLuint temp = this->vbo_in;
    this->vbo_in = this->vbo_out;
    this->vbo_out = temp;
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