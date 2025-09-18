#pragma once

struct Point {
    double x;
    double y;
};

double euclidean_distance(const Point& a, const Point& b);
double manhattan_distance(const Point& a, const Point& b);