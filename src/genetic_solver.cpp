#include "genetic_solver.h"
#include <algorithm>
#include <random>
#include <numeric>
#include <limits>
#include <cmath>

static std::random_device rd;
static std::mt19937 gen(rd());

GeneticTSPSolver::GeneticTSPSolver(const std::vector<Point>& points,
                                   int population_size,
                                   int generations,
                                   double mutation_rate)
    : points(points),
      population_size(population_size),
      generations(generations),
      mutation_rate(mutation_rate) {}