#include "Chromosome.h"

#include <algorithm>
#include <random>
#include "recombinators/CX.h"
#include "recombinators/PMX.h"

using namespace std;

vector <int> Chromosome::scramble(vector <int> original) {
    random_shuffle(original.begin(), original.end());
    return original;
}

vector <int> Chromosome::mutate(vector <int> original) {
    int l = original.size() /2;
    int z = max(0, (rand() % l) - (l / 2));
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
    Recombinator* r = new CX();
    std::vector<int> new_genome = r->crossover(x.genome, y.genome);

    genome = mutate(new_genome);
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