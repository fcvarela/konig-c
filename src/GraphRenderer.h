#ifndef KONIG_GRAPH_RENDERER_H
#define KONIG_GRAPH_RENDERER_H

#include <map>

#include "gl.h"

class Texture;
class DrawableGraph;

// this is essentially a particle system renderer
class GraphRenderer {
private:
    GLFWwindow *window;
    double last_update;
    double angle;

    GLuint point_texture;

    GLuint framebuffer;
    Texture *output_texture;

public:
    GraphRenderer();
    ~GraphRenderer();

    bool update(std::map<uint32_t, DrawableGraph*> *graph_list);
    bool draw(std::map<uint32_t, DrawableGraph*> *graph_list);

    bool done();

    // glu replacements
    static void set_perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);

    static void reshape_callback(GLFWwindow *window, int width, int height);
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
};

#endif
