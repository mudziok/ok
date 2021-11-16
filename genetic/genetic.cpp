#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include "../utility/Town.h"
#include "../utility/utility.h"
#include "Gene.h"

using namespace std;
int MAX_INT = 2147483647;

vector <Town> towns;

vector <pair<double, Gene>> evaluate(vector<Gene> genes) {
    vector <pair<double, Gene>> evaluated;
    for (Gene g: genes) {
        evaluated.push_back({g.length(towns), g});
    }
    return evaluated;
}

vector <pair<double, Gene>> fitnesses(vector <pair<double, Gene>> genes, double best_length) {
    for (auto &g: genes) {
        g.first = pow(best_length / g.first, 5.0);
    }
    return genes;
}

Gene randomGene(vector <pair<double, Gene>> genes) {
    double x = rand() / (RAND_MAX + 1.0);
    double sum = 0.0;
    for (auto p: genes) {
        Gene g = p.second;
        sum += p.first;
        if (sum > x) { return g; }
    }

    return genes[genes.size() - 1].second;
}


int main(int argc, char** argv) {
    srand(time(NULL));

    int n; cin >> n;
    towns = read_towns(n);
    vector <Gene> genes;
    pair<double, Gene> best {1000000.0, Gene(towns)};

    for (int i = 0; i < 50; i++) {
        genes.push_back(Gene(towns));
    }

    for (int i = 0; i < 10000; i++) {
        vector <pair<double, Gene>> ev = evaluate(genes);

        best = {1000000.0, Gene(towns)};
        for (auto p: ev) {
            if (p.first < best.first) {
                best = p;
            }
        }

        vector <pair<double, Gene>> fit = fitnesses(ev, best.first);


        double sum = 0.0;
        for (auto p: fit) {
            sum += p.first;
        }

        for (auto &g: fit) {
            g.first = g.first / sum;
        }

        //cout << best.first << endl;
        // for (auto g: ev) {
        //      cout << g.first << " - " << g.second << endl;
        // }

        vector <Gene> new_genes;
        for (Gene g: genes) {
            new_genes.push_back(Gene(randomGene(fit), randomGene(fit)));
        }
        genes = new_genes;
    }
    //cout << best.first << endl;
    cout << best.second << endl;

    return 0;
}