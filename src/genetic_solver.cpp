#include "genetic_solver.h"
#include <algorithm>
#include <random>
#include <numeric>
#include <limits>
#include <cmath>
#include <functional>

static std::random_device rd;
static std::mt19937 gen(rd());

GeneticTSPSolver::GeneticTSPSolver(const std::vector<Point>& points,
                                   int population_size,
                                   int generations,
                                   double mutation_rate,
                                   std::function<double(const Point&, const Point&)> metric_func
                                 )
    : points(points),
      population_size(population_size),
      generations(generations),
      mutation_rate(mutation_rate),
      metric_func(metric_func) {}

void GeneticTSPSolver::initialize_population() {
  int n = points.size();
  std::vector<int> base(n);
  std::iota(base.begin(), base.end(), 0);

  population.clear();
  for (int i = 0; i < population_size; i++) {
    std::vector<int> tour = base;
    std::shuffle(tour.begin(), tour.end(), gen);
    population.push_back(tour);
  }
}

double GeneticTSPSolver::evaluate(const std::vector<int>& tour) const {
  double total_distance = 0.0;
  int n = tour.size();

  for (int i = 0; i < n; i++) {
    total_distance += metric_func(points[tour[i]], points[tour[(i + 1) % n]]);
  }
  return total_distance;
}

std::vector<int> GeneticTSPSolver::tournament_selection() {
  std::uniform_int_distribution<> dist (0, population_size - 1);
  int i1 = dist(gen);
  int i2 = dist(gen);
  if (fitness_scores[i1] < fitness_scores[i2]) return population[i1];
  return population[i2];
}

std::vector<int> GeneticTSPSolver::crossover(const std::vector<int>& parent1, const std::vector<int>& parent2) {
  int n = parent1.size();
  std::vector<int> child(n, -1);

  std::uniform_int_distribution<> dist(0, n - 1);
  int start = dist(gen);
  int end = dist(gen);
  if (start > end) std::swap(start, end);

  for (int i = start; i <= end; i++) {
    child[i] = parent1[i];
  }

  int idx = (end + 1) % n;
  for (int j = 0; j < n; j++) {
    int candidate = parent2[(end + 1 + j) % n];
    if (std::find(child.begin(), child.end(), candidate) == child.end()) {
      child[idx] = candidate;
      idx = (idx + 1) % n;
    }
  }
  return child;
}

void GeneticTSPSolver::mutate(std::vector<int>& individual) {
  std::uniform_real_distribution<> prob(0.0, 1.0);
  if (prob(gen) < mutation_rate) {
    int n = individual.size();
    std::uniform_int_distribution<> dist(0, n - 1);
    int i = dist(gen);
    int j = dist(gen);
    if (i > j) std::swap(i, j);
    std::reverse(individual.begin() + i, individual.begin() + j);
  }
}

std::pair<std::vector<int>, double> GeneticTSPSolver::solve() {
  initialize_population();

  std::vector<int> best_tour;
  double best_distance = std::numeric_limits<double>::infinity();

  for (int gen_idx = 0; gen_idx < generations; gen_idx++) {
    fitness_scores.clear();
    for (auto& ind : population) {
      double score = evaluate(ind);
      fitness_scores.push_back(score);
      if (score < best_distance) {
        best_distance = score;
        best_tour = ind;
      }
    }

    std::vector<std::vector<int>> new_population;
    for (int i = 0; i < population_size; i++) {
      auto parent1 = tournament_selection();
      auto parent2 = tournament_selection();
      auto child = crossover(parent1, parent2);
      mutate(child);
      new_population.push_back(child);
    }
    population = std::move(new_population);
  }

  return {best_tour, best_distance};
}