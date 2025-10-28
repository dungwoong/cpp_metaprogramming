#include <iostream>
#include <cstdio>

struct Point {
    int x;
    int y;
    Point operator+(const Point& other); // p1 + p2
    Point operator-(); // unary -
    Point operator-(const Point& other);
    void print();
};

void Point::print() {
    printf("Point(%d, %d)\n", this->x, this->y);
}

Point Point::operator+(const Point& other) {
    return {x + other.x, y + other.y};
}

Point Point::operator-() {
    return {-x, -y};
}

Point Point::operator-(const Point& other) {
    return {x - other.x, y - other.y};
}

int main() {
    Point x{1, 2};
    Point y{2, 1};
    (x+y).print();
    (x-x).print();
    (-x).print();
}