//
// Created by antoinewdg on 2/11/16.
//

#ifndef HASH_CODE_COMMAND_H
#define HASH_CODE_COMMAND_H

#include <iostream>

#include "drone.h"
#include "warehouse.h"
#include "product.h"

struct Command {
    char tag;
    Drone *drone;
    Warehouse *warehouse;
    Product *product;

    int n_products;

};

ostream &operator<<(ostream &os, const Command &c) {
    os << c.drone->id << " " << c.tag << " " << c.warehouse->id << " " << c.product->id << " " << c.n_products;
}


#endif //HASH_CODE_COMMAND_H
