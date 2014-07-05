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
    
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -2.0);
    glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
    
    glBegin(GL_QUADS);
    
    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(-0.5f, -0.5f, 0.f);
    
    glColor3f(0.f, 1.f, 0.f);
    glVertex3f(0.5f, -0.5f, 0.f);
    
    glColor3f(0.f, 0.f, 1.f);
    glVertex3f(0.5f, 0.5f, 0.f);

    glColor3f(0.f, 1.f, 1.f);
    glVertex3f(-0.5f, 0.5f, 0.f);
    
    glEnd();
    
    glfwSwapBuffers(window);
    return true;
}

}