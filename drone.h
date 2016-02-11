//
// Created by antoinewdg on 2/11/16.
//

#ifndef HASH_CODE_DRONE_H
#define HASH_CODE_DRONE_H

#include <cmath>
#include <vector>
#include <list>

using namespace std;

struct Drone {
    int id;
    int r, c;
    int unavailable_for;

    list <vector<int>> history;

    Drone() : unavailable_for(0) { }

    void give_instruction(vector<int> cmd, int t) {
        cmd.push_back(t);
        history.push_back(cmd);
        unavailable_for = distance_between()
    }

    double distance_between(int r1, int c1, int r2, int c2) {
        return sqrt(pow(r1 - r2, 2,) + pow(c1 - c2, 2));
    }
};

#endif //HASH_CODE_DRONE_H
