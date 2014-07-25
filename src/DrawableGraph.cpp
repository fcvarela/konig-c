#include <string.h>
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
    glDeleteBuffers(1, &vbo_in);
    glDeleteBuffers(1, &vbo_out);
    glDeleteBuffers(1, &edge_vbo);

    delete solver;
}

void DrawableGraph::step(double dt) {
    // are we dirty?
    if (glfwGetTime() - last_update > 0.1 && dirty) {
        // move all of the append logic to the addvertex function
        if (inited) {
            glBindBuffer(GL_ARRAY_BUFFER, vbo_out);
            vertex_t *vptr = (vertex_t *)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);

            for (size_t count=0; count<vertex_array.size(); count++) {
                memcpy(&vertex_array[count], &vptr[count], sizeof(vertex_t));
            }
            glUnmapBuffer(GL_ARRAY_BUFFER);
        }

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
        old_capacity = vertex_array.capacity();
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
    newvertex.pos[0] = (float)(rand()) / (float)(RAND_MAX) * 500.0;
    newvertex.pos[1] = (float)(rand()) / (float)(RAND_MAX) * 500.0;
    newvertex.pos[2] = (float)(rand()) / (float)(RAND_MAX) * 500.0;
    newvertex.pos[3] = 1.0f;

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
    newedge.pad1 = 0;
    newedge.pad2 = 0;

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
