#pragma once
#include <vector>
#include "distances.h"

std::pair<std::vector<int>, double> nearest_neighbor_tour(const std::vector<Point>& points);