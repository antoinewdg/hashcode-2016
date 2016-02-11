//
// Created by antoinewdg on 2/11/16.
//

#ifndef HASH_CODE_DRONE_H
#define HASH_CODE_DRONE_H

#include <cmath>
#include <vector>
#include <list>
#include <iostream>

#include "order.h"
#include "warehouse.h"
#include "product.h"


using namespace std;


struct Drone {

    struct Command {
        int time;
        Product *p;
        int quantity;

        virtual void write_to(ostream &out);
    };

    struct LoadCommand : Command {
        Order *order;
        Warehouse *w;

        void write_to(ostream &out) {
            out << "L " << w->id << " " << p->id << " " << quantity;
        }
    };

    struct DeliverCommand : Command {
        Order *order;

        void write_to(ostream &out) {
            out << "D " << order->id << " " << p->id << " " << quantity;
        }
    };

    int id;
    int r, c;
    int unavailable_for;


    list<Command *> history;

    Drone() : unavailable_for(0) { }

    ~Drone() {
        for (Command *c : history) {
            delete c;
        }
    }

    void give_instruction(vector<LoadCommand> cmds, int t) {
        for (LoadCommand cmd : cmds) {
            history.push_back(new LoadCommand(cmd));
            unavailable_for += time_to_travel(cmd.w->r, cmd.w->c) + 1;
            r = cmd.w->r;
            c = cmd.w->r;
        }

        for (LoadCommand cmd : cmds) {
            DeliverCommand deliver;
            deliver.order = cmd.order;
            deliver.quantity = cmd.quantity;
            deliver.order = cmd.order;
            history.push_back(new DeliverCommand(deliver));

            unavailable_for += time_to_travel(deliver.order->r, deliver.order->c) + 1;
            r = deliver.order->r;
            c = deliver.order->c;
        }

        unavailable_for += time_to_travel(cmds.back().order->r, cmds.back().order->c) + 1;
        r = cmds.back().order->r;
        c = cmds.back().order->c;

        DeliverCommand deliver;
        deliver.order = cmds[0].order;
        history.push_back(DeliverCommand())

    }

    void write_history(ostream &os) {
        for (Command *cmd : history) {
            os << id << " ";
            cmd->write_to(os);
            os << endl;
        }
    }

    double time_to_travel(int r2, int c2) {
        return ceil(sqrt(pow(r - r2, 2) + pow(c - c2, 2)));
    }
};

#endif //HASH_CODE_DRONE_H
