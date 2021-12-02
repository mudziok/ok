#include "Chromosome.h"

#include <algorithm>
#include <random>

using namespace std;

vector <int> Chromosome::scramble(vector <int> original) {
    random_shuffle(original.begin(), original.end());
    return original;
}

vector <int> Chromosome::mutate(vector <int> original) {
    int z = max(0, (rand() % 4) - 2);
    for (int i = 0; i < z; i++) {
        int x = rand() % original.size();
        int y = rand() % original.size();
        swap(original[x], original[y]);
    }
    return original;
}

Chromosome::Chromosome(vector<Town> towns) {
    for (Town t: towns) {
        genome.push_back(t.id);
    }
    genome = scramble(genome);
}

Chromosome::Chromosome(Chromosome x, Chromosome y) {
    int l = x.genome.size();
    std::vector<int> new_genome(l, 0);

    int start = x.genome[0];
    int last = x.genome[0];
    for (int i = 0; i < l; i++) {
        int index = find(x.genome.begin(), x.genome.end(), last) - x.genome.begin();
        new_genome[index] = last;
        last = y.genome[index];
        if (last == start) {
            break;
        }
    }

    for (int i = 0; i < l; i++) {
        if (new_genome[i] == 0) {
            new_genome[i] = y.genome[i];
        }
    }

    new_genome = mutate(new_genome);

    genome = new_genome;
}

double Chromosome::length(vector<Town> towns) {
    double length = 0.0;
    int last = genome[genome.size() - 1];
    for (int t: genome) {
        length += towns[last - 1].dst(towns[t - 1]);
        last = t;
    }
    return length;
}

ostream &operator<<(ostream& os, const Chromosome& gene) {
    for (int g: gene.genome) {
        os << g << " ";
    }
    return os;
}