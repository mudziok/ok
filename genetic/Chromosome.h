#pragma once

#include <vector>
#include <iostream>
#include <string>
#include "../utility/Town.h"

using namespace std;

class Chromosome {
    vector <int> genome;
    vector <int> scramble(vector <int> original);
    vector <int> mutate(vector <int> original);
    void resolve(vector<Town> towns);
public:
    Chromosome(const string& list);
    Chromosome(vector<Town> towns, int start);
    Chromosome(Chromosome x, Chromosome y, vector<Town> towns);

    double length(vector<Town> towns);
    friend ostream &operator<<(ostream &os, const Chromosome &gene);
};