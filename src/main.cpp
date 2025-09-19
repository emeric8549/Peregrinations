#include <iostream>
#include <string>
#include <random>
#include "distances.h"
#include "data/data_generator.h"
#include "nearest_neighbor.h"

int main(int argc, char* argv[]) {
    int N = 10;
    unsigned int seed = std::random_device{}();
    std::string filename = "../data/synthetic_points.csv";
    std::function<double(const Point&, const Point&)> metric_func = euclidean_distance;
    bool calculate_simple_tour = false;
    bool calculate_nn_tour = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--n" && i + 1 < argc) {
            N = std::stoi(argv[++i]);
        } else if (arg == "--seed" && i + 1 < argc) {
            seed = std::stoi(argv[++i]);
        } else if (arg == "--out" && i + 1 < argc) {
            filename = argv[++i];
        } else if (arg == "--distance-metric" && i + 1 < argc) {
            std::string metric_str = argv[++i];
            if (metric_str == "euclidean") {
                metric_func = euclidean_distance;
            } else if (metric_str == "manhattan") {
                metric_func = manhattan_distance;
            } else {
                std::cerr << "Warning: Unknown distance metric: " << metric_str << ". Using euclidean by default." << std::endl;
                metric_func = euclidean_distance;
            }
        } else if (arg == "--calculate-simple-tour") {
            calculate_simple_tour = true;
        } else if (arg == "--calculate-nn-tour") {
            calculate_nn_tour = true;
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

    if (calculate_simple_tour) {
        if (N < 2) {
            std::cout << "Not enough points to calculate a tour." << std::endl;
        } else {
            double tour_length = 0.0;
            for (int i = 0; i < N - 1; ++i) {
                tour_length += metric_func(points[i], points[i + 1]);
            }
            tour_length += metric_func(points[N - 1], points[0]); // Return to start
            std::cout << "Length of simple tour: " << tour_length << std::endl;
        }
    }

    if (calculate_nn_tour) {
        if (N < 2) {
            std::cout << "Not enough points to calculate a tour." << std::endl;
        } else {
            auto [tour, tour_length] = nearest_neighbor_tour(points, metric_func);
            std::cout << "Length of nearest neighbor tour: " << tour_length << std::endl;
        }
    }

    return 0;
}