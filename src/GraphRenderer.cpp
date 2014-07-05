#include <math.h>
#include <stdlib.h>

#include "GraphRenderer.h"

namespace konig {

void GraphRenderer::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void GraphRenderer::set_perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar) {
    GLdouble xmin, xmax, ymin, ymax;

    ymax = zNear * tan(fovy * M_PI / 360.0);
    ymin = -ymax;
    xmin = ymin * aspect;
    xmax = ymax * aspect;
    glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
}

void GraphRenderer::reshape_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // make sure we take into account expanding the box (10.0->whatever bounding sphere diameter is)
    GraphRenderer::set_perspective(60.0, (GLfloat)width/(GLfloat)height, 1.0, 10.0);

    // setup modelview
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

GraphRenderer::GraphRenderer() {
    if (!glfwInit()) {
        fprintf(stderr, "Error intializing glfw\n");
        exit(EXIT_FAILURE);
    }

    this->window = glfwCreateWindow(1280, 800, "Konig", NULL, NULL);
    if (!this->window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(this->window);
    glfwSetKeyCallback(this->window, GraphRenderer::key_callback);
    glfwSetFramebufferSizeCallback(this->window, GraphRenderer::reshape_callback);

    GraphRenderer::reshape_callback(this->window, 1280, 800);
}

GraphRenderer::~GraphRenderer() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool GraphRenderer::done() {
    return glfwWindowShouldClose(this->window);
}

bool GraphRenderer::update(std::map<uint32_t, DrawableGraph*> *graph_list) {
    glfwPollEvents();
    return true;
}

bool GraphRenderer::draw(std::map<uint32_t, DrawableGraph*> *graph_list) {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glPointSize(4.0);
    
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -3.0);
    
    glEnableClientState(GL_VERTEX_ARRAY);

    std::map<uint32_t, DrawableGraph *>::iterator iter;
    for (iter = graph_list->begin(); iter != graph_list->end(); iter++) {
        DrawableGraph *graph = iter->second;
        glVertexPointer(3, GL_FLOAT, sizeof(graph->vertex_array[0]), (float *)&graph->vertex_array[0].x);
        glDrawArrays(GL_POINTS, 0, graph->vertex_array.size());
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    
    glfwSwapBuffers(window);
    return true;
}

}