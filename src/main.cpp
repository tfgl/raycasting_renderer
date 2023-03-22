#include <unistd.h>
#include "renderer/renderer.h"

int main(int argc, char* argv[]) {
    Renderer renderer;
    Player player({5.5, 5.5}, PI/2, 75.0 * PI*2 / 360);
    Level level(10, 10);
    level.set("##########"
              "#   #    #"
              "# ###    #"
              "# # #    #"
              "#        #"
              "# #      #"
              "#        #"
              "#    #   #"
              "#        #"
              "##########");

    double xpos, ypos;
    glfwGetCursorPos(renderer._window, &xpos, &ypos);

    while (!renderer.should_close()) {
        glfwPollEvents();
        glfwGetCursorPos(renderer._window, &xpos, &ypos);

        if (glfwGetKey(renderer._window, GLFW_KEY_W) == GLFW_PRESS) {
            player.forward();
        }
        if (glfwGetKey(renderer._window, GLFW_KEY_A) == GLFW_PRESS) {
            player.left();
        }
        if (glfwGetKey(renderer._window, GLFW_KEY_S) == GLFW_PRESS) {
            player.backward();
        }
        if (glfwGetKey(renderer._window, GLFW_KEY_D) == GLFW_PRESS) {
            player.right();
        }

        if (glfwGetKey(renderer._window, GLFW_KEY_Q) == GLFW_PRESS) {
            player.turn( PI/100 );
        }
        if (glfwGetKey(renderer._window, GLFW_KEY_E) == GLFW_PRESS) {
            player.turn( -PI/100 );
        }
        player.turn (-(PI/1000) * xpos);

        renderer.render(level, player);

        glfwSetCursorPos(renderer._window, 0, 0);
        usleep(1000000 * 1/60);
    }

    return 0;
}
