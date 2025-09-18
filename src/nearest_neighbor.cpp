#include "nearest_neighbor.h"
#include <limits>
#include <numeric>
#include <algorithm>

std::pair<std::vector<int>, double> nearest_neighbor_tour(const std::vector<Point>& points) {
    int N = points.size();
    if (N == 0) {
        return {{}, 0.0};
    }

    std::vector<int> tour;
    double tour_length = 0.0;
    std::vector<bool> visited(N, false);

    int current_idx = 0;
    tour.push_back(current_idx);
    visited[current_idx] = true;

    for (int i = 0; i < N - 1; ++i) {
        double min_dist = std::numeric_limits<double>::max();
        int next_idx = -1;

        for (int j = 0; j < N; ++j) {
            if (!visited[j]) {
                double dist = euclidean_distance(points[current_idx], points[j]);
                if (dist < min_dist) {
                    min_dist = dist;
                    next_idx = j;
                }
            }
        }
        
        if (next_idx != -1) {
            tour.push_back(next_idx);
            tour_length += min_dist;
            visited[next_idx] = true;
            current_idx = next_idx;
        } else {
            break;
        }
    }

    if (N > 1) {
        tour_length += euclidean_distance(points[current_idx], points[tour[0]]);
        tour.push_back(tour[0]);
    }
    return {tour, tour_length};
}