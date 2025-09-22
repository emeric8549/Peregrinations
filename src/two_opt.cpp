#include "two_opt.h"
#include <numeric>
#include <algorithm>


static double compute_tour_length(const std::vector<int>& tour, const std::vector<Point>& points, const std::function<double(const Point&, const Point&)>& metric_func) {
    double length = 0.0;
    int N = tour.size();
    for (int i = 0; i < N; ++i) {
        length += metric_func(points[tour[i]], points[tour[(i + 1) % N]]);
    }
    return length;
}

std::pair<std::vector<int>, double> two_opt_tour_first_improvement(const std::vector<Point>& points, std::function<double(const Point&, const Point&)> metric_func) {
    int N = points.size();
    if (N < 2) {
        return {{}, 0.0};
    }
    if (N == 2) {
        return {{0, 1, 0}, 2 * metric_func(points[0], points[1])};
    }

    std::vector<int> tour(N + 1);
    std::iota(tour.begin(), tour.end() - 1, 0);

    std::vector<std::vector<double>> dist_matrix(N, std::vector<double>(N, 0.0));
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            double dist = metric_func(points[i], points[j]);
            dist_matrix[i][j] = dist;
            dist_matrix[j][i] = dist;
        }
    }

    double current_length = compute_tour_length(tour, points, metric_func);
    bool improved = true;
    const double epsilon = 1e-12;
    while (improved) {
        improved = false;
        for (int i = 0; i < N - 1 && !improved; ++i) {
            for (int k = i + 2; k < N + 1; ++k) {
                int A = tour[i];
                int B = tour[(i + 1) % N];
                int C = tour[k];
                int D = tour[(k + 1) % N];

                double delta = dist_matrix[A][C] + dist_matrix[B][D] - dist_matrix[A][B] - dist_matrix[C][D];

                if (delta < -epsilon) {
                    std::reverse(tour.begin() + (i + 1), tour.begin() + (k + 1));
                    current_length += delta;
                    improved = true;
                    break;
                }
            }
        }
    }

    return {tour, current_length};
}