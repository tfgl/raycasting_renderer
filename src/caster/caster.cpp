#include "caster.h"

bool cast_ray(Level& level, v2f origin, radian theta, double max_dst, float& dst) {
    v2f ray_vec = {(float)std::cos(theta), (float)std::sin(theta)};

    v2f ray_step = {std::sqrt(1 + (ray_vec.y/ray_vec.x)*(ray_vec.y/ray_vec.x)),
                    std::sqrt(1 + (ray_vec.x/ray_vec.y)*(ray_vec.x/ray_vec.y))};
    v2i snaped = origin.cast<int>();
    v2f ray_lenght;
    v2i step;

    bool wall_hit = false;
    dst = 0;

    if (ray_vec.x < 0) {
        step.x = -1;
        ray_lenght.x = (origin.x - float(snaped.x)) * ray_step.x;
    } else {
        step.x = 1;
        ray_lenght.x = (float(snaped.x + 1) - origin.x) * ray_step.x;
    }
    if (ray_vec.y < 0) {
        step.y = -1;
        ray_lenght.y = (origin.y - float(snaped.y)) * ray_step.y;
    } else {
        step.y = 1;
        ray_lenght.y = (float(snaped.y + 1) - origin.y) * ray_step.y;
    }

    while(!wall_hit && dst < max_dst) {
        if( ray_lenght.x < ray_lenght.y ) {
            snaped.x     += step.x;
            dst           = ray_lenght.x;
            ray_lenght.x += ray_step.x;
        } else {
            snaped.y     += step.y;
            dst           = ray_lenght.y;
            ray_lenght.y += ray_step.y;
        }

        if( snaped.x >= 0 && snaped.x < level._width && snaped.y >= 0 && snaped.y < level._height )
            wall_hit = level.get(snaped.x, snaped.y) == '#';
    }

    return wall_hit;
}
