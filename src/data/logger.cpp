#include "data/logger.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

void log_experiment(
    const std::string& filename,
    const std::string& algorithm,
    int n_points,
    unsigned int seed,
    double tour_length,
    long long exec_time_microseconds,
    const std::vector<int>& tour,
    const std::vector<Point>& points
) {
    bool file_exists = std::filesystem::exists(filename);

    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: could not open log file " << filename << std::endl;
        return ;
    }

    if (!file_exists) {
        file << "algorithm,n_points,seed,tour_length,execution_time_microseconds,tour_order,points\n";
    }

    std::ostringstream tour_stream;
    for (size_t i = 0; i < tour.size(); ++i) {
        tour_stream << tour[i];
        if (i + 1 < tour.size()) tour_stream << "-";
    }

    std::ostringstream points_stream;
    for (size_t i = 0; i < points.size(); ++i) {
        points_stream << "(" << points[i].x << "," << points[i].y << ")";
        if (i + 1 < points.size()) points_stream << ";";
    }

    file << algorithm << ","
         << n_points << ","
         << seed << ","
         << tour_length << ","
         << exec_time_microseconds << ","
         << "\"" << tour_stream.str() << "\","
         << "\"" << points_stream.str() << "\"\n";

    file.close();
}