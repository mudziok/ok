#pragma once

#include <vector>
#include <iostream>
#include "Town.h"

using namespace std;

vector<Town> read_towns(int quantity) {
    vector<Town> towns;

    for (int i = 1; i <= quantity; i++) {
        int id, x, y;
        cin >> id >> x >> y;
        towns.push_back(Town(id, x, y));
    }

    return towns;
}