#ifndef KONIG_GRAPH_RENDERER_H
#define KONIG_GRAPH_RENDERER_H

#include "gl.h"
#include "Quaternion.h"

#include <AntTweakBar.h>

class Texture;
class DrawableGraph;

// this is essentially a particle system renderer
class GraphRenderer {
private:
    GLFWwindow *window;
    double last_update;
    uint16_t fps;

    // tweakbar
    TwBar *myBar;

    // translate & rotate
    Quatd rotation;
    bool mouse_down;
    double prev_mouse_coords[2];
    double ctr_distance;

    // framebuffers
    GLuint output_framebuffer = 0;
    GLuint screen_quad_list;
    // GLuint picking_framebuffer;

    Texture *output_texture = NULL;
    //Texture *picking_texture;

public:
    static GraphRenderer* instance () {
        static GraphRenderer *instance = new GraphRenderer();
        return instance;
    }

    static bool did_resize;
    static double pixel_ratio;
    static size_t framebuffer_size[2];

    GraphRenderer();
    ~GraphRenderer();

    bool update(DrawableGraph *graph);
    bool draw(DrawableGraph *graph);

    bool done();

    // offscreen framebuffer updater (when we resize)
    void update_framebuffer();
    void create_screen_quad();
    void prepare_offscreen();
    void disable_offscreen();
    void draw_inner(DrawableGraph *graph);

    // glu replacements
    static void set_perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
    static void mouse_move_callback(GLFWwindow *window, double x, double y);
    static void mouse_click_callback(GLFWwindow *window, int button, int action, int mods);
    static void mouse_scroll_callback(GLFWwindow *window, double x, double y);
    static void reshape_callback(GLFWwindow *window, int width, int height);
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
};

#endif
