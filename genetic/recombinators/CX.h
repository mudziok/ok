#pragma once

#include <algorithm>
#include "../recombinator.h"

using namespace std;

class CX: public Recombinator {
public:
    std::vector<int> crossover(std::vector<int> x, std::vector<int> y) {
        int l = x.size();
        std::vector<int> new_genome(l, 0);

        int start = x[0];
        int last = x[0];
        for (int i = 0; i < l; i++) {
            int index = find(x.begin(), x.end(), last) - x.begin();
            new_genome[index] = last;
            last = y[index];
            if (last == start) {
                break;
            }
        }

        for (int i = 0; i < l; i++) {
            if (new_genome[i] == 0) {
                new_genome[i] = y[i];
            }
        }

        return new_genome;
    };
};