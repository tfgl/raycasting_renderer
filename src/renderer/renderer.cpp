#include "renderer.h"

#include "logger/logger.h"
#include "caster/caster.h"

void render_rect(double x, double y, double w, double h) {
    glBegin(GL_QUADS);
    glVertex2f(x - w/2 , y - h/2 );
    glVertex2f(x + w/2 , y - h/2 );
    glVertex2f(x + w/2 , y + h/2 );
    glVertex2f(x - w/2 , y + h/2 );
    glEnd();
}

void render_line(double x1, double y1, double x2, double y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

Renderer::Renderer() {
    _width = 1920;
    _height = 1080;

    if(!glfwInit())
        Logger::write("[ERR] [Renderer::Renderer]: glfwInit failed");

    _window = glfwCreateWindow(_width, _height, "raycaster", glfwGetPrimaryMonitor(), NULL);
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    if(!_window)
        glfwTerminate();

    glfwMakeContextCurrent(_window);
    glClearColor(0, 0, 0, 0);
}

void Renderer::render_level3d(Player& player, Level& level) {
    int n_ray = 1000;
    radian ray_direction = player._rotation - player._fov / 2.0;
    radian ray_spacing = player._fov / n_ray;
    double max_dst = level._width + level._height;

    glColor3f(0.3, 0.6, 0.9);
    render_rect(-1, 1, 4, 2);
    glColor3f(0.1, 0.7, 0.4);
    render_rect(-1, -1, 4, 2);

    for (int ray = 0; ray < n_ray + 1; ray++) {
        float dst = 0;
        if( cast_ray(level, player._coord, ray_direction, max_dst, dst) ) {

            float color_k = dst < 2 ? 2 : dst;
            glColor3f(0.8/color_k, 0.6/color_k, 0.5/color_k);

            float x = -2*(float(ray) / n_ray)+1,
                  y = 0,
                  w = 2.0/n_ray,
                  h = 2.0/(dst*std::cos(player._rotation - ray_direction));

            render_rect(x, y, w, h);
        }

        ray_direction += ray_spacing;
    }
}

void Renderer::render(Level& level, Player& player) {
    glClear(GL_COLOR_BUFFER_BIT);
    render_level3d(player, level);
    glfwSwapBuffers(_window);
}

void Renderer::render_rays(Player& player, Level& level) {
    int n_ray = 100;
    radian ray_direction = player._rotation - player._fov / 2.0;
    radian ray_spacing = player._fov / n_ray;
    double max_dst = level._width + level._height;
    float px = player._coord.x/level._width - 0.5,
          py = player._coord.y/level._height - 0.5;

    for (int ray = 0; ray < n_ray; ray++) {
        float dst = 0;
        if( cast_ray(level, player._coord, ray_direction, max_dst, dst) ) {
            glColor3f(0.0, 1.0, 0.0);

            render_line(px, py,
                        px + std::cos(ray_direction)*dst/max_dst,
                        py + std::sin(ray_direction)*dst/max_dst);
        }

        ray_direction += ray_spacing;
    }
}

bool Renderer::should_close() {
    return glfwWindowShouldClose(_window);
}
