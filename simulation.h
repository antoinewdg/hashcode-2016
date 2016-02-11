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
#include "drone.h"

using namespace std;

struct Simulation {



    int rows, cols, n_drones, t_max, payload;
    int n_products, n_warehouses, n_orders;

    vector<Product> products;
    vector<Warehouse> warehouses;
    vector<Order> orders;
    vector<Drone> drones;

    Simulation(string filename);


    void takeInWarehouse(Warehouse &w, Order &o, Drone::LoadCommand &command, int i, int numb, int &charge) {
        int weight = products[i].weight;
        if (w.product_quantities[i] >= numb) {
            w.product_quantities[i] -= numb;
            o.product_quantities[i] -= numb;
            command.order = &o;
            command.w = &w;
            command.p = &products[i];
            command.quantity = numb;
            charge += numb * weight;
        }
        else {
            o.product_quantities[i] -= w.product_quantities[i];
            command.order = &o;
            command.w = &w;
            command.p = &products[i];
            command.quantity = w.product_quantities[i];
            charge += w.product_quantities[i] * weight;
            w.product_quantities[i] = 0;
        }
    };


    int time_for_operation(int r1, int c1, int r2, int c2);

    vector<Drone::LoadCommand> locateObjects(Order o);

    bool droneAvailable();

    void processOrders();

    void update_drones();

};

ostream &operator<<(ostream &os, const Simulation &s);

#endif //HASH_CODE_SIMULATION_H
