#pragma once

#include <algorithm>
#include "../recombinator.h"

using namespace std;

class PMX: public Recombinator {
    int resolve(std::vector<int> g, std::vector<int> x, std::vector<int> y, int res) {
        while (find(g.begin(), g.end(), res) != g.end())
        {
            int index = find(x.begin(), x.end(), res) - x.begin();
            res = y[index];
        }

        return res;
    }
public:
    std::vector<int> crossover(std::vector<int> x, std::vector<int> y) {
        int l = x.size();
        std::vector<int> new_genome(l, -1);

        int start = rand() % l;
        int end = (rand() % (l - start)) + start;
        for (int i = start; i <= end; i++) {
            new_genome[i] = y[i];
        }

        for (int i = 0; i < start; i++) {
            if (find(new_genome.begin(), new_genome.end(), x[i]) == new_genome.end()) {
                new_genome[i] = x[i];
            }
        }
        for (int i = end + 1; i < l; i++) {
            if (find(new_genome.begin(), new_genome.end(), x[i]) == new_genome.end()) {
                new_genome[i] = x[i];
            }
        }

        for (int i = 0; i < l; i++) {
            if (new_genome[i] == -1) {
                new_genome[i] = resolve(new_genome, x, y, x[i]);
            }
        }

        return new_genome;
    };
};