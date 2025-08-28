#include <iostream>
#include <string>
#include <random>
#include "tsp_solver.h"
#include "data/data_generator.h"

int main(int argc, char* argv[]) {
    int N = 10;
    unsigned int seed = std::random_device{}();
    std::string filename = "data/synthetic_points.csv";

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--n" && i + 1 < argc) {
            N = std::stoi(argv[++i]);
        } else if (arg == "--seed" && i + 1 < argc) {
            seed = std::stoi(argv[++i]);
        } else if (arg == "--out" && i + 1 < argc) {
            filename = argv[++i];
        } else {
            std::cerr << "Unknown argument: " << arg << std::endl;
            return 1;
        }
    }

    auto points = generate_points(N, seed);
    if (!save_points_to_csv(points, filename)) {
        std::cerr << "Error: could not save points to CSV" << std::endl;
        return 1;
    }

    return 0;
}