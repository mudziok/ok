#pragma once

#include <vector>
#include <iostream>
#include "../utility/Town.h"

using namespace std;

class Chromosome {
    vector <int> genome;
    vector <int> scramble(vector <int> original);
    vector <int> mutate(vector <int> original);
public:
    Chromosome(vector<Town> towns);
    Chromosome(Chromosome x, Chromosome y);

    double length(vector<Town> towns);
    friend ostream &operator<<(ostream &os, const Chromosome &gene);
};