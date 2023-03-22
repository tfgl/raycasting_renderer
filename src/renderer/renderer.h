#pragma once

#include <GLFW/glfw3.h>
#include "level/level.h"
#include "player/player.h"

class Renderer {
    void render_level3d(Player& player_pos, Level& level);
    void render_rays(Player& player_pos, Level& level);

public:
    GLFWwindow* _window;
    int _width, _height;

    Renderer();
    void render(Level&, Player& player);
    bool should_close();
};
