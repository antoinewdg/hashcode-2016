//
// Created by antoinewdg on 2/11/16.
//

#ifndef HASH_CODE_DRONE_H
#define HASH_CODE_DRONE_H


#include "order.h"
#include "warehouse.h"
#include "product.h"

struct Drone {

    struct LoadCommand {
        Order* order;
        Warehouse* w;
        Product* p;
        int quantity;
    };

    int id;
    int r, c;
    bool available;

    Drone() : available(true) { }
};

#endif //HASH_CODE_DRONE_H
