//
// Created by antoinewdg on 2/11/16.
//

#ifndef HASH_CODE_DRONE_H
#define HASH_CODE_DRONE_H


#include "order.h"
#include "warehouse.h"
#include "product.h"

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
    bool available;

    Drone() : available(true) { }
};

#endif //HASH_CODE_DRONE_H
