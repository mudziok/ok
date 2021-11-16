#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include "../utility/Town.h"
#include "utility.h"

using namespace std;
int MAX_INT = 2147483647;

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