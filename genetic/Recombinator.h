#pragma once

#include "Chromosome.h"

using namespace std;

class Recombinator {
public:
    virtual std::vector<int>  crossover(std::vector<int>  x, std::vector<int>  y) = 0;
};