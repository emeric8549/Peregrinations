#pragma once

struct Point {
    int x;
    int y;
};

double euclidean_distance(const Point& a, const Point& b);
double manhattan_distance(const Point& a, const Point& b);