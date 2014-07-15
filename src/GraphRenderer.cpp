#include <math.h>
#include <stdlib.h>

#include "GraphRenderer.h"
#include "DrawableGraph.h"
#include "Texture.h"

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
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // make sure we take into account expanding the box
    // (10.0->whatever bounding sphere diameter is)
    GraphRenderer::set_perspective(60.0, (GLfloat)width/(GLfloat)height, 1.0, 200.0);

    // setup modelview
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

GraphRenderer::GraphRenderer() {
    if (!glfwInit()) {
        fprintf(stderr, "Error intializing glfw\n");
        exit(EXIT_FAILURE);
    }

    // request fullscreen
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    window = glfwCreateWindow(mode->width/2, mode->height/2, "Konig", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    last_update = glfwGetTime();

    glfwMakeContextCurrent(window);
    glewInit();
    glfwSetKeyCallback(window, GraphRenderer::key_callback);
    glfwSetFramebufferSizeCallback(window, GraphRenderer::reshape_callback);
    glfwSwapInterval(1);

    // load texture here for now: needs refactoring
    // glGenTextures(1, &point_texture);
    // glBindTexture(GL_TEXTURE_2D, point_texture);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // point_texture = SOIL_load_OGL_texture("data/textures/particle.bmp", SOIL_LOAD_AUTO, point_texture, SOIL_FLAG_MIPMAPS);

    // set basic properties
    glPointSize(8.0);
    // glTexEnvf(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
    // glEnable(GL_POINT_SPRITE);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    // glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, GL_LOWER_LEFT);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    glLineWidth(2.0);
    glEnable(GL_LINE_SMOOTH);

    GraphRenderer::reshape_callback(window, mode->width/2.0, mode->height/2.0);

    angle = 0.0;
}

GraphRenderer::~GraphRenderer() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool GraphRenderer::done() {
    return glfwWindowShouldClose(window);
}

bool GraphRenderer::update(std::map<uint32_t, DrawableGraph*> *graph_list) {
    double dt = glfwGetTime() - last_update;

    std::map<uint32_t, DrawableGraph *>::iterator iter;
    for (iter = graph_list->begin(); iter != graph_list->end(); iter++) {
        DrawableGraph *graph = iter->second;
        graph->step(dt);
    }

    glfwPollEvents();

    last_update = glfwGetTime();
    return true;
}

bool GraphRenderer::draw(std::map<uint32_t, DrawableGraph*> *graph_list) {
    // glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, output_texture->id, 0);
    //output_texture->bind(GL_TEXTURE1);

    angle += (glfwGetTime() - last_update)*450000.0;

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -100.0);
    //glRotatef(angle, 0.0, 1.0, 0.0);

    glEnableClientState(GL_VERTEX_ARRAY);

    std::map<uint32_t, DrawableGraph *>::iterator iter;
    for (iter = graph_list->begin(); iter != graph_list->end(); iter++) {
        DrawableGraph *graph = iter->second;
        if (!graph->inited)
            continue;

        glColor3f(0.0, 1.0, 0.0);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, point_texture);

        glBindBuffer(GL_ARRAY_BUFFER, graph->vbo_out);
        glVertexPointer(3, GL_FLOAT, sizeof(vertex_t), 0);
        glDrawArrays(GL_POINTS, 0, graph->vertex_element_count);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDisable(GL_TEXTURE_2D);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor3f(1.0, 0.0, 0.0);
        glEnableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, graph->vbo_out);
        glVertexPointer(3, GL_FLOAT, sizeof(vertex_t), 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, graph->edge_vbo);
        glDrawElements(GL_LINES, graph->edge_array.size()*2, GL_UNSIGNED_INT, 0);
        glDisableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    // glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glFlush();
    glfwSwapBuffers(window);
    glFinish();
    return true;
}
