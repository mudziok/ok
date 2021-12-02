#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include "../utility/Town.h"
#include "../utility/utility.h"
#include "Gene.h"

using namespace std;

vector <Town> towns;

pair<double, Gene> bestGene(vector <pair<double, Gene>> lengths) {
    return *min_element(lengths.begin(), lengths.end(), [](const auto& a, const auto& b) { return a.first < b.first; });
}

vector <pair<double, Gene>> evaluate(vector<Gene> genes) {
    vector <pair<double, Gene>> evaluated;
    for (Gene g: genes) {
        evaluated.push_back({g.length(towns), g});
    }
    return evaluated;
}

// rates solutions from 1 to 0 in a ?logarythmic? fashion
vector <pair<double, Gene>> calcFitness(vector <pair<double, Gene>> genes, double best_length) {
    for (auto &g: genes) {
        g.first = pow(best_length / g.first, 6.0);
    }
    return genes;
}

Gene randomGene(vector <pair<double, Gene>> odds) {
    double x = rand() / (RAND_MAX + 1.0);
    double sum = 0.0;
    for (auto p: odds) {
        Gene g = p.second;
        sum += p.first;
        if (sum > x) { return g; }
    }

    return odds[odds.size() - 1].second;
}

vector <pair<double, Gene>> normalize(vector <pair<double, Gene>> fitnesses) {
    double sum = accumulate(fitnesses.begin(), fitnesses.end(), 0.0, [](double acc, auto p) { return acc + p.first; });
    
    for (auto &g: fitnesses) {
        g.first = g.first / sum;
    }

    return fitnesses;
}

int main(int argc, char** argv) {
    srand(time(NULL));

    int n; cin >> n;
    towns = read_towns(n);
    vector <Gene> genes;

    for (int i = 0; i < 40; i++) {
        genes.push_back(Gene(towns));
    }

    for (int i = 0; i < 50000; i++) {
        vector <pair<double, Gene>> lengths = evaluate(genes);

        pair<double, Gene> best = bestGene(lengths);

        vector <pair<double, Gene>> fitnesses = calcFitness(lengths, best.first);

        vector <pair<double, Gene>> odds = normalize(fitnesses);

        vector <Gene> new_genes;
        for (Gene g: genes) {
            new_genes.push_back(Gene(randomGene(odds), randomGene(odds)));
        }
        genes = new_genes;
    }
    
    pair<double, Gene> best = bestGene(evaluate(genes));
    cout << best.second << endl;

    return 0;
}