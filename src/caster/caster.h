#pragma once

#include "level/level.h"

bool cast_ray(Level& level, v2f origin, radian theta, double max_dst, float& dst);
