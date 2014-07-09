#ifndef KONIG_GRAPH_RENDERER_H
#define KONIG_GRAPH_RENDERER_H

#include <map>

#include <GLFW/glfw3.h>

#include "DrawableGraph.h"

namespace konig {

// this is essentially a particle system renderer
class GraphRenderer {
private:
    GLFWwindow *window;
    double last_update, angle;
    GLuint point_texture;

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

}

#endif
