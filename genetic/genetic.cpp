#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include "../utility/Town.h"
#include "../utility/utility.h"
#include "Chromosome.h"

using namespace std;

vector <Town> towns;

vector <pair<double, Chromosome>> evaluate(vector<Chromosome> chromosomes) {
    vector <pair<double, Chromosome>> evaluated;
    for (Chromosome c: chromosomes) {
        evaluated.push_back({c.length(towns), c});
    }
    std::sort(evaluated.begin(), evaluated.end(), [](const auto& a, const auto& b) { return a.first < b.first; });
    return evaluated;
}

// rates solutions from 1 to 0 in a ?logarythmic? fashion
vector <pair<double, Chromosome>> calcFitness(vector <pair<double, Chromosome>> chromosomes, double best_length) {
    for (auto &c: chromosomes) {
        c.first = pow(best_length / c.first, 10.0);
    }
    return chromosomes;
}

Chromosome randomGene(vector <pair<double, Chromosome>> odds) {
    double x = rand() / (RAND_MAX + 1.0);
    double sum = 0.0;
    for (auto p: odds) {
        Chromosome c = p.second;
        sum += p.first;
        if (sum > x) { return c; }
    }

    return odds[odds.size() - 1].second;
}

vector <pair<double, Chromosome>> normalize(vector <pair<double, Chromosome>> fitnesses) {
    double sum = accumulate(fitnesses.begin(), fitnesses.end(), 0.0, [](double acc, auto p) { return acc + p.first; });
    
    for (auto &c: fitnesses) {
        c.first = c.first / sum;
    }

    return fitnesses;
}

int main(int argc, char** argv) {
    srand(time(NULL));

    int n; cin >> n;
    int population = 10;
    towns = read_towns(n);
    vector <Chromosome> chromosomes;

    for (int i = 0; i < population * 2; i++) {
        chromosomes.push_back(Chromosome(towns));
    }

    for (int i = 0; i < 50000; i++) {
        vector <pair<double, Chromosome>> lengths = evaluate(chromosomes);

        pair<double, Chromosome> best = lengths[0];
        // for (auto p: lengths) {
        //     cout << p.first << " " << p.second << endl;
        // }
        for (int i = 0; i < population; i++) { lengths.pop_back(); }
        //cout << best.first << endl;

        vector <pair<double, Chromosome>> fitnesses = calcFitness(lengths, best.first);
        vector <pair<double, Chromosome>> odds = normalize(fitnesses);

        vector <Chromosome> new_chromosomes;
        for (pair<double, Chromosome> p: odds) {
            new_chromosomes.push_back(p.second);
            new_chromosomes.push_back(Chromosome(randomGene(odds), randomGene(odds)));
        }
        chromosomes = new_chromosomes;
    }
    
    vector <pair<double, Chromosome>> lengths = evaluate(chromosomes);
    cout << lengths[0].second << endl;

    return 0;
}