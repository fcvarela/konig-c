#include <stdlib.h>

#include "DrawableGraph.h"
#include "ParticleSolver.h"

DrawableGraph::DrawableGraph() {
    inited = false;
    last_update = glfwGetTime();
    dirty = false;

    solver = new ParticleSolver();

    glGenBuffers(1, &vbo_in);
    glGenBuffers(1, &vbo_out);
    glGenBuffers(1, &edge_vbo);
}

DrawableGraph::~DrawableGraph() {

}

void DrawableGraph::step(double dt) {
    // are we dirty?
    if (glfwGetTime() - last_update > 0.1 && dirty) {
        // copy from out into vertex_array!!!
        size_t vertex_byte_size = vertex_array.size() * sizeof(vertex_array[0]);
        size_t edge_byte_size = edge_array.size() * sizeof(edge_array[0]);

        glBindBuffer(GL_ARRAY_BUFFER, vbo_in);
        glBufferData(GL_ARRAY_BUFFER, vertex_byte_size, &vertex_array[0], GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, vbo_out);
        glBufferData(GL_ARRAY_BUFFER, vertex_byte_size, &vertex_array[0], GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edge_vbo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, edge_byte_size, &edge_array[0], GL_DYNAMIC_DRAW);

        inited = true;
        dirty = false;
        vertex_element_count = vertex_array.size();
        edge_element_count = edge_array.size();
    }

    if (!inited)
        return;

    solver->step(vbo_in, vbo_out, edge_vbo, vertex_element_count, edge_element_count, dt);

    // swap the vbos
    GLuint temp = vbo_in;
    vbo_in = vbo_out;
    vbo_out = temp;
}

uint32_t DrawableGraph::add_vertex() {
    vertex_t newvertex;

    // randomize starting position (-1 to 1)
    newvertex.pos[0] = (float)(rand()) / (float)(RAND_MAX/5.0) - 2.5;
    newvertex.pos[1] = (float)(rand()) / (float)(RAND_MAX/5.0) - 2.5;
    newvertex.pos[2] = 0.0f;//(float)(rand()) / (float)(RAND_MAX/100.0) - 50.0;
    newvertex.pos[3] = 0.0f;

    newvertex.vel[0] = 0.0;
    newvertex.vel[1] = 0.0;
    newvertex.vel[2] = 0.0;
    newvertex.vel[3] = 0.0;

    vertex_array.push_back(newvertex);

    last_update = glfwGetTime();
    dirty = true;

    return vertex_array.size() - 1;
}

uint32_t DrawableGraph::add_edge(uint32_t vertex_idx1, uint32_t vertex_idx2) {
    edge_t newedge;

    newedge.vertex_idx1 = vertex_idx1;
    newedge.vertex_idx2 = vertex_idx2;

    edge_array.push_back(newedge);

    last_update = glfwGetTime();
    dirty = true;

    return vertex_array.size() - 1;
}

bool DrawableGraph::delete_vertex(uint32_t vertex_idx) {
    // vertex_array[vertex_idx].active = 0;
    return true;
}

bool DrawableGraph::delete_edge(uint32_t edge_idx) {
    // edge_array[edge_idx].active = 0;
    return true;
}
