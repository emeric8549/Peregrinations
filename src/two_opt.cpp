#include "two_opt.h"

std::pair<std::vector<int>, double> two_opt_tour(const std::vector<Point>& points, const std::function<double(const Point&)> metric_func) {
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
        for (int j = i+1; j < N; ++j) {
            double dist = metric_func(points[i], points[j]);
            dist_matrix[i][j] = dist;
            dist_matrix[j][i] = dist;
        }
    }
}