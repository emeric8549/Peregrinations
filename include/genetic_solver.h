#pragma once
#include <vector>
#include "distances.h"
#include <functional>

class GeneticTSPSolver {
public :
    GeneticTSPSolver(const std::vector<Point>& points,
                     int population_size = 100,
                     int generations = 500,
                     double mutation_rate = 0.05,
                     std::function<double(const Point&, const Point&)> metric_func = euclidean_distance);
    
    std::pair<std::vector<int>, double> solve();

private:
    const std::vector<Point>& points;
    int population_size;
    int generations;
    double mutation_rate;
    std::function<double(const Point&, const Point&)> metric_func;

    std::vector<std::vector<int>> population;
    std::vector<double> fitness_scores;

    void initialize_population();
    double evaluate(const std::vector<int>& tour) const;
    std::vector<int> tournament_selection();
    std::vector<int> crossover(const std::vector<int>& parent1, const std::vector<int>& parent2);
    void mutate(std::vector<int>& individual);
};