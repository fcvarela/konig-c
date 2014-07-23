#include <math.h>
#include <stdlib.h>

#include "GraphRenderer.h"
#include "DrawableGraph.h"
#include "Texture.h"
#include "Vector.h"

void GraphRenderer::mouse_scroll_callback(GLFWwindow *window, double x, double y) {
    GraphRenderer *r = instance();

    r->ctr_distance -= y;
    if (r->ctr_distance > 900.0)
        r->ctr_distance = 900.0;

    if (r->ctr_distance < 50.0)
        r->ctr_distance = 50.0;
}

void GraphRenderer::mouse_click_callback(GLFWwindow *window, int button, int action, int mods) {
    GraphRenderer *r = instance();

    // mouse down?
    if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS) {
        r->mouse_down = true;
    }

    if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE) {
        r->mouse_down = false;
    }
}

void GraphRenderer::mouse_move_callback(GLFWwindow *window, double x, double y) {
    GraphRenderer *r = instance();

    if (r->mouse_down) {
        // get travel
        double mouse_up_coords[2];
        glfwGetCursorPos(r->window, &mouse_up_coords[0], &mouse_up_coords[1]);

        double mouse_travel[2];
        mouse_travel[0] = (r->prev_mouse_coords[0] - mouse_up_coords[0]);
        mouse_travel[1] = (r->prev_mouse_coords[1] - mouse_up_coords[1]);

        Vector3d delta = Vector3d(mouse_travel[1], mouse_travel[0], 0.0);
        double deltalen = delta.length();
        delta.normalize();

        r->rotation = r->rotation * Quatd(delta, deltalen);
    }
    glfwGetCursorPos(r->window, &r->prev_mouse_coords[0], &r->prev_mouse_coords[1]);
}

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
    int fb_width, fb_height;
    glfwGetFramebufferSize(window, &fb_width, &fb_height);
    glfwGetWindowSize(window, &width, &height);

    // update pixel ratio (in case our window moved to another screen of different pixel density)
    double pixel_ratio = (double)fb_width/(double)width;
    glPointSize(8.0*pixel_ratio);
    glLineWidth(1.0*pixel_ratio);

    glViewport(0, 0, fb_width, fb_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // make sure we take into account expanding the box
    // (10.0->whatever bounding sphere diameter is)
    GraphRenderer::set_perspective(60.0, (GLfloat)fb_width/(GLfloat)fb_height, 1.0, 1000.0);

    // setup modelview
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

GraphRenderer::GraphRenderer() {
    rotation = Quatd(1.0, 0.0, 0.0, 0.0);
    ctr_distance = 200.0;
    mouse_down = false;

    if (!glfwInit()) {
        fprintf(stderr, "Error intializing glfw\n");
        exit(EXIT_FAILURE);
    }

    // set to half window size
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    window = glfwCreateWindow(mode->width/2, mode->height/2, "Konig", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Print out GLFW, OpenGL version and GLEW Version:
    int iOpenGLMajor = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR);
    int iOpenGLMinor = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR);
    int iOpenGLRevision = glfwGetWindowAttrib(window, GLFW_CONTEXT_REVISION);
    fprintf(stderr, "Status: Using GLFW Version %s\n", glfwGetVersionString());
    fprintf(stderr, "Status: Using OpenGL Version: %i.%i, Revision: %i\n", iOpenGLMajor, iOpenGLMinor, iOpenGLRevision);
    fprintf(stderr, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    // warm up the timer
    last_update = glfwGetTime();

    glfwMakeContextCurrent(window);
    glewInit();

    // key, mouse, scroll, resize callbacks
    glfwSetKeyCallback(window, GraphRenderer::key_callback);
    glfwSetMouseButtonCallback(window, GraphRenderer::mouse_click_callback);
    glfwSetCursorPosCallback(window, GraphRenderer::mouse_move_callback);
    glfwSetScrollCallback(window, GraphRenderer::mouse_scroll_callback);
    glfwSetFramebufferSizeCallback(window, GraphRenderer::reshape_callback);
    glfwSwapInterval(1);

    // load texture here for now: needs refactoring
    // glGenTextures(1, &point_texture);
    // glBindTexture(GL_TEXTURE_2D, point_texture);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // point_texture = SOIL_load_OGL_texture("data/textures/particle.bmp", SOIL_LOAD_AUTO, point_texture, SOIL_FLAG_MIPMAPS);

    // glTexEnvf(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
    // glEnable(GL_POINT_SPRITE);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, GL_LOWER_LEFT);
    glClearColor(0.9f, 0.9f, 0.9f, 0.0f);
    glEnable(GL_LINE_SMOOTH);

    GraphRenderer::reshape_callback(window, mode->width/2.0, mode->height/2.0);
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

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // setperspective
    glTranslatef(0.0, 0.0, -ctr_distance);
    GLdouble mat[16];
    this->rotation.glMatrix(mat);
    glMultMatrixd(mat);

    glEnableClientState(GL_VERTEX_ARRAY);

    std::map<uint32_t, DrawableGraph *>::iterator iter;
    for (iter = graph_list->begin(); iter != graph_list->end(); iter++) {
        DrawableGraph *graph = iter->second;
        if (!graph->inited)
            continue;

        glColor3f(1.0, 0.5, 0.0);
        glBindBuffer(GL_ARRAY_BUFFER, graph->vbo_out);
        glVertexPointer(3, GL_FLOAT, sizeof(vertex_t), 0);
        glDrawArrays(GL_POINTS, 0, graph->vertex_element_count);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor3f(0.7, 0.7, 0.7);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, graph->edge_vbo);
        glDrawElements(GL_LINES, graph->edge_array.size()*4, GL_UNSIGNED_INT, 0);
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
