#pragma once

#include <vector>
#include <iostream>
#include "../utility/Town.h"

using namespace std;

class Gene {
    vector <int> genome;
    vector <int> scramble(vector <int> original);
    vector <int> mutate(vector <int> original);
public:
    Gene(vector<Town> towns);
    Gene(Gene x, Gene y);

    double length(vector<Town> towns);
    friend ostream &operator<<(ostream &os, const Gene &gene);
};