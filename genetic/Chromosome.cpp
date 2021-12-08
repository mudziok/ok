#include "Chromosome.h"

#include <algorithm>
#include <random>
#include <sstream>
#include <iterator>
#include "recombinators/CX.h"
#include "recombinators/PMX.h"
#include "../utility/collisions.h"

using namespace std;

vector <int> Chromosome::scramble(vector <int> original) {
    random_shuffle(original.begin(), original.end());
    return original;
}

vector <int> Chromosome::mutate(vector <int> original) {
    int x = rand() % original.size();
    int y = rand() % (original.size() - x) + x;
    reverse(original.begin() + min(x, y), original.begin() + max(x,y));

    return original;
}

void Chromosome::resolve(vector<Town> towns) {
    int l = towns.size();
    int start = rand() % l;
    for (int i = 0; i < l; i++) {
        int i1 = genome[((i + start) % l)] - 1;
        int i2 = genome[((i + 1 + start) % l)] - 1;
        Town t1 = towns[i1];
        Town t2 = towns[i2];
        for (int j = i + start + 2; j < i + start + l - 1; j++) {
            int j1 = genome[(j % l)] - 1;
            int j2 = genome[(j + 1) % l] - 1;
            Town t3 = towns[j1];
            Town t4 = towns[j2];
            Collision c;
            if (c.lineLine(t1.x, t1.y, t2.x, t2.y, t3.x, t3.y, t4.x, t4.y)) {
                int x = ((i + 1 + start) % l);
                int y = ((j + 1) % l);
                reverse(genome.begin() + min(x, y), genome.begin() + max(x,y));
                return;
            }
        }
    }
}

Chromosome::Chromosome(const string& list) {
    stringstream in(list);
    std::vector<int> ints;
    copy(istream_iterator<int, char>(in), istream_iterator<int, char>(), back_inserter(ints));
    genome = ints;
}

Chromosome::Chromosome(vector<Town> towns, int start) {
    Town current = towns[start];
    genome.push_back(current.id);
    towns.erase(remove(towns.begin(), towns.end(), current), towns.end());
    
    while (!towns.empty()) {
        Town closest = towns[0];
        int closest_dst = 2147483647; // = infinity

        for (Town t: towns) {
            int dst = current.dst_sq(t);
            if (dst < closest_dst) {
                closest = t;
                closest_dst = dst;
            }
        }

        genome.push_back(closest.id);
        towns.erase(remove(towns.begin(), towns.end(), closest), towns.end());
        current = closest;
    }
}

Chromosome::Chromosome(Chromosome x, Chromosome y, vector<Town> towns) {
    Recombinator* r = new CX();
    std::vector<int> new_genome = r->crossover(x.genome, y.genome);

    genome = mutate(new_genome);
    resolve(towns);
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