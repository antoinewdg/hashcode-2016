//
// Created by antoinewdg on 2/11/16.
//

#ifndef HASH_CODE_SIMULATION_H
#define HASH_CODE_SIMULATION_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "product.h"
#include "warehouse.h"
#include "order.h"

using namespace std;

struct Simulation {
    int rows, cols, n_drones, t_max, payload;
    int n_products, n_warehouses, n_orders;

    vector<Product> products;
    vector<Warehouse> warehouses;
    vector<Order> orders;

    Simulation(string filename);


    vector<vector<int>> locateObjects(Order o);
};

ostream &operator<<(ostream &os, const Simulation &s);

#endif //HASH_CODE_SIMULATION_H
