#include "data/data_generator.h"
#include <random>
#include <fstream>
#include <iostream>

std::vector<Point> generate_points(int N, unsigned int seed) {
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dis(0.0, 100.0);

    std::vector<Point> points;
    points.reserve(N);
    for (int i = 0; i < N; i++) {
        points.push_back(Point{dis(gen), dis(gen)});
    }
    return points;
}

bool save_points_to_csv(const std::vector<Point>& points, const std::string& filename) {
     std::ofstream file("../" + filename);
    if (!file.is_open()) {
        std::cerr << "Error: cannot open file " << filename << std::endl;
        return 1;
    }

    file << "x,y\n";
    for (const auto& p : points) {
        file << p.x << "," << p.y << "\n";
    }
    file.close();

    std::cout << "Data successfully generated in " << filename << std::endl;

    return true;
}