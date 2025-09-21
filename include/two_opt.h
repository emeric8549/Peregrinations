#pragma once
#include <vector>
#include <functional>
#include "distances.h"

std::pair<std::vector<int>, double> two_opt_tour(const std::vector<Point>& points, std::function<double(const Point&, const Point&)> metric_func);