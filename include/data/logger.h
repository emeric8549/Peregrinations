#pragma once
#include <string>
#include <vector>
#include "distances.h"

void log_experiment(
    const std::string& filename,
    const std::string& algorithm,
    int n_points,
    double tour_length,
    long long exec_time_microseconds,
    const std::vector<int>& tour,
    const std::vector<Point>& points
);