#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
int MAX_INT = 2147483647;

class Town {
    public:
    int id, x, y;

    Town(int id, int x, int y) : id(id), x(x), y(y) {}

    int dst_sq(Town t) {
        int dx = x - t.x;
        int dy = y - t.y;
        return dx*dx + dy*dy;
    }

    inline bool operator==(const Town& o) { return id == o.id; }
};

vector<Town> read_towns(int quantity) {
    vector<Town> towns;

    for (int i = 1; i <= quantity; i++) {
        int id, x, y;
        cin >> id >> x >> y;
        towns.push_back(Town(id, x, y));
    }

    return towns;
}

int main(int argc, char** argv) {
    int n; cin >> n;
    vector <Town> towns = read_towns(n);
    vector <int> hamilton;
    
    Town current = towns[0];
    hamilton.push_back(current.id);
    towns.erase(remove(towns.begin(), towns.end(), current), towns.end());
    
    while (!towns.empty()) {
        Town closest = towns[0];
        int closest_dst = MAX_INT; // = infinity

        for (Town t: towns) {
            int dst = current.dst_sq(t);
            if (dst < closest_dst) {
                closest = t;
                closest_dst = dst;
            }
        }

        hamilton.push_back(closest.id);
        towns.erase(remove(towns.begin(), towns.end(), closest), towns.end());
        current = closest;
    }

    for (int p: hamilton) {
        cout << p << " ";
    } cout << endl;
    
    return 0;
}