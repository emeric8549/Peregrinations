#pragma once
#include <vector>
#include "distances.h"
#include <functional>

std::pair<std::vector<int>, double> nearest_neighbor_tour(const std::vector<Point>& points, std::function<double(const Point&, const Point&)> metric_func);