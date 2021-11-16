#pragma once

#include <math.h>
#include <iostream>

using namespace std;

class Town {
    public:
    int id, x, y;

    Town(int id, int x, int y) : id(id), x(x), y(y) {}

    int dst_sq(Town t) {
        int dx = x - t.x;
        int dy = y - t.y;
        return dx*dx + dy*dy;
    }

    double dst(Town t) {
        int x = dst_sq(t);
        return sqrt(x);
    }

    inline bool operator==(const Town& o) { return id == o.id; }
};