//
// Created by antoinewdg on 2/11/16.
//

#ifndef HASH_CODE_DRONE_H
#define HASH_CODE_DRONE_H

#include <cmath>
#include <vector>
#include <list>

#include "order.h"
#include "warehouse.h"
#include "product.h"


using namespace std;


struct Drone {

    struct Command {
        int time;
        Product *p;
        int quantity;
    };

    struct LoadCommand : Command {
        Order *order;
        Warehouse *w;
    };

    struct DeliverCommand : Command {
        Order *order;
    };

    int id;
    int r, c;
    int unavailable_for;

    list <LoadCommand> history;

    Drone() : unavailable_for(0) { }

    void give_instruction(vector<LoadCommand> cmds, int t) {
        for (LoadCommand cmd : cmds) {
            history.push_back(cmd);
            unavailable_for += time_to_travel(cmd.w->r, cmd.w->c) + 1;
            r = cmd.w->r;
            c = cmd.w->r;
        }

        unavailable_for += time_to_travel(cmds.back().order->r, cmds.back().order->c) + 1;
        r = cmds.back().order->r;
        c = cmds.back().order->c;

    }

    double time_to_travel(int r2, int c2) {
        return ceil(sqrt(pow(r - r2, 2) + pow(c - c2, 2)));
    }
};

#endif //HASH_CODE_DRONE_H
