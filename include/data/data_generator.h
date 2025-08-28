#pragma once
#include <string>
#include <vector>
#include "tsp_solver.h"

std::vector<Point> generate_points(int N, unsigned int seed);

bool save_points_to_csv(const std::vector<Point>& points, const std::string& filename);