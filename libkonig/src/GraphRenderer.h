#ifndef KONIG_GRAPH_RENDERER_H
#define KONIG_GRAPH_RENDERER_H

#include <map>

#include "gl.h"
#include "Quaternion.h"

class Texture;
class DrawableGraph;

// this is essentially a particle system renderer
class GraphRenderer {
private:
    GLFWwindow *window;
    double last_update;

    // translate & rotate
    Quatd rotation;
    bool mouse_down;
    double prev_mouse_coords[2];
    double ctr_distance;

    GLuint point_texture;

    GLuint output_framebuffer;
    GLuint picking_framebuffer;

    Texture *output_texture;
    Texture *picking_texture;

public:
    static GraphRenderer* instance () {
        static GraphRenderer *instance = new GraphRenderer();
        return instance;
    }

    GraphRenderer();
    ~GraphRenderer();

    bool update(std::map<uint32_t, DrawableGraph*> *graph_list);
    bool draw(std::map<uint32_t, DrawableGraph*> *graph_list);

    bool done();

    // glu replacements
    static void set_perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
    static void mouse_move_callback(GLFWwindow *window, double x, double y);
    static void mouse_click_callback(GLFWwindow *window, int button, int action, int mods);
    static void mouse_scroll_callback(GLFWwindow *window, double x, double y);
    static void reshape_callback(GLFWwindow *window, int width, int height);
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
};

#endif
