#include <GLFW/glfw3.h>
#include <unistd.h>
#include "renderer/renderer.h"

bool collide(v2f& _coord, Level& lvl) {
    return (_coord.x > 0 && _coord.y > 0 &&
            _coord.x < lvl._width && _coord.y < lvl._height) &&
           (lvl.get(_coord.x, _coord.y) == '#');
}

int main(int argc, char* argv[]) {
    Renderer renderer;
    //                           75.0d = 1.309
    Player player({2.5, 17}, -PI/2, 1.309);
    Level level(22, 22, // sligthly bigger dimension than the level itself avoid artifacts when outside the boundaries
              " #################### "
              " #   #              # "
              " # ###              # "
              " # # #              # "
              " #                  # "
              " # #                # "
              " #                  # "
              " #    #             # "
              " #                  # "
              " #                  # "
              " ################## # "
              " #  #     #   #     # "
              " #  # # #   # #  #  # "
              " #  # # ##### #  #  # "
              " #  # #  #       #  # "
              " #  # #### #######  # "
              " #  #      #        # "
              " #  # #### #  ####### "
              " #         #        # "
              " ################## # ");

    double xpos, ypos;
    glfwGetCursorPos(renderer._window, &xpos, &ypos);

    while (!renderer.should_close()) {
        glfwPollEvents();
        glfwGetCursorPos(renderer._window, &xpos, &ypos);

        if (glfwGetKey(renderer._window, GLFW_KEY_W) == GLFW_PRESS) {
            player.forward();
            if(collide(player._coord, level))
                player.backward();
        }
        if (glfwGetKey(renderer._window, GLFW_KEY_A) == GLFW_PRESS) {
            player.left();
            if(collide(player._coord, level))
                player.right();
        }
        if (glfwGetKey(renderer._window, GLFW_KEY_S) == GLFW_PRESS) {
            player.backward();
            if(collide(player._coord, level))
                player.forward();
        }
        if (glfwGetKey(renderer._window, GLFW_KEY_D) == GLFW_PRESS) {
            player.right();
            if(collide(player._coord, level))
                player.left();
        }

        if (glfwGetKey(renderer._window, GLFW_KEY_Q) == GLFW_PRESS) {
            player.turn( PI/100 );
        }
        if (glfwGetKey(renderer._window, GLFW_KEY_E) == GLFW_PRESS) {
            player.turn( -PI/100 );
        }

        if (glfwGetKey(renderer._window, GLFW_KEY_F) == GLFW_PRESS) {
            std::cout << "Player Data: " << "\n"
                      << "  position [x, y]: " << "(" << player._coord.x << "," << player._coord.y << ")" << "\n"
                      << "  velocity [x, y]: " << "(" << player._velocity.x << "," << player._velocity.y << ")" << "\n"
                      << "            speed: " << "(" << player._speed << "\n"
                      << "              fov: " << "(" << player._fov << "\n"
                      << "         rotation: " << "(" << player._rotation << "\n"
                      << "            pitch: " << "(" << player._pitch << "\n"
                      << std::endl;
            usleep(50000);
        }

        player.turn(-(PI/1000) * xpos);

        player._pitch += PI * ypos/1000;
        if (player._pitch > PI) {
            player._pitch = PI;
        } else if (player._pitch < -PI) {
            player._pitch = -PI;
        }

        renderer.render(level, player);

        glfwSetCursorPos(renderer._window, 0, 0);
        usleep(1000000 * 1/60);
    }

    return 0;
}
