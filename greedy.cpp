#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
int INF = 2147483647;

class Town {
    public:
    int id, x, y;

    Town() {}
    Town(int _id, int _x, int _y) : id(_id), x(_x), y(_y) {}

    int dst_sq(Town t) {
        int dx = x - t.x;
        int dy = y - t.y;
        return dx*dx + dy*dy;
    }

    inline bool operator==(const Town& o) { return id == o.id; }
};

vector<Town> towns;

int main(int argc, char** argv) {
    int n; cin >> n;
    vector <int> path;
    
    for (int i = 1; i <= n; i++) {
        int id, x, y;
        cin >> id >> x >> y;
        towns.push_back(Town(id, x, y));
    }
    
    Town cur = towns[0];
    path.push_back(cur.id);
    towns.erase(remove(towns.begin(), towns.end(), cur), towns.end());
    
    while (!towns.empty()) {
        Town closest;
        int min_dst = INF;

        for (Town t: towns) {
            int dst = cur.dst_sq(t);
            if (dst < min_dst) {
                closest = t;
                min_dst = dst;
            }
        }

        path.push_back(closest.id);
        towns.erase(remove(towns.begin(), towns.end(), closest), towns.end());
        cur = closest;
    }

    for (int p: path) {
        cout << p << " ";
    } cout << endl;
    
    return 0;
}